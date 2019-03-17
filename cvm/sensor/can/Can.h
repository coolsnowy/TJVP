/**
  * @file Can.h
  * @brief Can类的实现
  */
#ifndef _CVM_SENSOR_CAN_CAN_H_
#define _CVM_SENSOR_CAN_CAN_H_

#include <memory>

#include <cvm/base/NonCopyable.h>
#include <cvm/sensor/can/CanConfig.h>

/**
 * @namespace cvm::sensor::cvm
 * @brief cvm::sensor::cvm
 */
namespace cvm
{

namespace sensor
{

namespace can
{

class CanTransmitter;
class CanDecoder;

/**
 * @class Can
 * @brief 从硬件设备获取Can数据，或从高层应用接收can的控制数据
 *
 * 使用SocketCAN读取底层CAN数据，并在CVM_CHANNEL_CAN_PUB这个通道中广播数据
 * 在通道CVM_CAHNNEL_CAN_CTRL接收到上层的控制数据后，先缓存在队列中，然后定时使用SocketCAN向底层写入数据
 *
 */

class Can : public base::NonCopyable
{
public:

    Can(const CanConfig& config);
    ~Can();

    void loop();

private:
    std::unique_ptr<CanTransmitter> _transmitter;
    std::unique_ptr<CanDecoder> _decoder;

};

}

}

}

#endif // _CVM_SENSOR_CAN_CAN_H_
