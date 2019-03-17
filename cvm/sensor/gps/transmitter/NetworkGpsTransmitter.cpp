#include <assert.h>
#include <math.h>

#include <gps/gps.h>
#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/base/EventLoop.h>
#include <cvm/base/Logging.h>
#include <cvm/base/Timestamp.h>
#include <cvm/base/Channel.h>
#include <cvm/base/Logging.h>
#include <cvm/sensor/gps/GpsConfig.h>
#include <cvm/sensor/gps/transmitter/NetworkGpsTransmitter.h>
#include <cvm/protocol/ProtocolChannel.h>
#include <cvm/protocol/GpsData.hpp>

namespace cvm
{
namespace sensor
{
namespace gps
{

NetworkGpsTransmitter::NetworkGpsTransmitter(const GpsConfig& config)
    : _loop("gpsd"),
      _config(config)
{
    // Logger
    if (_config.debug) {
        base::Logging::setLogLevel(base::Logging::Debug);
    }else {
        _logger.reset(new base::FileLogger(2, false, _config.logPath));
        base::Logging::initLogging(base::Logging::Debug,
                                   std::bind(&base::FileLogger::log, &*_logger, std::placeholders::_1, std::placeholders::_2),
                                   std::bind(&base::FileLogger::flush, &*_logger, std::placeholders::_1));

    }

    LINFO << "Loop start";

    // Lcm
    if (!_lcm.good()) {
        LDIE << "lcm init error";
    }
    _lcmChannel.reset(new base::Channel(&_loop, _lcm.getFileno(), "lcm"));

    // Gps
    if(::gps_open(_config.gpsdServerIp.data(), _config.gpsdServerPort.data(), &_gpsdData) != 0) {
        LDIE << "gps open error";
    }
    ::gps_stream(&_gpsdData, WATCH_ENABLE, nullptr);
    _gpsChannel.reset(new base::Channel(&_loop, _gpsdData.gps_fd, "gps"));
    _gpsChannel->setReadCallback(std::bind(&NetworkGpsTransmitter::handleGpsRead, this));
    _gpsChannel->enableReading();

    // Gps Data
    _cvmData.location.latitude  = 0;
    _cvmData.location.longitude = 0;
    _cvmData.location.altitude  = 0;
    _cvmData.speed     = 0;
    _cvmData.quality   = 0;
    _cvmData.satelliteNumber = 0;
    _cvmData.azimuth   = 0;

}

NetworkGpsTransmitter::~NetworkGpsTransmitter()
{
    _lcmChannel->remove();
    _gpsChannel->remove();
    ::gps_close(&_gpsdData);

    LINFO << "Loop end";
}

void NetworkGpsTransmitter::loop()
{
    _loop.loop();
}

void NetworkGpsTransmitter::handleGpsRead()
{
    int ret = ::gps_read(&_gpsdData);
    if (ret < 0) {
        LDIE << "Gps read error";
    }
    if(!::isnan(_gpsdData.fix.latitude)) {
        _cvmData.location.latitude  = _gpsdData.fix.latitude;
        _cvmData.location.longitude = _gpsdData.fix.longitude;
        _cvmData.location.altitude  = _gpsdData.fix.altitude;
        _cvmData.speed     = _gpsdData.fix.speed;
        _cvmData.quality   = _gpsdData.status;
        _cvmData.satelliteNumber = _gpsdData.satellites_used;

        // Keep azimuth if vehicle suddenly stops
        if (_gpsdData.fix.track != 0) {
            _cvmData.azimuth   = _gpsdData.fix.track;
        }
        int retval = _lcm.publish(CVM_CHANNEL_GPS_PUB, &_cvmData);
        (void)retval;
    }

}



}

}

}
