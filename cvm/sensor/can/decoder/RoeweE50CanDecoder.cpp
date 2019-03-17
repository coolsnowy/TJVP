#include <linux/can.h>

#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/TurnLight.hpp>
#include <cvm/sensor/can/decoder/RoeweE50CanDecoder.h>
#include <cvm/sensor/can/CanDecoder.h>

namespace cvm
{

namespace sensor
{

namespace can
{

void RoeweE50CanDecoder::decode(const struct can_frame& canData, protocol::CanData& cvmData)
{
    if (canData.can_id == 0x8A) {
        //int vbreak = static_cast<double>(canData.data[0]&0xff;
        //cvmData. = ((double)vbreak)*0.019685;
        //int vacc = static_cast<double>(canData.data[1]&0xff;
        //NewData.AccelerationPedal = ((double)vacc)*0.390625;

//        double speed0 = static_cast<double>(canData.data[0])*256;
//        double speed1 = static_cast<double>(canData.data[1]);
//        cvmData.speed = (speed0+speed1)*0.015625*5/18;
    } else if (canData.can_id == 0xAB) {
        int vspeed1 = static_cast<double>(canData.data[3]&0xff);
        int vspeed2 = static_cast<double>(canData.data[2]&0xff)*256;
        cvmData.speed = ((double)(vspeed1+vspeed2))*0.01 / 3.6; // Conv km/h to m/s

//        double wheelAngle0 = static_cast<double>(canData.data[1])*256;
//        double wheelAngle1 = static_cast<double>(canData.data[2]);
//        double wheelAngle = (wheelAngle0+wheelAngle1)*0.0625;
//        if (wheelAngle > 2048) {
//            wheelAngle = wheelAngle-4095.9375;
//        }
//        cvmData.steeringWheelAngle = -wheelAngle / 13;
    } else if (canData.can_id == 0x18B) {
        int vwheel1 = static_cast<double>(canData.data[0]&0xff)*256;
        int vwheel2 = static_cast<double>(canData.data[1]&0xff);
        //double ret = ((double)(vwheel1+vwheel2))*0.1-3277;
               //if(qAbs(ret-OldData.WheelAngle)<200 || OldData.WheelAngle == 0)
        cvmData.steeringWheelAngle = (((double)(vwheel1+vwheel2))*0.1-3277)/13;
//        int turnLight = canData.data[2]&0xc;
//        if(turnLight == 4){
//            cvmData.turnLight = protocol::TurnLight::TurnLeft;
//        }else if(turnLight == 8){
//            cvmData.turnLight = protocol::TurnLight::TurnRight;
//        }else{
//            cvmData.turnLight = protocol::TurnLight::TurnNone;
//        }
    }
}

}

}

}
