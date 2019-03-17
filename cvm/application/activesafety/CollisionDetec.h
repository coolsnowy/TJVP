/**
  * @file collisiondetec.h
  * @brief 定义了Vehicle类和VehiclesModel类
  */
#ifndef COLLISIONDETEC_H
#define COLLISIONDETEC_H

#include <vector>
#include <map>
#include <set>
#include <memory>

#include <lcm/lcm-cpp.hpp>
#include <cvm/base/Channel.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/VehicleCtrlData.hpp>
#include <cvm/base/NonCopyable.h>
#include <cvm/protocol/HmiVehicleData.hpp>
#include <cvm/protocol/HmiWarnData.hpp>
#include <cvm/protocol/HmiEventData.hpp>

#include <cvm/application/activesafety/ActiveSafetyConfig.h>
#include <cvm/application/activesafety/ComputeTools.h>

namespace cvm
{

namespace application
{

namespace activesafety
{

class PushHmi;

/**
 * @class Vehicle类
 * @brief 该类存储单个车辆数据，包含了对车辆进行轨迹预测的函数
 */
class Vehicle
{
public:
    /**
     * @param VehicleData 通信中获取的车辆数据
     * @brief 将通信中获取的单个车辆数据转换为Vehicle类
     */
    explicit Vehicle(const protocol::VehicleData &);

    int id;
    double longitude;
    double latitude;
    double altitude;
    double speed;
    double heading;

    double wheelAngle;

    point relativePoint;
    double relativeHeading;

    double vehicleWidth;
    double vehicleLength;
    double vehicleWheelDis;

    VEHICLE_TURN_LIGHT turnLight;

    std::vector<point> prePath;

public:
    /**
     * @brief 根据车辆数据预测车辆的轨迹
     */
    void calPrePath();
};


/// ----------------------------- split line -------------------------------


typedef std::shared_ptr<Vehicle> VehiclePtr;

/**
 * @class VehicleModel类
 * @brief 该类存储了周围车辆的集合，包含了车辆预警判断的函数
 */
class VehiclesModel : public base::NonCopyable
{
    friend class PushHmi;
    friend class PushCan;
public:
    explicit VehiclesModel(lcm::LCM &lcm);

    /**
     * @brief 根据参数isHost选择刷新自车或他车数据
     * @param vdata 通信中的车辆数据
     * @param isHost 是否为自车
     */
    void refreshVehicle(const protocol::VehicleData &vdata, bool isHost);
    /**
     * @brief 根据车辆控制指令删除相应的车辆数据
     * @param vdata 车辆控制指令
     */
    void removeVehicle(const protocol::VehicleCtrlData &vdata);
    /**
     * @brief 融合预警判断，并输出判断结果
     */
    void dangerResultFusionAndOutput();

private:
    /**
     * @brief 单个车辆宫格检测函数
     * @param HV 自车数据
     * @param OV 他车数据
     */
    void sixGridsDetect(const Vehicle &HV, const Vehicle &OV);
    /**
     * @brief 单个车辆危险检测函数
     */
    void vehicleDangerDetection();
    /**
     * @brief 日志结果输出（控制台）
     */
    void log_result();

    /// detect results living time count
    unsigned int liveTimeCount;

    /// lcm object
    lcm::LCM &lcm_;

    VehiclePtr host_vehicle_;
    std::map<int, VehiclePtr> vehicles_; // other vehicles

    std::map<WARN_PRIO, detectResult> detect_results_;

    /// vehicle status of six grids
    std::map<VEHICLE_LOC, std::map<VEHICLE_STATUS, int> > six_grids_state_;

};

}

}

}


#endif // COLLISIONDETEC_H
