#pragma once

#include "nanoflann.hpp"
#include "pointcloud.h"

template <typename T>
class DataHandler
{
public:
    using PointCloudType = PointCloud<T>;
    using PointCloudVector = std::vector<typename PointCloudType::Point>;

public:
    std::pair<T, T> findNearestPoint (const T x, const T y)
    {
        const T query[] = { x, y };
        const int pointsCount = sizeof(query) / sizeof(T);

        using AdaptorType = nanoflann::L2_Simple_Adaptor<T, PointCloudType>;
        using KdTree = nanoflann::KDTreeSingleIndexAdaptor<AdaptorType, PointCloudType, pointsCount>;

        KdTree index(pointsCount, pointCloud, nanoflann::KDTreeSingleIndexAdaptorParams(10 /* max leaf */) ); // construct a kd-tree index

        index.buildIndex();

        size_t retIndex;
        nanoflann::KNNResultSet<T> resultSet(1);
        auto getIndex = [&retIndex, this] (const int index) -> int { return pointCloud.kdtree_get_pt(retIndex, index); };

        resultSet.init(&retIndex, &distanse);
        index.findNeighbors(resultSet, &query[0], nanoflann::SearchParams());

        distanse = sqrt(distanse);

        return std::pair<T, T>(getIndex(0), getIndex(1));
    }

    void setData(const PointCloudType& pointCloud)
    {
        this->pointCloud = pointCloud;
    }

    PointCloudVector getPoints() const
    {
        return pointCloud.points;
    }

    T getDistance() const
    {
        return distanse;
    }

private:
    PointCloudType pointCloud;
    T distanse = 0;
};


