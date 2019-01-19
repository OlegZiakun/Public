#include "dataconnector.h"
#include "datahandler.h"
#include <random>

template <typename T>
struct DataConnector<T>::DataConnectorPrivate
{
    DataConnectorPrivate(DataConnectorObserver &dataConnectorObserver)
        : observer(dataConnectorObserver)
        , dataHandler(std::make_unique<DataHandler<T>>()) {}

    DataConnectorObserver& observer;
    std::unique_ptr <DataHandler<T>> dataHandler;
    std::pair<T, T> nearestPoint;
};

template <typename T>
DataConnector<T>::DataConnector(DataConnectorObserver &dataConnectorObserver)
    : d(std::make_unique<DataConnectorPrivate>(dataConnectorObserver))
{
}

template <typename T>
DataConnector<T>::~DataConnector() = default;

template <typename T>
void DataConnector<T>::requestData(const DataRequest dataRequest, const int areaWidth, const int areaHeight, const int maxResults)
{
    if(loadPointData(dataRequest, areaWidth, areaHeight, maxResults))
    {
        d->observer.pointDataComplete();

        if(loadMapData())
            d->observer.mapDataComplete();
        else
            d->observer.errorOccurred(DataConnectorErrors::LoadMapDataFailed);
    }
    else
        d->observer.errorOccurred(DataConnectorErrors::LoadPointDataFailed);
}

template <typename T>
DataHandler<T>* DataConnector<T>::getDataHandler() const
{
    return d->dataHandler.get();
}

template <typename T>
std::pair<T, T> DataConnector<T>::findNearestPoint(const T x, const T y)
{
    d->nearestPoint = d->dataHandler->findNearestPoint(x, y);
    return d->nearestPoint;
}

/* Load real coordinates data is here. To simulate loading process random values setup.
   Return true on successfully loaded, oherwise return false. */
template <typename T>
bool DataConnector<T>::loadPointData(const DataRequest dataRequest, const int areaWidth, const int areaHeight, const int maxResults)
{
    PointCloud<T> pointCloud;

    pointCloud.points.resize(maxResults);

    for(int i = 0; i < maxResults; ++i)
    {
        pointCloud.points[i].x = std::random_device()() % areaWidth;
        pointCloud.points[i].y = std::random_device()() % areaHeight;
    }

    d->dataHandler->setData(pointCloud);

    return true;
}

/* Load real map data is here.
   Return true on successfully loaded, oherwise return false. */
template <typename T>
bool DataConnector<T>::loadMapData()
{
    //use d->nearestPoint to load necceessary map
    return true;
}

template class DataConnector<float>;
