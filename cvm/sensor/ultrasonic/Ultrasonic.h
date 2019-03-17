#ifndef _CVM_SENSOR_ULTRASONIC_ULTRASONIC_H_
#define _CVM_SENSOR_ULTRASONIC_ULTRASONIC_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>
#include <cvm/sensor/ultrasonic/UltrasonicConfig.h>

namespace cvm
{

namespace sensor
{

namespace ultrasonic
{

class Ultrasonic : public base::NonCopyable
{
public:
    Ultrasonic(const UltrasonicConfig& config);
    ~Ultrasonic();

    void loop();

private:
    lcm::LCM _lcm;
    const UltrasonicConfig _config;
};

}

}

}


#endif // _CVM_SENSOR_ULTRASONIC_ULTRASONIC_H_
