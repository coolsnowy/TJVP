/**
 * @file ActiveSafety.h
 * @brief ActiveSafety的实现，主动安全应用的入口
 */
#ifndef _CVM_APPLICATION_ACTIVESAFETY_ACTIVESAFETY_H_
#define _CVM_APPLICATION_ACTIVESAFETY_ACTIVESAFETY_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/base/FileLogger.h>
#include <cvm/application/activesafety/ActiveSafetyConfig.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/VehicleCtrlData.hpp>
#include <cvm/application/activesafety/PushHMI.h>

namespace cvm
{

namespace application
{

namespace activesafety
{

class ActiveSafety : public base::NonCopyable
{

public:
    ActiveSafety(const ActiveSafetyConfig& config);
    ~ActiveSafety();

    void loop();

private:

    void handleLcmReadThisVehicle(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel,
                                  const protocol::VehicleData* msg);

    void handleLcmReadOtherVehicle(const lcm::ReceiveBuffer* rbuf,
                                   const std::string& channel,
                                   const protocol::VehicleData* msg);

    void handleLcmReadOtherVehicleCtrl(const lcm::ReceiveBuffer* rbuf,
                                       const std::string& channel,
                                       const protocol::VehicleCtrlData* msg);

    ActiveSafetyConfig _config;

    base::EventLoop _loop;
    lcm::LCM _lcm;
    std::unique_ptr<base::Channel> _lcmChannel;
    std::unique_ptr<base::FileLogger> _logger;

    // Add your data structures here
    std::shared_ptr<VehiclesModel> VehsModel;
//    std::unique_ptr<PushHmi> pushHmi;
};

}

}

}


#endif // _CVM_APPLICATION_ACTIVESAFETY_ACTIVESAFETY_H_
