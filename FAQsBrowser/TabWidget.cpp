#include "TabWidget.h"
#include "TabBar.h"
#include "WebView.h"
#include "SearchDlg.h"
#include "Connection.h"
#include "Settings.h"
#include "WebPage.h"

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent),
      _tabBar(new TabBar(this))
{
    setTabBar(_tabBar);
    setElideMode(Qt::ElideRight);
    setDocumentMode(true);

    connect(_tabBar, SIGNAL(closeOtherTabs(int)),    this, SLOT(onCloseOtherTabs(int)));
    connect(_tabBar, SIGNAL(closeAllTabs()),         this, SLOT(onCloseAllTabs()));
    connect(_tabBar, SIGNAL(reloadTab(int)),         this, SLOT(onReloadTab(int)));
    connect(_tabBar, SIGNAL(reloadAllTabs()),        this, SLOT(onReloadAllTabs()));
    connect(this, SIGNAL(tabCloseRequested(int)),    this, SLOT(closeTab(int)));

    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onCurrentChanged(int)));
}

WebView* TabWidget::getCurrentWebView() const {
    return getWebView(currentIndex());
}

WebView* TabWidget::getWebView(int index) const {
    return qobject_cast<WebView*>(widget(index));
}

int TabWidget::getDocTabIndex()
{
    // find existing doc page
    for(int i = 0; i < count(); ++i)
        if(getWebView(i)->getRole() == WebView::DOC_ROLE)
            return i;

    // or create a new one
    WebView* webView = newTab(WebView::DOC_ROLE);
    webView->load(QUrl(Settings::getInstance()->getDocUrl()));
    return indexOf(webView);
}

int TabWidget::findExistingSearchTab() const
{
    for(int index = 0; index < count(); ++index)
        if(getWebView(index)->getRole() == WebView::SEARCH_ROLE)
            return index;
    return -1;
}

/**
 * Find an existing or create a new search tab
 * @param api       - API for the search
 * @param query     - search query
 * @param question  - question
 * @return          - the index of the tab
 */
int TabWidget::createSearchTab(const API& api, const QString& query, const QString& question)
{
    // find existing search page
    int index = findExistingSearchTab();

    // create a new view or use the existing one
    WebView* webView = (index == -1) ? newTab(WebView::SEARCH_ROLE)
                                     : getWebView(index);

    // Previous search is ended, log previous search
    if (index > -1)
        Connection::getInstance()->logCloseSearch(webView->getAPI().toSignature(), webView->getQuestion());

    // log current search
    Connection::getInstance()->logOpenSearch(api.toSignature(), question);

    // load search page
    webView->setAPI(api);
    webView->setQuestion(question);
    webView->load(QUrl(Settings::getInstance()->getSearchEngineUrl() + query));

    return index;
}

void TabWidget::onAPISearch(const API& api)
{
    SearchDlg dlg(this);
    dlg.setContext(api.toQueryString());
    if(dlg.exec() == QDialog::Accepted)
    {
        setCurrentIndex(
            createSearchTab(api, dlg.getQuery(), dlg.getQuestion())   // go searching
        );
    }
}

void TabWidget::onReloadTab(int index) {
    if(WebView* webView = getWebView(index))
        webView->reload();
}

void TabWidget::onCurrentChanged(int index)
{
    static int prevTabIndex = -1;  // for disconnecting signals from prev tab
    if(index == prevTabIndex)
        return;

    WebView* webView = getWebView(index);
    if(webView == 0)
        return;

    // disconnect signals from prev tab so that its progress won't affect current one
    if(WebView* oldWebView = getWebView(prevTabIndex))
        disconnect(oldWebView, SIGNAL(loadProgress(int)), this, SIGNAL(loadProgress(int)));

    connect(webView, SIGNAL(loadProgress(int)), this, SIGNAL(loadProgress(int)));

    emit currentTitleChanged(webView->title());
    emit historyChanged();
    emit loadProgress(webView->getProgress());

    prevTabIndex = index;
}

