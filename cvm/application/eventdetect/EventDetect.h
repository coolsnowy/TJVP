/**
 * @file EventDetect
 * @brief detect event warnings
 */

#ifndef _CVM_APPLICATION_EVENTDETECT_EVENTDETECT_H_
#define _CVM_APPLICATION_EVENTDETECT_EVENETDETCT_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/base/FileLogger.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/VehicleData.hpp>
#include <cvm/protocol/HmiEventData.hpp>

#include <cvm/application/eventdetect/EventDetectConfig.h>
#include <cvm/application/eventdetect/ComputeTools.h>

namespace cvm {

namespace application {

namespace eventdetect {

class EventDetect:public base::NonCopyable
{
public:
    EventDetect(const EventDetectConfig & config);
    ~EventDetect();

    void loop();

private:

    void handleLcmReadThisVehicle(const lcm::ReceiveBuffer* rbuf,
                                  const std::string& channel,
                                  const protocol::VehicleData* msg);
    void detect_event();

    std::shared_ptr<protocol::VehicleData>  this_vehicle;

    EventDetectConfig _config;
    base::EventLoop _loop;
    lcm::LCM _lcm;
    std::unique_ptr<base::Channel>  _lcmChannel;
    std::unique_ptr<base::FileLogger> _logger;

};

}

}

}



#endif
