#pragma once

#include "datahandler.h"
#include <memory>

enum class DataConnectorErrors { LoadPointDataFailed, LoadMapDataFailed /*etc*/ };
enum class DataRequest { Restaurant/*etc*/ };

class DataConnectorObserver
{
  public:
      virtual void pointDataComplete() = 0;
      virtual void mapDataComplete() = 0;
      virtual void errorOccurred(DataConnectorErrors e) = 0;
};

template <typename T>
class DataConnector
{
public:
    explicit DataConnector(DataConnectorObserver& dataConnectorObserver);
    ~DataConnector();

public:
    void requestData(const DataRequest dataRequest, const int areaWidth, const int areaHeight, const int maxResults);
    DataHandler<T>* getDataHandler() const;
    std::pair<T, T> findNearestPoint (const T x, const T y);

private:
    bool loadPointData(const DataRequest dataRequest, const int areaWidth, const int areaHeight, const int maxResults);
    bool loadMapData();

private:
    struct DataConnectorPrivate;
    std::unique_ptr <DataConnectorPrivate> d;
};
