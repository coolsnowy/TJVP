/**
  * @file VehicleQueue.h
  * @brief VehicleQueue类的定义
  */
#ifndef _CVM_WORLDMODEL_VEHICLEQUEUE_H_
#define _CVM_WORLDMODEL_VEHICLEQUEUE_H_

#include <map>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/CountDownLatch.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Timestamp.h>
#include <cvm/worldmodel/Vehicle.h>

namespace cvm
{

// Forward declaration
namespace protocol
{
class GpsData;
class CanData;
class BsmData;
}

namespace worldmodel
{

/**
 * @class VehicleQueue
 * @brief 管理所有的车辆,并在某车超时之后删除该车信息
 */
class VehicleQueue : public base::NonCopyable
{
public:
    VehicleQueue();
    ~VehicleQueue();

    /**
     * @brief 获取自车数据
     * @return 指向自车数据的指针
     */
    const protocol::VehicleData* getThisVehicleData() const
    { return _thisVehicle.getVehicleData(); }

    /**
     * @brief 根据id获取他车数据
     * @param carId 待获取数据的车辆ID
     * @return 指向某车数据的指针
     */
    const protocol::VehicleData* getOtherVehicleData(int32_t carId) const
    {
        auto it = _vehicles.find(carId);
        assert(it != _vehicles.end());
        return it->second->getVehicleData();
    }

    void updateFromCan(const protocol::CanData* canData)
    { _thisVehicle.updateFromCan(canData); }

    void updateFromGps(const protocol::GpsData* gpsData)
    { _thisVehicle.updateFromGps(gpsData); }

    int32_t updateFromBsm(const protocol::BsmData* bsmData);

    /**
     * @brief 清楚超时车辆
     * @return 返回一个vector，其中的元素是超时车辆的ID
     */
    std::vector<int32_t> clearTimeoutVehicles();

private:

    // std::unique_ptr<Vehicle> should be better!
    std::map<int32_t, Vehicle*> _vehicles;

    Vehicle     _thisVehicle;
};

}

}

#endif // _CVM_WORLDMODEL_VEHICLEQUEUE_H_
