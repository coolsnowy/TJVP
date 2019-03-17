/**
  * @file Gps.h
  * @brief Gps类的定义
  */
#ifndef _CVM_SENSOR_GPS_GPS_H_
#define _CVM_SENSOR_GPS_GPS_H_

#include <memory>

#include <cvm/base/NonCopyable.h>

/**
 * @namespace cvm::sensor::gps
 * @brief cvm::sensor::gps
 */
namespace cvm
{
namespace sensor
{
namespace gps
{

class GpsTransmitter;
struct GpsConfig;

/**
 * @class Gps
 * @brief User Interface for gps
 */
class Gps : public base::NonCopyable
{

public:
    Gps(const GpsConfig& config);
    ~Gps();

    void loop();

private:

    std::unique_ptr<GpsTransmitter> _transmitter;
};


}

}

}

#endif // _CVM_SENSOR_GPS_GPSD_H_