void TabWidget::onTitleLoaded(const QString& title)
{
    if (title.isEmpty())
        return;

    WebView* webView = qobject_cast<WebView*>(sender());
    int index = indexOf(webView);
    if(-1 != index && currentIndex() == index)
        emit titleLoaded();
}

WebView* TabWidget::newTab(WebView::PageRole role)
{
    WebView* webView = new WebView;
    webView->setRole(role);

    connect(webView, SIGNAL(loadStarted()),         this, SLOT(onWebViewLoadStarted()));
    connect(webView, SIGNAL(loadFinished(bool)),    this, SLOT(onWebViewIconChanged()));
    connect(webView, SIGNAL(iconChanged()),         this, SLOT(onWebViewIconChanged()));
    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(onWebViewTitleChanged(QString)));
    connect(webView, SIGNAL(apiSearch(API)),        this, SLOT(onAPISearch(API)));
    connect(webView, SIGNAL(titleChanged(QString)), this, SLOT(onTitleLoaded(QString)));

    connect(webView->page(), SIGNAL(linkHovered(QString,QString,QString)),
            this, SIGNAL(linkHovered(QString)));
    connect(webView->page()->action(QWebPage::Forward), SIGNAL(changed()), this, SIGNAL(historyChanged()));
    connect(webView->page()->action(QWebPage::Back),    SIGNAL(changed()), this, SIGNAL(historyChanged()));

    addTab(webView, tr("(Untitled)"));
    setCurrentWidget(webView);

    return webView;
}

void TabWidget::onReloadAllTabs()
{
    for(int i = 0; i < count(); ++i)
        if(WebView* webView = getWebView(i))
            webView->reload();
}

void TabWidget::onCloseOtherTabs(int index)
{
    for(int i = count() - 1; i >= 0; --i)
        if(i != index)
            closeTab(i);
}

void TabWidget::onCloseAllTabs() {
    for(int i = count() - 1; i >= 0; --i)
        closeTab(i);
}

void TabWidget::closeTab(int index)
{
    if (index < 0 || index >= count())
        return;

    if(WebView* webView = getWebView(index))
    {
        WebView::PageRole role = webView->getRole();
        if (role == WebView::DOC_ROLE)  // doc page not closable
            return;

        Connection* connection = Connection::getInstance();
        QString apiSig      = webView->getAPI().toSignature();
        QString question    = webView->getQuestion();
        QString url         = webView->url().toString();
        if (role == WebView::SEARCH_ROLE)
            connection->logCloseSearch(apiSig, question);
        else if (role == WebView::RESULT_ROLE)
            connection->logCloseResult(apiSig, question, url);
        else if (role == WebView::ANSWER_ROLE)
            connection->logCloseAnswer(apiSig, question, url);
    }

    widget(index)->deleteLater();
    removeTab(index);
}

void TabWidget::onWebViewLoadStarted()
{
    WebView* webView = qobject_cast<WebView*>(sender());
    int index = indexOf(webView);
    if(-1 != index)
        setTabIcon(index, QIcon(":/Images/Loading.gif"));
}

void TabWidget::onWebViewIconChanged()
{
    WebView* webView = qobject_cast<WebView*>(sender());
    int index = indexOf(webView);
    if(-1 != index)
    {
        QIcon icon = QWebSettings::iconForUrl(webView->url());
        icon = icon.isNull() ? QIcon(":/Images/DefaultIcon.png").pixmap(16, 16)
                             : icon.pixmap(16, 16);
        setTabIcon(index, icon);
    }
}

void TabWidget::onWebViewTitleChanged(const QString& title)
{
    WebView* webView = qobject_cast<WebView*>(sender());
    int index = indexOf(webView);
    if(-1 != index)
        setTabText(index, title);
    if(currentIndex() == index)
        emit currentTitleChanged(title);
}
