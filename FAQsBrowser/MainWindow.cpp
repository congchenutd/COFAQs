﻿#include "MainWindow.h"
#include "TabWidget.h"
#include "TabBar.h"
#include "WebView.h"
#include "OptionsDlg.h"
#include "Connection.h"
#include "Settings.h"
#include "WebPage.h"
#include <QMessageBox>
#include <QWebSettings>
#include <QProgressBar>
#include <QDebug>
#include <QWebHistory>
#include <QCloseEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    _instance = this;
    _settings = Settings::getInstance();

    _tabWidget = new TabWidget(this);
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(_tabWidget);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    QWebSettings::setIconDatabasePath(".");
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled,    true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);

    ui.actionBack   ->setIcon(qApp->style()->standardIcon(QStyle::SP_ArrowBack));
    ui.actionForward->setIcon(qApp->style()->standardIcon(QStyle::SP_ArrowForward));
    ui.actionDocPage   ->setShortcut(QKeySequence("Ctrl+1"));
    ui.actionZoomIn    ->setShortcut(QKeySequence::ZoomIn);
    ui.actionZoomOut   ->setShortcut(QKeySequence::ZoomOut);
    ui.actionFullScreen->setShortcut(QKeySequence::FullScreen);
    ui.actionShowSearch->setShortcut(QKeySequence::Find);

    TabBar* tabBar = static_cast<TabBar*>(_tabWidget->tabBar());
    ui.menuTab->addAction(tabBar->getActionClose());
    ui.menuTab->addAction(tabBar->getActionCloseOthers());
    ui.menuTab->addAction(tabBar->getActionCloseAll());
    ui.menuTab->addSeparator();
    ui.menuTab->addAction(tabBar->getActionRefresh());
    ui.menuTab->addAction(tabBar->getActionRefreshAll());

    _progressBar = new QProgressBar(this);
    _progressBar->setMaximum(100);
    ui.statusBar->addPermanentWidget(_progressBar);

    _labelServerStatus = new QLabel;
    ui.statusBar->addPermanentWidget(_labelServerStatus);
    ui.statusBar->addPermanentWidget(new QLabel("  ")); // extra space to the right

    qApp->setFont(_settings->getFont());

    onDocPage();
    toggleReloadStop(false);  // update reload/stop button status

    connect(ui.actionAbout,         SIGNAL(triggered()), this, SLOT(onAbout()));
    connect(ui.actionDocPage,       SIGNAL(triggered()), this, SLOT(onDocPage()));
    connect(ui.actionZoomIn,        SIGNAL(triggered()), this, SLOT(onZoomIn()));
    connect(ui.actionZoomOut,       SIGNAL(triggered()), this, SLOT(onZoomOut()));
    connect(ui.actionResetZoom,     SIGNAL(triggered()), this, SLOT(onZoomReset()));
    connect(ui.actionBack,          SIGNAL(triggered()), this, SLOT(onBack()));
    connect(ui.actionForward,       SIGNAL(triggered()), this, SLOT(onForward()));
    connect(ui.actionReloadStop,    SIGNAL(triggered()), this, SLOT(onReloadStop()));
    connect(ui.actionHelpful,       SIGNAL(triggered()), this, SLOT(onHelpful()));
    connect(ui.actionNotHelpful,    SIGNAL(triggered()), this, SLOT(onNotHelpful()));
    connect(ui.actionPersonal,      SIGNAL(triggered()), this, SLOT(onPersonal()));
    connect(ui.actionQuit,          SIGNAL(triggered()), this, SLOT(onQuit()));
    connect(ui.actionOptions,       SIGNAL(triggered()), this, SLOT(onOptions()));

    connect(ui.actionShowSearch,   SIGNAL(toggled(bool)), this, SLOT(onShowSearch  (bool)));
    connect(ui.actionZoomTextOnly, SIGNAL(toggled(bool)), this, SLOT(onZoomTextOnly(bool)));
    connect(ui.actionFullScreen,   SIGNAL(toggled(bool)), this, SLOT(onFullScreen  (bool)));

    connect(ui.toolBarSearch, SIGNAL(hideMe()), ui.actionShowSearch, SLOT(toggle()));
    connect(ui.toolBarSearch, SIGNAL(search(QString,bool,bool)),
            this, SLOT(onSearch(QString,bool,bool)));
    connect(ui.toolBarSearch, SIGNAL(highlight(QString,bool,bool)),
            this, SLOT(onHighlight(QString,bool,bool)));

    connect(_tabWidget, SIGNAL(loadProgress(int)),              this, SLOT(onLoadProgress(int)));
    connect(_tabWidget, SIGNAL(currentTitleChanged(QString)),   this, SLOT(onCurrentTitleChanged(QString)));
    connect(_tabWidget, SIGNAL(historyChanged()),               this, SLOT(onHistoryChanged()));
    connect(_tabWidget, SIGNAL(linkHovered(QString)), statusBar(), SLOT(showMessage(QString)));
