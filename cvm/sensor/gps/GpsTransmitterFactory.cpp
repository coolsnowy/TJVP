#include <cvm/base/Factory.h>
#include <cvm/sensor/gps/GpsTransmitterFactory.h>
#include <cvm/sensor/gps/transmitter/NetworkGpsTransmitter.h>

namespace cvm
{

namespace sensor
{

namespace gps
{

GpsTransmitterFactory& GpsTransmitterFactory::instance()
{
    static GpsTransmitterFactory gpsTransmitterFactory;
    return gpsTransmitterFactory;
}

GpsTransmitterFactory::GpsTransmitterFactory()
{
    regist(NetworkGps, [](const GpsConfig& config)
                        { return new NetworkGpsTransmitter(config); });
}

}

}

}
