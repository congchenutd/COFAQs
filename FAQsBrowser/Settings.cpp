#include "Settings.h"
#include <QFont>
#include <QApplication>
#include <QFile>

Settings* Settings::getInstance()
{
    if(_instance == 0)
        _instance = new Settings();
    return _instance;
}

QString Settings::getDocUrl()           const { return value("DocUrl")      .toString(); }
QString Settings::getLibrary()          const { return value("LibraryName") .toString(); }
QString Settings::getServerIP()         const { return value("ServerIP")    .toString(); }
int     Settings::getServerPort()       const { return value("ServerPort")  .toInt();    }
QString Settings::getUserName()         const { return value("UserName")    .toString(); }
qreal   Settings::getZoomFactor()       const { return value("ZoomFactor")  .toReal();   }

// Google: http://www.google.com/search?q=
// Baidu: http://www.baidu.com/s?wd=
QString Settings::getSearchEngineUrl()  const {
    return getSearchEngine() == "Google" ? "http://www.google.com/search?q="
                                         : "http://www.baidu.com/s?wd="; }

QString Settings::getSearchEngine() const {
    return value("SearchEngine").toString();
}

QFont Settings::getFont() const
{
    QString savedFont = value("Font").toString();
    if(savedFont.isEmpty())
        return qApp->font();

    QFont result;
    result.fromString(savedFont);
    return result;
}

void Settings::setDocUrl            (const QString& url)        { setValue("DocUrl",            url);      }
void Settings::setLibraryName       (const QString& libName)    { setValue("LibraryName",       libName);  }
void Settings::setServerIP          (const QString& ip)         { setValue("ServerIP",          ip);       }
void Settings::setServerPort        (int port)                  { setValue("ServerPort",        port);     }
void Settings::setUserName          (const QString& userName)   { setValue("UserName",          userName); }
void Settings::setZoomFactor        (qreal factor)              { setValue("ZoomFactor",        factor);   }
void Settings::setSearchEngine      (const QString& searchEngineName) { setValue("SearchEngine", searchEngineName); }

void Settings::setFont(const QFont& font)
{
    setValue("Font", font.toString());
    qApp->setFont(font);
}

Settings::Settings()
    : QSettings("FAQsBrowser.ini", QSettings::IniFormat)
{
    if(QFile("FAQsBrowser.ini").size() == 0)   // no setting
        loadDefaults();
}

void Settings::loadDefaults()
{
    setLibraryName("Java SE 7");
    setDocUrl("http://docs.oracle.com/javase/7/docs/api/");
    setSearchEngine("Google");
    setZoomFactor(1.2);
}

Settings* Settings::_instance = 0;


