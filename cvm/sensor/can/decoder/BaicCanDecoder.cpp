#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/TurnLight.hpp>
#include <cvm/sensor/can/decoder/BaicCanDecoder.h>
#include <cvm/sensor/can/CanDecoder.h>
#include <math.h>

namespace cvm
{

namespace sensor
{

namespace can
{

void BaicCanDecoder::decode(const struct can_frame& canData, protocol::CanData& cvmData)
{
    if (canData.can_id == 0x120) {
        //        int ESP_operator = ((frame.data[0]&0x10)>>4);
        //        int ABS_operator = ((frame.data[0]&0x40)>>6);
    }
    else if (canData.can_id == 0x3F0) {
//        double LonAcc = static_cast<double>(frame.data[1]);
//        data.Longitudinal_acc = LonAcc*0.2 - 25.0;
        double LatAcc = static_cast<double>(canData.data[3]);
//        data.Lateral_acc = LatAcc*0.2 -25.0;

        cvmData.acceleration = LatAcc*0.2 -25.0;
    }
    else if (canData.can_id == 0x3A0) {
        double Speed1 = static_cast<double>(canData.data[3])*256;
        double Speed2 = static_cast<double>(canData.data[4]);
        cvmData.speed = ((Speed1+Speed2)*0.1)*5/18;
        //        data.Speed_valid = ((frame.data[0]&0xC)>>2);
    }
    else if (canData.can_id == 0x280) {
        //        data.Brake_valid = ((frame.data[0]&0x8)>>3);
        //        data.Brake_switch = ((frame.data[2]&0x2)>>1);
    }
    else if (canData.can_id == 0x4A0) {
        int Turning_lamp_switch = canData.data[0]&0x3;
        if(Turning_lamp_switch == 1)
        {
            cvmData.turnLight = protocol::TurnLight::TurnLeft;
        }
        else if(Turning_lamp_switch == 2)
        {
            cvmData.turnLight = protocol::TurnLight::TurnRight;
        }
        else if(Turning_lamp_switch == 0)
        {
            cvmData.turnLight = protocol::TurnLight::TurnNone;
        }

        //        data.Turn_bulb_failure_right = ((frame.data[5]&0x8)>>3);
        //        data.Turn_bulb_failure_left = ((frame.data[5]&0x10)>>4);
        //        data.Brake_light = ((frame.data[5]&0x80)>>7);
        //        data.Brake_auxiliary_light = ((frame.data[7]&0x80)>>7);
    }
    else if (canData.can_id == 0x180) {
        double Angle1 = static_cast<double>(canData.data[3])*256;
        double Angle2 = static_cast<double>(canData.data[4]);
        cvmData.steeringWheelAngle = (((Angle1 + Angle2)*0.1) - 780)/13;
        //printf("steering angle: %f .\n", cvmData.steeringWheelAngle);
    }

    // add 0.01 in case speed=0
    cvmData.steeringWheelAngle = 180*asin((cvmData.acceleration*2.569)/((cvmData.speed*cvmData.speed+0.01)*3.1415926*13)); //vehicleWheelDis(2.569)

}

}

}

}
