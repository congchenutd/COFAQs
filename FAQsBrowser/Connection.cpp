#include "Connection.h"
#include "Settings.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include <QTimer>

Connection* Connection::_instance = 0;

Connection* Connection::getInstance()
{
    if(_instance == 0)
        _instance = new Connection;
    return _instance;
}

Connection::Connection()
    : _settings(Settings::getInstance())
{
    QTimer* timer = new QTimer;
    timer->start(5000);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    onTimer();
}

/**
 * Check if the server is alive by sending a ping message and wait for a pong response
 */
void Connection::ping()
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished   (QNetworkReply*)),
            this,    SLOT  (onPingReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    // Send request
    QString url = tr("http://%1:%2/?action=ping&username=%3")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName());
    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::registration(const QString& userName,  const QString& encryptedPassword,
                              const QString& firstName, const QString& lastName, const QString& email)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished   (QNetworkReply*)),
            this,    SLOT  (onRegistrationReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    // Send request
    QString url = tr("http://%1:%2/?action=registration&username=%3&password=%4&firstname=%5&lastname=%6&email=%7")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(userName)
            .arg(encryptedPassword)
            .arg(firstName)
            .arg(lastName)
            .arg(email);
    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::changePassword(const QString &userName, const QString& encryptedOldPassword, const QString& encryptedNewPassword)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished   (QNetworkReply*)),
            this,    SLOT  (onChangePasswordReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    // Send request
    QString url = tr("http://%1:%2/?action=changepassword&username=%3&oldpassword=%4&newpassword=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(userName)
            .arg(encryptedOldPassword)
            .arg(encryptedNewPassword);
    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::onRegistrationReply(QNetworkReply* reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit registrationReply(status == 200);  // status code 200 means OK
}

void Connection::onChangePasswordReply(QNetworkReply *reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit changePasswordReply(status == 200);  // status code 200 means OK
}

void Connection::login(const QString& userName, const QString& encryptedPassword)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished   (QNetworkReply*)),
            this,    SLOT  (onLoginReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=login&username=%3&password=%4")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(userName)
            .arg(encryptedPassword);

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::onLoginReply(QNetworkReply* reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit loginReply(status == 200);  // status code 200 means OK
}

void Connection::logout(const QString& userName)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=logout&username=%3")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(userName);
    qDebug() << userName << "logged out";

    manager->get(QNetworkRequest(QUrl(url)));
}

/**
 * Ping reply returned
 * @param reply - reply object
 */
void Connection::onPingReply(QNetworkReply* reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    _serverAlive= (status == 200);    // status code 200 means OK
    emit serverAlive(_serverAlive);
}

/**
 * Query for all Q&A pairs for a given library and class
 * @param libraryName   - library name
 * @param classSig      - class signature
 */
void Connection::queryFAQs(const QString& libraryName, const QString& classSig)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished    (QNetworkReply*)),
            this,    SLOT  (onQueryReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=queryfaqs&username=%3&class=%4")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(libraryName + ";" + classSig);
    qDebug() << "Query: " << url;
    manager->get(QNetworkRequest(QUrl(url)));
}

/**
 * Save the event of the user read the official document of an API
 * @param apiSig    - signature of the API
 */
void Connection::logDocumentReading(const QString& apiSig)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=docreading&username=%3&apisig=%4")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig);
    qDebug() << "Log API document reading: " << url;

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::logOpenDocument(const QString& apiSig)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=opendoc&username=%3&apisig=%4")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig);
    qDebug() << "Log open API document:" << url;

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::logCloseDocument(const QString& apiSig)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=closedoc&username=%3&apisig=%4")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig);
    qDebug() << "Log close API document:" << url;

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::logOpenSearch(const QString& apiSig, const QString& question)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=opensearch&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);
    manager->get(QNetworkRequest(QUrl(url)));

    qDebug() << "Open search" + url;
}

void Connection::logCloseSearch(const QString& apiSig, const QString& question)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=closesearch&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);
    manager->get(QNetworkRequest(QUrl(url)));

    qDebug() << "Close search" + url;
}

void Connection::logOpenResult(const QString& apiSig, const QString& question, const QString& link, const QString& title)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=openresult&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);

    // link may contain illegal chars for url, percent encode them
    // Workaround: tr doesn't work correctly for percent encoded strings
    url +=  "&link="        + QUrl::toPercentEncoding(link) +
            "&title="       + QUrl::toPercentEncoding(title);

    manager->get(QNetworkRequest(QUrl(url)));
    qDebug() << "Open result " << link << title;
}

