#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include "WebView.h"

class TabBar;
class API;

class TabWidget : public QTabWidget
{
    Q_OBJECT

signals:
    void currentTitleChanged(const QString& title);
    void linkHovered(const QString& link);
    void loadProgress(int progress);
    void historyChanged();   // page back and forward history

public:
    TabWidget(QWidget* parent = 0);

    WebView* getCurrentWebView() const;
    WebView* getWebView(int index) const;

    int getDocTabIndex();
    int getSearchTabIndex(const API& api, const QString& query, const QString& question);

    WebView* newTab(WebView::PageRole role = WebView::NULL_ROLE);

public slots:
    void closeTab(int index = -1);
    void onCloseAllTabs();

private slots:
    void onCloseOtherTabs(int index);
    void onReloadTab(int index = -1);
    void onReloadAllTabs();
    void onAPISearch(const API& api);
    void onCurrentChanged(int index);

    void onWebViewLoadStarted();
    void onWebViewIconChanged();
    void onWebViewTitleChanged(const QString &title);

private:
    int findExistingSearchTab() const;

private:
    TabBar* _tabBar;
};

#endif // TABWIDGET_H

