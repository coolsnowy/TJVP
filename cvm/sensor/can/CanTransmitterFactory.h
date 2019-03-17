#ifndef _CVM_SENSOR_CAN_CANTRANSMITTERFACTORY_H_
#define _CVM_SENSOR_CAN_CANTRANSMITTERFACTORY_H_

#include <functional>

#include <cvm/base/Factory.h>
#include <cvm/sensor/can/CanConfig.h>
#include <cvm/sensor/can/CanTransmitter.h>

namespace cvm
{

namespace sensor
{

namespace can
{
class CanTransmitterFactory : public base::Factory<CanTransmitterIdentifier,
                                                   CanTransmitter,
                                                   std::function<CanTransmitter*(const CanConfig&, CanDecoder*)>>
{
public:
    static CanTransmitterFactory& instance();

private:
    CanTransmitterFactory();
};

}

}

}

#endif // _CVM_SENSOR_CAN_CANTRANSMITTERFACTORY_H_
