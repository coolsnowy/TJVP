/**
  * @file CanDecode.h
  * @brief Decoding can data
  */
#ifndef _CVM_SENSOR_CAN_CANDECODER_H_
#define _CVM_SENSOR_CAN_CANDECODER_H_

#include <linux/can.h>

#include <cvm/protocol/CanData.hpp>

namespace cvm
{

namespace sensor
{

namespace can
{

enum CanDecoderIdentifier
{
    RoeweE50 = 1,
    PanAsia,
    Baic
};

/**
 * @class CanDecoder
 * @brief Base class for decoding can data
 */
class CanDecoder
{
public:
    CanDecoder() {}
    ~CanDecoder() {}
    /**
     * @brief virtual function for decoding
     * @param canData can data ready to be decoded
     * @param cvmData structure to hold decoded data
     */
    virtual void decode(const struct can_frame& canData, protocol::CanData& cvmData) = 0;
};

}

}

}

#endif // _CVM_SENSOR_CAN_CANDECODER_H_
