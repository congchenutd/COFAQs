#include "WebView.h"
#include "WebPage.h"
#include "DocVisitor.h"
#include "Settings.h"
#include "Connection.h"
#include "SearchEngineVisitor.h"

#include <QApplication>
#include <QMenu>
#include <QMouseEvent>
#include <QWebHitTestResult>
#include <QWebElement>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>

WebView::WebView(QWidget* parent)
    : QWebView(parent),
      _page(new WebPage(this)),
      _visitor(DocVisitorFactory::getInstance()->getVisitor(
                   Settings::getInstance()->getLibrary()))
{
    setPage(_page);
    setZoomFactor(Settings::getInstance()->getZoomFactor());
    connect(this, SIGNAL(loadProgress(int)),        this, SLOT(onProgress(int)));
    connect(this, SIGNAL(titleChanged(QString)),    this, SLOT(onTitleChanged(QString)));
    connect(this, SIGNAL(loadFinished(bool)),       this, SLOT(onLoaded()));
    connect(Connection::getInstance(), SIGNAL(queryReply(QJsonObject)),
            this, SLOT(onQueryReply(QJsonObject)));
}

void WebView::setZoomFactor(qreal factor)
{
    if(factor <= 0)
        factor = 1.0;
    QWebView::setZoomFactor(factor);
    Settings::getInstance()->setZoomFactor(factor);
}

void WebView::wheelEvent(QWheelEvent* event)
{
    // zoom with wheel
    if(QApplication::keyboardModifiers() & Qt::ControlModifier)
    {
        int numDegrees = event->angleDelta().y() / 8;   // see the doc for angleDelta()
        setZoomFactor(zoomFactor() + numDegrees /150);
        return event->accept();
    }
    QWebView::wheelEvent(event);
}

void WebView::contextMenuEvent(QContextMenuEvent* event)
{
    QWebHitTestResult hitTest = page()->mainFrame()->hitTestContent(event->pos());
    QMenu menu(this);

    // click on a link
    if(!hitTest.linkUrl().isEmpty())
        menu.addAction(tr("Open in New Tab"), this, SLOT(onOpenLinkInNewTab()));

    // click on empty space
    else
    {
        menu.addAction(pageAction(QWebPage::Back));
        menu.addAction(pageAction(QWebPage::Forward));
        menu.addAction(pageAction(QWebPage::Reload));

        // try to find API
        API api = _visitor->getAPI(hitTest.enclosingBlockElement());
        if(!api.getClassSignature().isEmpty())  // is a class page
        {
            setAPI(api);   // save the API current viewing

            // add an option for searching this API
            menu.addAction(QIcon(":/Images/Search.png"),
                           tr("Search for %1 on the Web").arg(api.toLowestName()),
                           this, SLOT(onSearchAPI()));
        }
    }
    menu.exec(mapToGlobal(event->pos()));
}

void WebView::onOpenLinkInNewTab() {
    pageAction(QWebPage::OpenLinkInNewWindow)->trigger();
}

void WebView::onSearchAPI() {
    emit apiSearch(_api);
}

void WebView::onProgress(int progress) {
    _progress = progress;
}

void WebView::onTitleChanged(const QString& title)
{
    if (title.isEmpty())
        return;

    if (getRole() == RESULT_ROLE)
        Connection::getInstance()->logOpenResult(getAPI().toSignature(), getQuestion(), url().toString(), title);

    else if (getRole() == ANSWER_ROLE)
        Connection::getInstance()->logOpenAnswer(getAPI().toSignature(), getQuestion(), url().toString());
}

void WebView::onLoaded()
{
    if (getRole() == DOC_ROLE) {
        requestFAQs();
    }

    else if (getRole() == SEARCH_ROLE)
    {
        ISearchEngineVisitor* visitor = SearchEngineVisitorFactory::getInstance()->getVisitor(
                    Settings::getInstance()->getSearchEngine());
        visitor->hideSearchBar(page());
    }
}

void WebView::requestFAQs()
{
    // when the page is loaded, query for the FAQ for this class
    QString classSig = _visitor->getClassSig(_visitor->getRootElement(page()));
    if(!classSig.isEmpty())   // is a class page
        Connection::getInstance()->queryFAQs(_visitor->getLibrary(), classSig);
}

void WebView::onQueryReply(const QJsonObject& joDocPage)
{
    if(joDocPage.empty())
        return;

    _visitor->setStyleSheet(page(), joDocPage.value("style").toString());

    // for each API, add a FAQ section to its document
    QJsonArray jaAPIs = joDocPage.value("apis").toArray();
    for(QJsonArray::ConstIterator it = jaAPIs.begin(); it != jaAPIs.end(); ++it)
    {
        QJsonObject joAPI = (*it).toObject();
        _visitor->addFAQ(page(), joAPI);
    }
}
