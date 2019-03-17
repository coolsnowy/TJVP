/**
  * @file NetworkGpsTransmitter.h
  * @brief A specified gps transmitter using network(gpsd)
  */
#ifndef _CVM_SENSOR_GPS_TRANSMITTER_NETWORKGPSTRANSMITTER_H_
#define _CVM_SENSOR_GPS_TRANSMITTER_NETWORKGPSTRANSMITTER_H_

#include <assert.h>
#include <math.h>

#include <gps/gps.h>
#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Channel.h>
#include <cvm/sensor/gps/GpsConfig.h>
#include <cvm/sensor/gps/GpsTransmitter.h>
#include <cvm/protocol/GpsData.hpp>


namespace cvm
{
namespace sensor
{
namespace gps
{

/**
 * @class NetworkGpsTransmitter
 * @brief Getting gps data from gpsd
 *
 */
class NetworkGpsTransmitter : public GpsTransmitter
{

public:
    NetworkGpsTransmitter(const GpsConfig& config);
    ~NetworkGpsTransmitter();

    void loop() override;

private:

    void handleGpsRead();

    GpsConfig _config;

    std::unique_ptr<base::FileLogger> _logger;

    base::EventLoop _loop;
    lcm::LCM _lcm;
    struct gps_data_t _gpsdData;
    protocol::GpsData _cvmData;

    std::unique_ptr<base::Channel> _gpsChannel;
    std::unique_ptr<base::Channel> _lcmChannel;
};


}

}

}

#endif // _CVM_SENSOR_GPS_TRANSMITTER_NETWORKGPSTRANSMITTER_H_
