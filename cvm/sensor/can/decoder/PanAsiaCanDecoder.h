/**
  * @file PanAsiaCanDecoder.h
  * @brief PanAsia CAN数据的解码函数
  */
#ifndef _CVM_SENSOR_CAN_CANDECODER_PANASIACANDECODER_H_
#define _CVM_SENSOR_CAN_CANDECODER_PANASIACANDECODER_H_

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
 * @class PanAsiaCanDecoder
 * @brief class for decoding panasian can data
 */
class PanAsiaCanDecoder : public CanDecoder
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

#endif // _CVM_SENSOR_CAN_CANDECODER_PANASIACANDECODER_H_
