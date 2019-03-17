/**
 * @file GpsTransmitterFactory.h
 * @brief Factory to produce GpsTransmitter obejct
 */
#ifndef _CVM_SENSOR_GPS_GPSTRANSMITTERFACTORY_H_
#define _CVM_SENSOR_GPS_GPSTRANSMITTERFACTORY_H_

#include <functional>

#include <cvm/base/Factory.h>
#include <cvm/sensor/gps/GpsConfig.h>
#include <cvm/sensor/gps/GpsTransmitter.h>

namespace cvm
{

namespace sensor
{

namespace gps
{

/**
 * @class GpsTransmitterFactory
 * @brief Derived from base::Factory, concrete factory to procude object
 */
class GpsTransmitterFactory : public base::Factory<GpsTransmitterIdentifier,
                                                   GpsTransmitter,
                                                   std::function<GpsTransmitter*(const GpsConfig&)>>
{
public:
    static GpsTransmitterFactory& instance();

private:
    GpsTransmitterFactory();
};

}

}

}

#endif // _CVM_SENSOR_GPS_GPSTRANSMITTERFACTORY_H_
