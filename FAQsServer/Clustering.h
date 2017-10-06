#ifndef CLUSTERING_H
#define CLUSTERING_H

#include "SimilarityComparer.h"
#include <QVector>
#include <QMap>

class SimilarityComparer;

typedef QStringList Cluster;
typedef QList<QStringList> ClusterList;

class Clustering: public QObject
{
    Q_OBJECT

public:
    virtual ~Clustering();
    virtual void run(const QStringList& sentences) = 0;

signals:
    void clusteringResult(const ClusterList& clusters);
};

class AgglomerativeClustering: public Clustering
{
    Q_OBJECT

public:
    AgglomerativeClustering();
    void run(const QStringList& sentences);

private slots:
    void onSimilarityResult(const SimilarityResult& result);

private:
    void doClustering();

    QPair<Cluster, Cluster> findClosestPair(const ClusterList& clusters);

private:
    SimilarityComparer*         _comparer;
    QMap<QString, int>          _sentences;
    QVector<QVector<double>>    _similarities;
    int                         _resultCount;
};

class StoppingCriteria
{
public:
    virtual ~StoppingCriteria();
    virtual bool shouldStop(const ClusterList& clusters) = 0;
};

class CohesionLessThanCoupling: public StoppingCriteria
{
public:
    bool shouldStop(const ClusterList& clusters);

private:
    double cohesion(const Cluster& cluster);
    double coupling(const ClusterList& clusters);
};

class Linkage
{
public:
    virtual ~Linkage();
    virtual double linkage(const Cluster& cluster1, const Cluster& cluster2) const = 0;
};

class AverageLinkage: public Linkage
{
public:
    double linkage(const Cluster& cluster1, const Cluster& cluster2) const;
};

#endif // CLUSTERING_H
