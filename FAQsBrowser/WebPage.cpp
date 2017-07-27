#include "WebPage.h"
#include "WebView.h"
#include "MainWindow.h"
#include "TabWidget.h"
#include "DocVisitor.h"
#include "Connection.h"
#include "Settings.h"
#include "API.h"

#include <QDesktopServices>
#include <QNetworkRequest>
#include <QDebug>
#include <QWebFrame>
#include <QWebElement>
#include <QNetworkReply>

WebPage::WebPage(QObject* parent)
    : QWebPage(parent)
{
    const QString libName = Settings::getInstance()->getLibrary();
    _visitor = DocVisitorFactory::getInstance()->getVisitor(libName);
    connect(networkAccessManager(), SIGNAL(sslErrors(QNetworkReply*, QList<QSslError>)), SLOT(onSslErrors(QNetworkReply*)));
}

void WebPage::onSslErrors(QNetworkReply* reply) {
    reply->ignoreSslErrors();
}

bool WebPage::acceptNavigationRequest(QWebFrame* frame, const QNetworkRequest& request, NavigationType type)
{
    if(type == NavigationTypeLinkClicked)
    {
        // personal profile link
        if(request.url().toString().startsWith("profile:", Qt::CaseInsensitive))
        {
            QString userName = request.url().toString().remove("profile:");
            MainWindow::getInstance()->newPersonalTab(userName);
            return false;
        }

        WebView* thisView = static_cast<WebView*>(view());

        // document page
        if(thisView->getRole() == WebView::DOC_ROLE)
        {
            QString url = request.url().toString();

            // document link clicked
            if(url.startsWith(Settings::getInstance()->getDocUrl()))
                Connection::getInstance()->logDocumentReading(_visitor->urlToAPI(url).toSignature());
            // external link (answer link) clicked
            else
            {
                Connection::getInstance()->logAnswerClicking(url);
                WebView* newView = MainWindow::getInstance()->newTab(WebView::RESULT_ROLE);
                newView->setAPI(thisView->getAPI());    // transfer the attributes
                newView->load(request);
                return false;
            }
        }

        // links on the search page open in new tab
        else if(thisView->getRole() == WebView::SEARCH_ROLE)
        {
            WebView* newView = MainWindow::getInstance()->newTab(WebView::RESULT_ROLE);
            newView->setAPI     (thisView->getAPI());    // transfer the attributes
            newView->setQuestion(thisView->getQuestion());
            newView->load(request);
            return false;
        }
    }
    else if (type == NavigationTypeFormSubmitted)
    {
        qDebug() << "Search within search page" << request.url();
        // TODO: this is the place where we can capture if the user reuses the search page
        // Best option is perhaps to replace the original search line and button with our own,
        // thus we are able to constrain the related API
    }
    return QWebPage::acceptNavigationRequest(frame, request, type);
}

// always open in tab
QWebPage* WebPage::createWindow(QWebPage::WebWindowType) {
    return MainWindow::getInstance()->newTab()->page();
}