//    connect(_tabWidget, SIGNAL(tabCloseRequested(int)),         this, SLOT(onCloseTab(int)));
    connect(_tabWidget, SIGNAL(titleLoaded()),                  this, SLOT(updateHelpfulButtons()));
    connect(_tabWidget, SIGNAL(currentChanged(int)),            this, SLOT(updateHelpfulButtons()));

    Connection* connection = Connection::getInstance();
    connect(connection, SIGNAL(serverAlive(bool)), this, SLOT(onServerAlive(bool)));
    onServerAlive(connection->isServerAlive());

    ui.actionShowSearch->toggle();
}

WebView* MainWindow::newTab(WebView::PageRole role) {
    return _tabWidget->newTab(role);
}

void MainWindow::newPersonalTab(const QString& userName)
{
    _tabWidget->newTab(WebView::PROFILE_ROLE)->load(
        QUrl(tr("http://%1:%2/?action=profile&username=%3").arg(_settings->getServerIP())
                                                           .arg(_settings->getServerPort())
             .arg(userName)));
}

MainWindow* MainWindow::_instance = 0;

MainWindow* MainWindow::getInstance() {
    return _instance;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    _tabWidget->onCloseAllTabs();   // save closing events
    event->accept();
    onQuit();
}

void MainWindow::onAbout() {
    QMessageBox::about(this, tr("About"),
                       tr("<h3><b>FAQs Browser v0.2.2</b></h3>"
                          "<p><a href=mailto:CongChenUTD@Gmail.com>CongChenUTD@Gmail.com</a></p>"));
}

void MainWindow::onDocPage() {
    _tabWidget->setCurrentIndex(_tabWidget->getDocTabIndex());
}

void MainWindow::onZoomIn() {
    if(WebView* webView = currentWebView())
        webView->setZoomFactor(webView->zoomFactor() + 0.2);
}

void MainWindow::onZoomOut() {
    if(WebView* webView = currentWebView())
        webView->setZoomFactor(webView->zoomFactor() - 0.2);
}

void MainWindow::onZoomReset() {
    if(WebView* webView = currentWebView())
        webView->setZoomFactor(1.0);
}

void MainWindow::onZoomTextOnly(bool textOnly) {
    QWebSettings::globalSettings()->setAttribute(QWebSettings::ZoomTextOnly, textOnly);
}

void MainWindow::onFullScreen(bool fullScreen)
{
    if(fullScreen)
        showFullScreen();
    else
        showMaximized();
}

void MainWindow::onShowSearch(bool show) {
    ui.toolBarSearch->setVisible(show);
}

void MainWindow::onSearch(const QString& target, bool forward, bool matchCase)
{
    if(WebView* webView = currentWebView())
    {
        QWebPage::FindFlags flags = QWebPage::FindWrapsAroundDocument;
        if(!forward)
            flags |= QWebPage::FindBackward;
        if(matchCase)
            flags |= QWebPage::FindCaseSensitively;
        webView->findText(target, flags);
    }
}

void MainWindow::onHighlight(const QString& target, bool highlight, bool matchCase)
{
    if(WebView* webView = currentWebView())
    {
        QWebPage::FindFlags flags = QWebPage::HighlightAllOccurrences |
                                    QWebPage::FindWrapsAroundDocument;
        if(matchCase)
            flags |= QWebPage::FindCaseSensitively;
        webView->findText(highlight ? target : QString(),
                          flags);
    }
}

