#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
public:
    static Settings* getInstance();

    QString getDocUrl()             const;
    QString getLibrary()            const;
    QString getServerIP()           const;
    int     getServerPort()         const;
    QString getUserName()           const;
    qreal   getZoomFactor()         const;
    QFont   getFont()               const;
    QString getSearchEngineUrl()    const;
    QString getSearchEngine()       const;
//    QString getLoggedUserName()     const;

    void setDocUrl          (const QString& url);
    void setLibraryName     (const QString& libName);
    void setServerIP        (const QString& ip);
    void setServerPort      (int port);
    void setUserName        (const QString& userName);
    void setZoomFactor      (qreal factor);
    void setFont            (const QFont& font);
    void setSearchEngine    (const QString& searchEngineName);
//    void setLoggedUserName  (const QString& userName);

private:
    Settings();
    void loadDefaults();

private:
    static Settings* _instance;

    QString _loggedUserName;
};

#endif // SETTINGS_H