void Connection::logCloseResult(const QString& apiSig, const QString& question, const QString &link)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=closeresult&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);

    // link may contain illegal chars for url, percent encode them
    // Workaround: tr doesn't work correctly for percent encoded strings
    url +=  "&link="        + QUrl::toPercentEncoding(link);

    manager->get(QNetworkRequest(QUrl(url)));
    qDebug() << "Close result " + url;
}

/**
 * Save the event of the user clicked an answer link
 * @param link  - the link to the answer page
 */
void Connection::logAnswerClicking(const QString& apiSig, const QString& question, const QString& link)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=answerclicking&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);

    // link may contain illegal chars for url, percent encode them
    // Workaround: tr doesn't work correctly for percent encoded strings
    url += "&link="  + QUrl::toPercentEncoding(link);
    qDebug() << "Log answer click: " << apiSig << question << url;

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::logOpenAnswer(const QString& apiSig, const QString& question, const QString& link)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=openanswer&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);

    // link may contain illegal chars for url, percent encode them
    // Workaround: tr doesn't work correctly for percent encoded strings
    url += "&link="  + QUrl::toPercentEncoding(link);
    qDebug() << "Log open answer: " << apiSig << question << url;

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::logCloseAnswer(const QString& apiSig, const QString& question, const QString& link)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=closeanswer&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);

    // link may contain illegal chars for url, percent encode them
    // Workaround: tr doesn't work correctly for percent encoded strings
    url += "&link="  + QUrl::toPercentEncoding(link);
    qDebug() << "Log close answer: " << apiSig << question << url;

    manager->get(QNetworkRequest(QUrl(url)));
}

void Connection::logRating(const QString& apiSig, const QString& question, const QString& link, bool helpful)
{
    if (apiSig.isEmpty() || question.isEmpty() || link.isEmpty())
    {
        qCritical() << "One of them is empty when calling logRating" << "apiSig" << apiSig << "question" << question << "link" << link;
        return;
    }

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=rateanswer&username=%3&apisig=%4&question=%5")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName())
            .arg(apiSig)
            .arg(question);

    // link may contain illegal chars for url, percent encode them
    // Workaround: tr doesn't work correctly for percent encoded strings
    url +=  "&link="  + QUrl::toPercentEncoding(link)  +
            "&helpful=" + (helpful ? "true" : "false");
    manager->get(QNetworkRequest(QUrl(url)));

    qDebug() << "Answer helpful " << url;
}

/**
 * Process query reply
 * @param reply - the reply object
 */
void Connection::onQueryReply(QNetworkReply* reply)
{
    QByteArray data = reply->readAll(); // the reply is a json array representing Q&A pairs of an API

    qDebug() << data;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error == QJsonParseError::NoError)
    {
        QJsonObject joDocPage = doc.object();
        QJsonArray jaAPIs = joDocPage.value("apis").toArray();
        if(!jaAPIs.isEmpty())
            emit queryReply(joDocPage);
    }
}

/**
 * Query for a user profile
 */
void Connection::queryUserProfile(const QString& userName)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished    (QNetworkReply*)),
            this,    SLOT  (onUserProfileReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=profile&username=%3")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(userName);
    manager->get(QNetworkRequest(QUrl(url)));
}

/**
 * Process user profile query reply
 */
void Connection::onUserProfileReply(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if(err.error == QJsonParseError::NoError)
    {
        QJsonObject profile = doc.object(); // reply is a JSON object containing profile info
        if(!profile.isEmpty())
            emit userProfileReply(profile);
    }
}

void Connection::onTimer() {
    ping();
}

/**
 * Send user photo to the server
 * @param filePath  - path of the file on the client machine
 */
void Connection::submitPhoto(const QString& filePath)
{
    QFile* file = new QFile(filePath);
    if(!file->open(QFile::ReadOnly))
        return;

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), file,    SLOT(deleteLater()));

    QString url = tr("http://%1:%2/?action=submitphoto&username=%3")
            .arg(_settings->getServerIP())
            .arg(_settings->getServerPort())
            .arg(_settings->getUserName());

    manager->post(QNetworkRequest(QUrl(url)), file);
}

bool Connection::isServerAlive() const {
    return _serverAlive;
}

QString Connection::getEncrytedPassword(const QString& plainText) {
    return QCryptographicHash::hash(plainText.toUtf8(), QCryptographicHash::Md5);
}
