#pragma once

#include <vector>

template <typename T>
class PointCloud
{
public:
    struct Point { T  x, y; };

    using PointVector = std::vector<Point>;

    void clear()
    {
        points.clear();
    }

    size_t kdtree_get_point_count() const
    {
        return points.size();
    }

    T kdtree_get_pt(const size_t idx, const int dim = 0) const
    {
        return (dim == 0) ? points[idx].x : points[idx].y;
    }

    PointVector getPoints() const
    {
        return points;
    }

    template <class BBOX> bool kdtree_get_bbox(BBOX&) const
    {
        return false;
    }

    PointVector points;
};
