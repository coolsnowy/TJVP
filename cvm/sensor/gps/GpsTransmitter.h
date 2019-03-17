#ifndef _CVM_SENSOR_GPS_GPSTRANSMITTER_H_
#define _CVM_SENSOR_GPS_GPSTRANSMITTER_H_

namespace cvm
{

namespace sensor
{

namespace gps
{

enum GpsTransmitterIdentifier
{
    NetworkGps = 0
};

class GpsTransmitter
{
public:
    GpsTransmitter() {}
    virtual ~GpsTransmitter() {}

    virtual void loop() = 0;

};

}

}
}


#endif // _CVM_SENSOR_GPS_GPSTRANSMITTER_H_
