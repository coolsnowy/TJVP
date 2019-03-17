/**
  * @file WorldModel.h
  * @brief WorldModel类的定义
  */
#ifndef _CVM_WORLDMODEL_WORLMODEL_H_
#define _CVM_WORLDMODEL_WORLMODEL_H_

#include <map>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/CountDownLatch.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/worldmodel/IntersectionQueue.h>
#include <cvm/worldmodel/VehicleQueue.h>
#include <cvm/worldmodel/WorldModelConfig.h>

/**
 * @namespace cvm::sensor::worldmodel
 * @brief cvm::sensor::worldmodel
 */
namespace cvm
{

namespace protocol
{
class GpsData;
class CanData;
class BsmData;
class MapData;
class SpatData;
class IntersectionData;
}

namespace worldmodel
{

/**
 * @class WorldModel
 * @brief 管理所有感知到的真实世界中的对象，并向上层提供信息
 */
class WorldModel : public base::NonCopyable
{
public:
    WorldModel(const WorldModelConfig& config);
    ~WorldModel();

    void loop();

private:

    void handleLcmReadGps(const lcm::ReceiveBuffer* rbuf,
                          const std::string& channel, const protocol::GpsData *msg);

    void handleLcmReadCan(const lcm::ReceiveBuffer* rbuf,
                          const std::string& channel, const protocol::CanData *msg);

    void handleLcmReadBsm(const lcm::ReceiveBuffer* rbuf,
                          const std::string& channel, const protocol::BsmData* msg);

    void handleLcmReadMap(const lcm::ReceiveBuffer* rbuf,
                          const std::string& channel, const protocol::MapData* msg);

    void handleLcmReadSpat(const lcm::ReceiveBuffer* rbuf,
                           const std::string& channel, const protocol::SpatData* msg);

    void clearExpiredItems();

    void sendBsm();

    WorldModelConfig _config;

    std::unique_ptr<base::FileLogger> _logger;
    base::EventLoop _loop;

    lcm::LCM _lcm;
    std::unique_ptr<base::Channel> _lcmChannel;

    VehicleQueue _vehicles;
    IntersectionQueue _intersections;
};

}

}

#endif // _CVM_WORLDMODEL_WORLMODEL_H_
