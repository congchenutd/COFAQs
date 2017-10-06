#ifndef SIMILARITYCOMPARER_H
#define SIMILARITYCOMPARER_H

#include <QObject>

class QNetworkReply;

struct SimilarityResult
{
    SimilarityResult(){}
    SimilarityResult(const QString& sentence1, const QString& sentence2, double similarity);
    QString _sentence1;
    QString _sentence2;
    double  _similarity;
};

// Communicating with a semantic similarity web service
class SimilarityComparer : public QObject
{
    Q_OBJECT

public:
    void compare(const QString& sentence1, const QString& sentence2);
    static SimilarityComparer* getInstance();

protected:
    QUrl makeUrl(const QString& sentence1, const QString& sentence2) const;
    SimilarityResult parseResult(QNetworkReply* reply);

private slots:
    void onReply(QNetworkReply* reply);

signals:
    // 用来发送语义相似度的结果，value的范围是0~1，1表示完全相同
    void comparisonResult(const SimilarityResult& result);
};

#endif // SIMILARITYCOMPARER_H
