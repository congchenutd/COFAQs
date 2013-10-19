#include "DocParser.h"
#include <QString>
#include <QWebElement>
#include <QRegExp>

/// A method details section of a Java Doc page looks like
/// <a name = ClassName>
/// </a>
/// <ul>
///   <XXX>
///       class details
///   </XXX>
/// </ul>
APIInfo JavaSE7Parser::parse(const QWebElement& e) const
{
    APIInfo result;
    if(e.isNull())
        return result;

    QWebElement p = e;
    while(p.tagName() != "UL")   // go up until a "ul" tag
    {
        if(p.isNull())           // empty tag
            return result;
        p = p.parent();
    }

    p = p.previousSibling();     // the tag above the "ul" is an "a" tag for class name
    if(p.tagName() == "A")
    {
        // full class name is found at the last ul tag a class=inheritance attribute
        QString fullClassName = e.document().findAll("ul[class=inheritance]").last().toPlainText();

        // the class name from the full class name and removing generic things like <T>
        result._className   = fullClassName.split(".").last().remove(QRegExp("<.*>"));

        // the package name is what remains after removing .classname
        result._packageName = fullClassName.remove(QRegExp("\\.\\w+$"));
        result._libName     = getLibName();

        // the parameter list of a method is removed
        result._methodName  = p.attribute("name").remove(QRegExp("\\(.*\\)"));
    }

    return result;
}

QByteArray JavaSE7Parser::getLibName() { return "Java SE 7"; }


/////////////////////////////////////////////////////////////////////
DocParserFactory* DocParserFactory::_instance = 0;

DocParserFactory* DocParserFactory::getInstance()
{
    if(_instance == 0)
        _instance = new DocParserFactory;
    return _instance;
}

IDocParser* DocParserFactory::getParser(const QString& name) const
{
    int id = QMetaType::type(name.toUtf8());
    if(id != QMetaType::UnknownType)
        return static_cast<IDocParser*>(QMetaType::create(id));
    return 0;
}

DocParserFactory::DocParserFactory()
{
    // class name -> parser name
    qRegisterMetaType<JavaSE7Parser>(JavaSE7Parser::getLibName());
}


////////////////////////////////////////////////////////////////////////////////
bool APIInfo::isEmpty() const {
    return _methodName.isEmpty();
}

QString APIInfo::toString() const
{
    QString result = _libName + " " + _className;
    if(_className != _methodName)  // constructor has the same name as class
        result += " " + _methodName;
    return result;
}
