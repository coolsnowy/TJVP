/**
 * @file  SpeedGuidance.h
 * @brief  SpeedGuidance
 */

#ifndef _CVM_APPLICATION_SPEEDGUIDANCE_SPEEDGUIDANCE_H_
#define _CVM_APPLICATION_SPEEDGUIDANCE_SPEEDGUIDANCE_H_

#include <lcm/lcm-cpp.hpp>
#include <vector>
#include <iostream>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/base/FileLogger.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/IntersectionData.hpp>
#include <cvm/protocol/HmiEventData.hpp>
#include <cvm/protocol/Lane.hpp>
#include <cvm/protocol/HmiRoadData.hpp>
#include <cvm/protocol/VehicleData.hpp>

#include <cvm/application/speedguidance/SpeedGuidanceConfig.h>
#include <cvm/application/speedguidance/ComputeTools.h>


namespace cvm {

namespace application {

namespace speedguidance {

typedef std::shared_ptr<protocol::VehicleData>  VehiclePtr;
class SpeedGuidance : public base::NonCopyable
{

public:
    SpeedGuidance(const SpeedGuidanceConfig&  config);
    ~SpeedGuidance();

    void loop();

private:
    void handleLcmReadSPAT(const lcm::ReceiveBuffer* rbuf,
                              const std::string& channel,
                              const protocol::IntersectionData *msg);
    void handleLcmReadThisVehicle(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel,
                                  const protocol::VehicleData *msg);

    void choose_light();
    void cal_adv_speed();


    VehiclePtr this_vehicle;

    std::vector<protocol::IntersectionData> Intersections_;
    protocol::Lane  drive_lane;
    VectorPP   Inter_position;
    double dis_car_inter;


    SpeedGuidanceConfig _config;
    base::EventLoop _loop;
    lcm::LCM _lcm;
    std::unique_ptr<base::Channel>  _lcmChannel;
    std::unique_ptr<base::FileLogger> _logger;


};



}

}

}

#endif








