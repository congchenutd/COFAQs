﻿#ifndef DAO_H
#define DAO_H

#include <QObject>
#include "Logger.h"

class QJsonDocument;
class SimilarityComparer;

// 读写数据库的DAO
class DAO : public QObject
{
    Q_OBJECT

public:
    static DAO* getInstance();

    void setLogger(Logger* logger);

    // log API doc reading history
    void logDocumentReading(const QString& userName, const QString& email, const QString& apiSig);

    // opened a search page
    void logSearchStart(const QString& userName, const QString& email, const QString& apiSig, const QString& question);

    // closed a search page
    void logSearchEnd(const QString& userName, const QString& email, const QString& apiSig, const QString& question);

    // opened a search result
    void logOpenResult(const QString& userName, const QString& email, const QString& apiSig,
                       const QString& question, const QString& link, const QString& title);

    // closed a search result
    void logCloseResult(const QString& userName, const QString& email, const QString& apiSig,
                        const QString& question, const QString& link);

    // user clicked helpful or unhelpful
    void logRating(const QString& userName, const QString& email, const QString& apiSig,
                    const QString& question, const QString& link,  bool helpful);

    // opened an answer link
    void logAnswerClicking(const QString& userName, const QString& email, const QString& apiSig,
                           const QString& question, const QString& link);

    // query FAQs for an API (class)
    QJsonDocument queryFAQs(const QString& classSig) const;

    // query personal profile
    QJsonDocument queryUserProfile(const QString& userName) const;

private slots:
    void onComparisonResult(const QString& leadQuestion,
                            const QString& question, qreal similarity);

private:
    DAO();
    int getNextID    (const QString& tableName) const;
    int getID(const QString& tableName, const QString& section, const QString& value) const;

    int getUserID    (const QString& userName)  const;   // for convenience
    int getAPIID     (const QString& signature) const;
    int getQuestionID(const QString& question)  const;
    int getAnswerID  (const QString& link)      const;

    int updateUser    (const QString& userName, const QString& email);
    int updateAPI     (const QString& signature);
    int updateQuestion(const QString& question, const QString& apiSig);
    int updateAnswer  (const QString& link, const QString& title);

//    void updateUserRateAnswer(int userID, int apiID, int questionID, int answerID, bool helpful);

    void updateLead(int questionID);   // try to make questionID the new lead

    // initiate comparison between the question and other lead questions associated with apiID
    void measureSimilarity(const QString& question, int apiID);

    // table -> json
    QJsonObject createAnswerJson    (int answerID) const;  // an answer -> json
    QJsonObject createUserJson      (int userID)   const;  // a user    -> json
    QJsonArray  createAnswersJson   (int apiID, int questionID) const;
    QJsonArray  createUsersJson     (int userID, int questionID) const;
    QJsonObject createQuestionJson (int apiID, int leadID) const;  // question group -> json
    QJsonArray  createQuestionsJson(int apiID)  const;  // api            -> its questions

    QString getCurrentDateTime() const;
    QString getDateTimeFormat() const;

private:
    static DAO*         _instance;
    SimilarityComparer* _comparer;
    Logger*             _logger;
};

#endif // DAO_H
