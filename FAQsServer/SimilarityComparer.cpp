#include "SimilarityComparer.h"
#include "DAO.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

void SimilarityComparer::compare(const QString& sentence1, const QString& sentence2)
{
    // TODO: find common prefix of two sentences and remove it
    // otherwise, the common prefix may make the sentences very similar

    // query from db
    double similarity = DAO::getInstance()->getSentenceSimilarity(sentence1, sentence2);
    if (similarity > -1)
    {
        emit comparisonResult(SimilarityResult(sentence1, sentence2, similarity));
        return;
    }

    // query from online service
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this,    SLOT(onReply(QNetworkReply*)));
    connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    manager->get(QNetworkRequest(makeUrl(sentence1, sentence2)));
}

SimilarityComparer* SimilarityComparer::getInstance()
{
    static SimilarityComparer instance;
    return &instance;
}

void SimilarityComparer::onReply(QNetworkReply* reply)
{
    auto result = parseResult(reply);
    DAO::getInstance()->updateSentenceSimilarity(result);
    emit comparisonResult(result);
}

QUrl SimilarityComparer::makeUrl(const QString& sentence1, const QString& sentence2) const {
    return QUrl(tr("https://api.dandelion.eu/datatxt/sim/v1/?text1=%1&text2=%2&token=ed80aa79e8204214b94a0d50b7ed9dbb")
                .arg(sentence1).arg(sentence2));
}

SimilarityResult SimilarityComparer::parseResult(QNetworkReply* reply)
{
    SimilarityResult result;
    QString query = reply->request().url().query();
    QStringList sections = query.split("&");
    if (sections.size() > 2)    // should be 3
    {
        result._sentence1 = sections[1];
        result._sentence2 = sections[2];
    }
    QJsonObject jsonObj = QJsonDocument::fromJson(reply->readAll()).object();
    if (jsonObj.contains("similarity"))
        result._similarity = jsonObj.value("similarity").toDouble();
    return result;
}

SimilarityResult::SimilarityResult(const QString& sentence1, const QString& sentence2, double similarity)
    : _sentence1    (sentence1),
      _sentence2    (sentence2),
      _similarity   (similarity)
{}
