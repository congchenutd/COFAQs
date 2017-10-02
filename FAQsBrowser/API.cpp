#include "API.h"
#include <QJsonObject>
#include <QStringList>
#include <QDebug>

// e.g., java.util.ArrayList<E> -> ArrayList
QString API::getClassName() const {
    return getClassSignature().section(".", -1, -1);
}

// e.g., ensureCapacity
QString API::getMethodName() const {
    return getMethodSignature().remove(QRegExp("\\(.*\\)"));  // remove parameters
}

// A search query for the API
// e.g., Java SE 7 ArrayList ensureCapacity
QString API::toQueryString() const
{
    QString result = getLibrary() + " " + getClassName();

    // add non-cstr method
    if(getClassName() != getMethodName() && !getMethodName().isEmpty())
        result += " " + getMethodName();

    return result;
}

// e.g., Java SE 7;ArrayList.ensureCapacity()
QString API::toSignature() const
{
    QString result = getLibrary() + ";" + getClassSignature();
    if(!getMethodSignature().isEmpty())
        result += "." + getMethodSignature();
    return result;
}

// Lowest level of the API, e.g., method or class
QString API::toLowestName() const {
    return getMethodName().isEmpty() ? getClassName() : getMethodName();
}

// signature string -> API
API API::fromSignature(const QString& sig)
{
    API result;
    QString signature = sig;
    int params = QRegExp("\\(.*\\)").indexIn(sig);
    if(params > -1)
    {
        // the dot before method
        int dot = signature.lastIndexOf(".", params);
        QString methodSig = signature.right(signature.length() - dot - 1);  // method(params)
        result.setMethodSignature(methodSig);
        signature = signature.left(signature.lastIndexOf(methodSig) - 1);
    }

    int semicolon = signature.indexOf(";"); // separator of library and class
    if (semicolon > -1)
    {
        result.setLibrary(signature.left(semicolon));
        signature = signature.mid(semicolon + 1);
    }
    result.setClassSignature(signature);
    return result;
}
