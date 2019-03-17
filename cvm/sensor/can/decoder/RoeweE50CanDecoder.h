/**
  * @file RoeweE50CanDecoder.h
  * @brief RoeweE50 CAN数据的解码函数
  */
#ifndef _CVM_SENSOR_CAN_CANDECODER_ROEWEE50CANDECODER_H_
#define _CVM_SENSOR_CAN_CANDECODER_ROEWEE50CANDECODER_H_

#include <linux/can.h>

#include <cvm/sensor/can/CanDecoder.h>

namespace cvm
{

namespace protocol
{
class CanData;
}

namespace sensor
{

namespace can
{

/**
 * @class RoeweE50CanDecoder
 * @brief class for decoding roeweE50 can data
 */
class RoeweE50CanDecoder : public CanDecoder
{
public:
    /**
     * @brief function for decoding, override
     * @param canData can data ready to be decoded
     * @param cvmData structure to hold decoded data
     */
    void decode(const struct can_frame& canData, protocol::CanData& cvmData) override;
};

}

}

}

#endif // _CVM_SENSOR_CAN_CANDECODER_ROEWEE50CANDECODER_H_
