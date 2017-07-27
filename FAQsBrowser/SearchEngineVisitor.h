#ifndef SEARCHENGINEVISITOR_H
#define SEARCHENGINEVISITOR_H

#include <QWebPage>

class ISearchEngineVisitor
{
public:
    virtual ~ISearchEngineVisitor();
    virtual void hideSearchBar(const QWebPage* page) = 0;
};

class GoogleVisitor: public ISearchEngineVisitor
{
public:
    void hideSearchBar(const QWebPage* page);
};

class BaiduVisitor: public ISearchEngineVisitor
{
public:
    void hideSearchBar(const QWebPage* page);
};


/////////////////////////////////////////////////////////////////////
// return a visitor object based on its name

Q_DECLARE_METATYPE(GoogleVisitor);
Q_DECLARE_METATYPE(BaiduVisitor);

class SearchEngineVisitorFactory
{
public:
    ISearchEngineVisitor* getVisitor(const QString& name) const;
    static SearchEngineVisitorFactory* getInstance();

private:
    SearchEngineVisitorFactory();

private:
    static SearchEngineVisitorFactory* _instance;
};

#endif // SEARCHENGINEVISITOR_H
