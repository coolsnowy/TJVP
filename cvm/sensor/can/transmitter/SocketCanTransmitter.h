#ifndef _CVM_SENSOR_CAN_SOCKETCANTRANSMITTER_H_
#define _CVM_SENSOR_CAN_SOCKETCANTRANSMITTER_H_

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
#include <cvm/sensor/can/CanConfig.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/CanCtrlData.hpp>
#include <cvm/protocol/TurnLight.hpp>
#include <cvm/sensor/can/CanTransmitter.h>

namespace cvm
{

namespace sensor
{

namespace can
{

class SocketCanTransmitter : public CanTransmitter
{
public:
    SocketCanTransmitter(const CanConfig& config, CanDecoder* decoder);
    ~SocketCanTransmitter();

    void loop() override;

private:
    void sendCanData();

    void handleLcmRead(const lcm::ReceiveBuffer* rbuf,
                       const std::string& channel,
                       const protocol::CanCtrlData* msg);

    void handleCanRead();

    CanConfig _config;

    std::unique_ptr<base::FileLogger> _logger;

    base::EventLoop _loop;
    lcm::LCM _lcm;

    struct can_frame _canData;
    protocol::CanData _cvmData;
    std::queue<struct can_frame> _canCtrlData;
    static const int s_maxCanCtrlDataQueue;

    int _canFd;
    std::unique_ptr<base::Channel> _canChannel;
    std::unique_ptr<base::Channel> _lcmChannel;
};

}

}
}

#endif // _CVM_SENSOR_CAN_SOCKETCANTRANSMITTER_H_
