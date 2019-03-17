#include <lcm/lcm-cpp.hpp>

#include <cvm/base/EventLoop.h>
#include <cvm/base/Channel.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/base/Logging.h>
#include <cvm/base/FileLogger.h>
#include <cvm/application/activesafety/ActiveSafetyConfig.h>
#include <cvm/application/activesafety/CollisionDetec.h>
#include <cvm/application/activesafety/ActiveSafety.h>
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


ActiveSafety::ActiveSafety(const ActiveSafetyConfig& config)
    : _loop("activesafety"),
      _config(config)
{
    // Logger
    if (!_config.debug) {
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Info,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush, &*_logger, std::placeholders::_1));
    }else {
        base::Logging::setLogLevel(base::Logging::Debug);
    }

    // Lcm
    if (!_lcm.good()) {
        LDIE << "lcm init error";
    }

    _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB,
                   &ActiveSafety::handleLcmReadThisVehicle, this);
    _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_PUB,
                   &ActiveSafety::handleLcmReadOtherVehicle, this);
    _lcm.subscribe(CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_CTRL,
                   &ActiveSafety::handleLcmReadOtherVehicleCtrl, this);

    _lcmChannel.reset(new base::Channel(&_loop, _lcm.getFileno(), "lcm"));
    _lcmChannel->setReadCallback(std::bind(&lcm::LCM::handle, &_lcm));
    _lcmChannel->enableReading();

    VehsModel.reset(new VehiclesModel(_lcm));
    //pushHmi.reset(new PushHmi(VehsModel));

    _loop.runEvery(100,
                   [&](){ VehsModel->dangerResultFusionAndOutput(); });
//    _loop.runEvery(100,
//                   [&](){ pushHmi->sendUdpToHMI(); });

    LINFO << "Loop start";
}

ActiveSafety::~ActiveSafety()
{
    _lcmChannel->remove();
    LINFO << "Loop end";
}

void ActiveSafety::loop()
{
    _loop.loop();
}


void ActiveSafety::handleLcmReadThisVehicle(const lcm::ReceiveBuffer* rbuf,
                                            const std::string& channel,
                                            const protocol::VehicleData* msg)
{
    assert(channel == CVM_CHANNEL_WORLDMODEL_THIS_VEHICLE_PUB);
    // Add your codes here
    VehsModel->refreshVehicle(*msg, true);
}

void ActiveSafety::handleLcmReadOtherVehicle(const lcm::ReceiveBuffer* rbuf,
                                             const std::string& channel,
                                             const protocol::VehicleData* msg)
{
    assert(channel == CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_PUB);

    // Add your codes here
    VehsModel->refreshVehicle(*msg, false);
}

void ActiveSafety::handleLcmReadOtherVehicleCtrl(const lcm::ReceiveBuffer* rbuf,
                                                 const std::string& channel,
                                                 const protocol::VehicleCtrlData* msg)
{
    assert(channel == CVM_CHANNEL_WORLDMODEL_OTHER_VEHICLE_CTRL);
    // Add your codes here
    VehsModel->removeVehicle(*msg);
}

}

}

}