void MainWindow::onLoadProgress(int progress)
{
    bool loading = 0 < progress && progress < 100;
    _progressBar->setValue(progress);
    _progressBar->setVisible(loading);
    toggleReloadStop(loading);
}

void MainWindow::onCurrentTitleChanged(const QString& title) {
    setWindowTitle(title.isEmpty() ? tr("FAQ Browser")
                                   : tr("%1 - FAQ Browser").arg(title));
}

void MainWindow::onBack() {
    if(WebView* webView = currentWebView())
        webView->back();
}

void MainWindow::onForward() {
    if(WebView* webView = currentWebView())
        webView->forward();
}

void MainWindow::onHistoryChanged()
{
    if(WebView* webView = currentWebView())
    {
        ui.actionBack   ->setEnabled(webView->history()->canGoBack());
        ui.actionForward->setEnabled(webView->history()->canGoForward());
    }
}

void MainWindow::onReloadStop()
{
    if(WebView* webView = currentWebView())
    {
        if(ui.actionReloadStop->text() == tr("Stop"))
            webView->stop();
        else
            webView->reload();
    }
}

void MainWindow::onHelpful()
{
    if(WebView* webView = currentWebView())
        Connection::getInstance()->logRating(webView->getAPI().toSignature(),
                                              webView->getQuestion(),
                                              webView->url().toString(),
                                              true);

    _tabWidget->closeTab(_tabWidget->currentIndex());
}

void MainWindow::onNotHelpful()
{
    if(WebView* webView = currentWebView())
        Connection::getInstance()->logRating(webView->getAPI().toSignature(),
                                              webView->getQuestion(),
                                              webView->url().toString(),
                                              false);

    _tabWidget->closeTab(_tabWidget->currentIndex());
}

//void MainWindow::onCloseTab(int index)
//{
////    WebView* webView = _tabWidget->getWebView(index);
////    if (webView->getRole() == WebView::RESULT_ROLE)
////        Connection::getInstance()->logHelpful(webView->getAPI().toSignature(),
////                                              webView->getQuestion(),
////                                              webView->url().toString(),
////                                              webView->title(),
////                                              false);

//    _tabWidget->closeTab(index);
//}

void MainWindow::updateHelpfulButtons()
{
    if(WebView* webView = currentWebView())
    {
        WebView::PageRole role = webView->getRole();
        bool showHelpful = (role == WebView::RESULT_ROLE || role == WebView::ANSWER_ROLE) && !webView->title().isEmpty();
        ui.actionHelpful   ->setVisible(showHelpful);
        ui.actionNotHelpful->setVisible(showHelpful);
    }
}

void MainWindow::onTimer() {
    Connection::getInstance()->ping();
}

void MainWindow::onServerAlive(bool serverAlive)
{
    // Server is disconnected
    if (!serverAlive)
    {
        _labelServerStatus->setText(tr("  Server is disconnected."));
        return;
    }

    // Already logged in
    _labelServerStatus->setText(tr("  %1 is logged onto the server.").arg(_settings->getUserName()));
}

void MainWindow::onQuit()
{
    Connection::getInstance()->logout(_settings->getUserName());
    qApp->quit();
}

void MainWindow::onOptions()
{
    OptionsDlg dlg(this);
    dlg.exec();
}

void MainWindow::onPersonal() {
    newPersonalTab(_settings->getUserName());
}

WebView* MainWindow::currentWebView() const {
    return _tabWidget->getCurrentWebView();
}

void MainWindow::toggleReloadStop(bool loading)
{
    ui.actionReloadStop->setIcon(
                qApp->style()->standardIcon(loading ? QStyle::SP_BrowserStop
                                                    : QStyle::SP_BrowserReload));
    ui.actionReloadStop->setText   (loading ? tr("Stop") : tr("Reload"));
    ui.actionReloadStop->setToolTip(loading ? tr("Stop") : tr("Reload"));
}
