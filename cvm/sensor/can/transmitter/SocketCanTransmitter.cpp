#include <assert.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <math.h>

#include <map>
#include <functional>
#include <queue>

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/Channel.h>
#include <cvm/base/Logging.h>
#include <cvm/sensor/can/Can.h>
#include <cvm/sensor/can/CanConfig.h>
#include <cvm/sensor/can/CanDecoder.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/CanCtrlData.hpp>
#include <cvm/protocol/TurnLight.hpp>
#include <cvm/sensor/can/transmitter/SocketCanTransmitter.h>

namespace cvm
{

namespace sensor
{

namespace can
{

SocketCanTransmitter::SocketCanTransmitter(const CanConfig &config, CanDecoder* decoder)
    : CanTransmitter(decoder),
      _loop("can"),
      _config(config)
{
    // Logger
    if (_config.debug) {
        base::Logging::setLogLevel(base::Logging::Debug);
    }else {
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Debug,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush, &*_logger, std::placeholders::_1));
    }

    LINFO << "Loop start";

    // Lcm
    if (!_lcm.good()) {
        LDIE << "lcm init error";
    }

    _lcm.subscribe(CVM_CHANNEL_CAN_CTRL, &SocketCanTransmitter::handleLcmRead, this);
    _lcmChannel.reset(new base::Channel(&_loop, _lcm.getFileno(), "lcm"));
    _lcmChannel->setReadCallback(std::bind(&lcm::LCM::handle, &_lcm));
    if (_config.canPublishIntervalMilisecond > 0) {
        _loop.runEvery(_config.canPublishIntervalMilisecond,
                       [&](){ _lcm.publish(CVM_CHANNEL_CAN_PUB, &_cvmData); });
    }
    _lcmChannel->enableReading();

    // Can
    _cvmData.acceleration = 0;
    _cvmData.turnLight = protocol::TurnLight::TurnNone;
    _cvmData.speed = 0;
    _cvmData.steeringWheelAngle = 0;

    _canFd = ::socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (_canFd < 0) {
        LDIE << "can init error";
    }

    struct ifreq ifr;
    strcpy(ifr.ifr_name, _config.canInterfaceName.data());
    if (ioctl(_canFd, SIOCGIFINDEX, &ifr) < 0) {
        LDIE << "ioctl can fd error";
    }

    // Set index to 0, ie. ANY device
    struct sockaddr_can addr;
    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    int ret = bind(_canFd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret) {
        LDIE << "can bind error";
    }

    _canChannel.reset(new base::Channel(&_loop, _canFd, "can"));
    _canChannel->setReadCallback(std::bind(&SocketCanTransmitter::handleCanRead, this));
    _canChannel->enableReading();

    // can ctrl
    _loop.runEvery(_config.canCtrlSendIntervalMilisecond,
                   std::bind(&SocketCanTransmitter::sendCanData, this));
}

SocketCanTransmitter::~SocketCanTransmitter()
{
    _lcmChannel->remove();
    _canChannel->remove();
    ::close(_canFd);

    LINFO << "Loop end";
}

void SocketCanTransmitter::loop()
{
    _loop.loop();
}

void SocketCanTransmitter::sendCanData()
{
    if (!_canCtrlData.empty()) {
        struct can_frame data = _canCtrlData.front();
        _canCtrlData.pop();
        ::write(_canFd, &data, sizeof(data));
    }
}

void SocketCanTransmitter::handleLcmRead(const lcm::ReceiveBuffer* rbuf,
                        const std::string& channel,
                        const protocol::CanCtrlData* msg)
{
    struct can_frame canData;
    canData.can_id = msg->id;
    canData.can_dlc = msg->length;
    memcpy(canData.data, msg->data, canData.can_dlc);

    if (_canCtrlData.size() >= s_maxCanCtrlDataQueue) {
        _canCtrlData.pop();
        LWARN << "Too many can ctrl data";
    }
    _canCtrlData.push(canData);
}

void SocketCanTransmitter::handleCanRead()
{
    size_t bytes = read(_canFd, &_canData, sizeof(struct can_frame));
    if (bytes != sizeof(struct can_frame)) {
        LWARN << "read bytes != sizeof(struct can_frame)";
    }else {
        _decoder->decode(_canData, _cvmData);
    }

    if (_config.canPublishIntervalMilisecond <= 0) {
        int retval = _lcm.publish(CVM_CHANNEL_CAN_PUB, &_cvmData);
        (void)retval;
    }
}

const int SocketCanTransmitter::s_maxCanCtrlDataQueue = 32;

}

}

}

