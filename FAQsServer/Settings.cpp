#include "Settings.h"

#include <QFile>

// Singleton方法
Settings* Settings::getInstance()
{
    if(_instance == 0)
        _instance = new Settings();
    return _instance;
}

QString Settings::getServerIP()   const { return value("IP").toString(); }
quint16 Settings::getServerPort() const { return static_cast<quint16>(value("Port").toUInt()); }
double  Settings::getSimilarityThreshold()  const { return value("SimilarityThreshold").toDouble(); }

// Min number of answers before we consider rating
// If there are no enough answers, we will show all the answers regardless of the ratings
int Settings::getMinAnswerCount() const { return value("MinAnswerCount").toInt(); }

void Settings::setServerIP  (const QString& ip) { setValue("IP", ip); }
void Settings::setServerPort(uint port)         { setValue("Port", port); }
void Settings::setMinAnswerCount(int count)     { setValue("MinAnswerCount", count); }
void Settings::setSimilarityThreshold(double threshold) { setValue("SimilarityThreshold", threshold); }

Settings::Settings()
    : QSettings("FAQsServer.ini", QSettings::IniFormat)
{
    if(QFile("FAQsServer.ini").size() == 0)   // no setting
        loadDefaults();
}

void Settings::loadDefaults()
{
    setServerIP("localhost");
    setServerPort(8080);
    setSimilarityThreshold(0.75);
    setMinAnswerCount(3);
}

Settings* Settings::_instance = 0;


