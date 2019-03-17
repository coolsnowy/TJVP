#ifndef _CVM_SENSOR_CAN_CANTRANSMITTER_H_
#define _CVM_SENSOR_CAN_CANTRANSMITTER_H_

namespace cvm
{

namespace sensor
{

namespace can
{

enum CanTransmitterIdentifier
{
    SocketCan = 0
};

class CanDecoder;

class CanTransmitter
{
public:
    CanTransmitter(CanDecoder* decoder) : _decoder(decoder) {}
    virtual ~CanTransmitter() {}

    virtual void loop() = 0;

protected:
    CanDecoder* _decoder;
};

}

}
}


#endif // _CVM_SENSOR_CAN_CANTRANSMITTER_H_
