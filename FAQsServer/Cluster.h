//#ifndef CLUSTER_H
//#define CLUSTER_H

//#include <QList>


//template <typename T>
//class Cluster
//{
//public:
//    virtual ~Cluster();
//    virtual QList<T>            getDataPoints()  const = 0;
//    virtual QList<Cluster<T>>   getSubclusters() const = 0;
//};

//template <typename T>
//class SingleCluster: public Cluster<T>
//{
//public:
//    SingleCluster(const T& dataPoint) {
//        _dataPoints << dataPoint;
//    }

//    SingleCluster(const QList<T>& dataPoints) {
//        _dataPoints << dataPoints;
//    }

//    QList<T> getDataPoints()  const  {
//        return _dataPoints;
//    }

//    QList<Cluster<T>> getSubclusters() const {
//        return QList<Cluster<T>>();
//    }

//private:
//    QList<T> _dataPoints;
//};

//template <typename T>
//class SuperCluster: public Cluster<T>
//{
//public:
//    SuperCluster(const Cluster<T>& cluster1, const Cluster<T>& cluster2) {
//        _subClusters << cluster1 << cluster2;
//    }

//    QList<T> getDataPoints()  const
//    {
//        QList<T> result;
////        foreach (auto subCluster, _subClusters)
//        return result;
//    }

//    QList<Cluster<T>> getSubclusters() const {
//        return _subClusters;
//    }

//private:
//    QList<Cluster<T>> _subClusters;
//};

//#endif // CLUSTER_H
