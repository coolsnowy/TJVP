#include <cvm/protocol/CanData.hpp>
#include <cvm/protocol/TurnLight.hpp>
#include <cvm/sensor/can/decoder/PanAsiaCanDecoder.h>
#include <cvm/sensor/can/CanDecoder.h>

namespace cvm
{

namespace sensor
{

namespace can
{

void PanAsiaCanDecoder::decode(const struct can_frame& canData, protocol::CanData& cvmData)
{
    if (canData.can_id == 1001) {
        double speed0 = static_cast<double>(canData.data[0])*256;
        double speed1 = static_cast<double>(canData.data[1]);
        cvmData.speed = (speed0+speed1)*0.015625*5/18;
    } else if (canData.can_id == 485) {
        double wheelAngle0 = static_cast<double>(canData.data[1])*256;
        double wheelAngle1 = static_cast<double>(canData.data[2]);
        double wheelAngle = (wheelAngle0+wheelAngle1)*0.0625;
        if (wheelAngle > 2048) {
            wheelAngle = wheelAngle-4095.9375;
        }
        cvmData.steeringWheelAngle = -wheelAngle / 13;
    } else if (canData.can_id == 320) {
        int turnLight = canData.data[2]&0xc;
        if(turnLight == 4){
            cvmData.turnLight = protocol::TurnLight::TurnLeft;
        }else if(turnLight == 8){
            cvmData.turnLight = protocol::TurnLight::TurnRight;
        }else{
            cvmData.turnLight = protocol::TurnLight::TurnNone;
        }
    }
}

}

}

}
