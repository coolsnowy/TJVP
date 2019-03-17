/**
  * @file Vehicle.h
  * @brief Implementation of class Vehicle
  */
#ifndef _CVM_WORLDMODEL_VEHICLE_H_
#define _CVM_WORLDMODEL_VEHICLE_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/CountDownLatch.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Timestamp.h>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/BsmData.hpp>
#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/GpsData.hpp>

namespace cvm
{

namespace worldmodel
{
/**
 * @class Vehicle
 * @brief 根据接收到的数据，更新车的信息
 */
class Vehicle : public base::NonCopyable
{
public:
    /**
     * @brief Constructor
     * @param carId Identity of car, should be more than 0
     */
    Vehicle(int32_t carId);

    /**
     * @brief Destructor
     */
    ~Vehicle();

    /**
     * @brief reset expiration
     */
    void resetExpiration()
    {
        _expiration = base::addTime(base::Timestamp::now(),
                                  kVehicleExpireTimeSeconds * 1000 * 1000);
    }

    /**
     * @brief 计算other相对于reference的相对位置，相对航向角
     * @param reference 参考车辆
     * @param other 待转换车辆
     */
    static void transformToRelativeCordination(const Vehicle* reference, Vehicle* other);

    /** 
     * @brief 获取该车超时时间
     * @return 超时时间戳
     */
    base::Timestamp getExpiration() const { return _expiration; }

    /**
     * @brief Get information about this vehicle
     * @return A pointer to this vehicle
     */
    const protocol::VehicleData* getVehicleData() const { return &_vehicleData; }

    /**
     * @brief 根据CAN数据更新车辆信息
     * @param canData 指向CAN数据的指针
     */
    void updateFromCan(const protocol::CanData* canData);

    /**
     * @brief 根据Gps数据更新车辆信息
     * @param gpsData 指向Gps数据的指针
     */
    void updateFromGps(const protocol::GpsData* gpsData);

    /**
     * @brief 根据BSM数据更新车辆信息
     * @param bsmData 指向BSM数据的指针
     */
    void updateFromBsm(const protocol::BsmData* bsmData);

private:

    static void transformToRelativeAzimuth(const Vehicle* reference, Vehicle* other);

    const static int kVehicleExpireTimeSeconds = 2;

    base::Timestamp _expiration;
    protocol::VehicleData _vehicleData;
};

}

}

#endif // _CVM_WORLDMODEL_VEHICLE_H_
