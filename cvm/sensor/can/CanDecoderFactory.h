/**
 * @file CanDecoderFactory.h
 * @brief Factory to produce CanDecoder according to CanDecoderIdentifier
 */
#ifndef _CVM_SENSOR_CAN_CANDECODERFACTORY_H_
#define _CVM_SENSOR_CAN_CANDECODERFACTORY_H_

#include <functional>

#include <cvm/base/Factory.h>
#include <cvm/sensor/can/CanDecoder.h>

namespace cvm
{

namespace sensor
{

namespace can
{

class CanDecoderFactory : public base::Factory<CanDecoderIdentifier,
                                               CanDecoder,
                                               std::function<CanDecoder*()>>
{
public:
    static CanDecoderFactory& instance();

private:
    CanDecoderFactory();
};

}

}

}

#endif // _CVM_SENSOR_CAN_CANDECODERFACTORY_H_
