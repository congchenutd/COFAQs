#include "SearchEngineVisitor.h"
#include <QDebug>
#include <QWebFrame>
#include <QWebElementCollection>

ISearchEngineVisitor::~ISearchEngineVisitor() {}


void GoogleVisitor::hideSearchBar(const QWebPage *page)
{
    QWebElement form = page->mainFrame()->findFirstElement("form[id=tsf]");
    form.removeFromDocument();
}

void BaiduVisitor::hideSearchBar(const QWebPage* page)
{
    QWebElement form = page->mainFrame()->findFirstElement("form[id=form]");
    form.removeFromDocument();
}

/////////////////////////////////////////////////////////////////////
SearchEngineVisitorFactory* SearchEngineVisitorFactory::_instance = 0;

SearchEngineVisitorFactory* SearchEngineVisitorFactory::getInstance()
{
    if(_instance == 0)
        _instance = new SearchEngineVisitorFactory;
    return _instance;
}

ISearchEngineVisitor* SearchEngineVisitorFactory::getVisitor(const QString& name) const
{
    int id = QMetaType::type(name.toUtf8());
    if(id != QMetaType::UnknownType)
        return static_cast<ISearchEngineVisitor*>(QMetaType::create(id));
    return 0;
}

SearchEngineVisitorFactory::SearchEngineVisitorFactory()
{
    // class name -> parser name
    qRegisterMetaType<GoogleVisitor>("Google");
    qRegisterMetaType<BaiduVisitor>("Baidu");
}
