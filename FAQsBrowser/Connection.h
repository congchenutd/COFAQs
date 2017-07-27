﻿#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>

class Settings;
class QNetworkReply;

// communicating with server
class Connection : public QObject
{
    Q_OBJECT

public:
    static Connection* getInstance();   // singleton
    void ping();    // check if the server is alive

    // Log API reading
    void logDocumentReading(const QString& apiSig);  // user viewed the api doc

    void logSearchStart(const QString& apiSig, const QString& question);

    void logSearchEnd(const QString& apiSig, const QString& question);

    void logOpenResult(const QString& link);

    void logCloseResult(const QString& link);

    // save a Q&A pair
    void saveFAQ(const QString& apiSig, const QString& question,
                 const QString& link = QString(), const QString& title = QString());

    // Log answer reading
    void logAnswerClicking(const QString& link);    // user clicked an answer link

    void logHelpful(const QString& link, bool helpful);

    // query for all Q&A pairs related to a given API
    void queryFAQs(const QString& libraryName, const QString& classSig);

    // Query a user's profile
    void queryUserProfile(const QString& userName);

    // Submit this user's photo
    void submitPhoto(const QString& filePath);

private slots:
    void onPingReply (QNetworkReply* reply);
    void onQueryReply(QNetworkReply* reply);
    void onUserProfileReply(QNetworkReply* reply);

signals:
    void pingReply(bool alive);

    // an array of api objects, each api object contains multiple questions
    void queryReply(const QJsonObject&);

    void userProfileReply(const QJsonObject&);

private:
    Connection();

private:
    static Connection* _instance;
    Settings*          _settings;
};

#endif // CONNECTION_H
