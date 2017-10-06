#include "Clustering.h"
#include "DAO.h"

Clustering::~Clustering() {}

/////////////////////////////////////////////////////////////////////////////////////////
AgglomerativeClustering::AgglomerativeClustering()
{
    _comparer = new SimilarityComparer;
    connect(_comparer, SIGNAL(comparisonResult(SimilarityResult)), this, SLOT(onSimilarityResult(SimilarityResult)));
}

void AgglomerativeClustering::run(const QStringList& sentences)
{
    int n = sentences.size();

    // sentence -> index
    _sentences.clear();
    for (int i = 0; i < n; ++i)
        _sentences.insert(sentences.at(i), i);

    _similarities.fill(QVector<double>(0.0, n), n);  // make a nxn matrix filled with 0.0

    _resultCount = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            _comparer->compare(sentences.at(i), sentences.at(j));
}

void AgglomerativeClustering::onSimilarityResult(const SimilarityResult& result)
{
    int index1 = _sentences[result._sentence1];
    int index2 = _sentences[result._sentence2];
    _similarities[index1][index2] = result._similarity;

    int n = _sentences.size();
    if (++_resultCount == n * (n-1) / 2)    // all similarity comparisons are done
        doClustering();
}

void AgglomerativeClustering::doClustering()
{
    QList<QStringList> clusters;
    foreach (auto sentence, _sentences.keys())
        clusters << (QStringList() << sentence);

    emit clusteringResult(clusters);
}

QPair<Cluster, Cluster> AgglomerativeClustering::findClosestPair(const ClusterList& clusters)
{
    int     first       = 0;
    int     second      = 0;
    double  minDistance = INT64_MAX;

    Linkage* linkage = new AverageLinkage;
    int n = clusters.size();
    for (int i = 0; i < n; i++)
    {
        Cluster cluster1 = clusters.at(i);
        for (int j = i + 1; j < n; j++)
        {
            Cluster cluster2 = clusters.at(j);
            double distance = linkage->linkage(cluster1, cluster2);
            if (distance <= minDistance)
            {
                first       = i;
                second      = j;
                minDistance = distance;
            }
        }
    }
    return QPair<Cluster, Cluster>(clusters.at(first), clusters.at(second));
}

StoppingCriteria::~StoppingCriteria() {}

bool CohesionLessThanCoupling::shouldStop(const ClusterList& clusters)
{
    double coupling = this->coupling(clusters);
    foreach (auto cluster, clusters)
    {
        double cohesion = this->cohesion(cluster);
        if (coupling - cohesion <= 0)
            return true;
    }
    return false;
}

double CohesionLessThanCoupling::cohesion(const Cluster& cluster)
{
    if (cluster.size() == 0)
        return 0.0;

    double  sum     = 0;
    int     count   = 0;
    int     n       = cluster.size();
    for(int i = 0; i < n; ++i)
    {
        QString point1 = cluster.at(i);
        for(int j = i + 1; j < n; ++j)
        {
            QString point2 = cluster.at(j);
            sum += 1 - DAO::getInstance()->getSentenceSimilarity(point1, point2);   // distance
            count ++;
        }
    }
    return sum / count;
}

double CohesionLessThanCoupling::coupling(const ClusterList& clusters)
{
    if (clusters.size() == 0)
        return 0;

    double  sum     = 0;
    int     count   = 0;
    int     n       = clusters.size();

    Linkage* linkage = new AverageLinkage;
    for (int i = 0; i < n; i++)
    {
        Cluster cluster1 = clusters.at(i);
        for (int j = i + 1; j < n; j++)
        {
            Cluster cluster2 = clusters.at(j);
            double distance = linkage->linkage(cluster1, cluster2);
            sum += distance;
            count ++;
        }
    }
    return sum / count;
}

Linkage::~Linkage() {}

double AverageLinkage::linkage(const Cluster &cluster1, const Cluster &cluster2) const
{
    double sum   = 0;
    int    count = 0;
    foreach (auto point1, cluster1)
        foreach (auto point2, cluster2)
        {
            sum += 1 - DAO::getInstance()->getSentenceSimilarity(point1, point2);   // distance
            count ++;
        }
    return count == 0 ? 0 : sum / count;
}
