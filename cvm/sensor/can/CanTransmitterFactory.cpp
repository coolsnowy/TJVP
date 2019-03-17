#include <cvm/base/Factory.h>
#include <cvm/sensor/can/CanTransmitterFactory.h>
#include <cvm/sensor/can/transmitter/SocketCanTransmitter.h>

namespace cvm
{

namespace sensor
{

namespace can
{

CanTransmitterFactory& CanTransmitterFactory::instance()
{
    static CanTransmitterFactory canTransmitterFactory;
    return canTransmitterFactory;
}

CanTransmitterFactory::CanTransmitterFactory()
{
    regist(SocketCan, [](const CanConfig& config, CanDecoder* decoder)
                        { return new SocketCanTransmitter(config, decoder); });
}

}

}

}
