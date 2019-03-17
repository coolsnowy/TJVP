#include <cvm/sensor/gps/GpsConfig.h>
#include <cvm/sensor/gps/GpsTransmitterFactory.h>
#include <cvm/sensor/gps/GpsTransmitter.h>
#include <cvm/sensor/gps/Gps.h>

namespace cvm
{
namespace sensor
{
namespace gps
{

Gps::Gps(const GpsConfig& config)
{
    GpsTransmitterFactory& gpsTransmitterFactory = GpsTransmitterFactory::instance();
    if (1) {
        _transmitter = gpsTransmitterFactory.createObject(NetworkGps, config);
    }
}

Gps::~Gps()
{
}

void Gps::loop()
{
    _transmitter->loop();
}



}

}

}
