#include <cvm/base/Logging.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/sensor/ultrasonic/Ultrasonic.h>
#include <cvm/sensor/ultrasonic/UltrasonicConfig.h>

namespace cvm
{

namespace sensor
{

namespace ultrasonic
{

Ultrasonic::Ultrasonic(const UltrasonicConfig& config)
    : _config(config)
{
    // lcm
    if (!_lcm.good()) {
        DIE("Lcm init error");
    }

    // Your initialization code goes here
}

Ultrasonic::~Ultrasonic()
{
    // Your de-initialization code goes here
}


void Ultrasonic::loop()
{
    // Your main loop code goes here
}

}

}

}
