#ifndef _CVM_SENSOR_MILLIMETERWAVE_MILLIMETERWAVE_H_
#define _CVM_SENSOR_MILLIMETERWAVE_MILLIMETERWAVE_H_

#include <lcm/lcm-cpp.hpp>

#include <cvm/base/NonCopyable.h>

#include <cvm/sensor/millimeterwave/MillimeterWaveConfig.h>

namespace cvm
{

namespace sensor
{

namespace millimeterwave
{

class MillimeterWave : public base::NonCopyable
{
public:
    MillimeterWave(const MillimeterWaveConfig& config);
    ~MillimeterWave();

    void loop();

private:
    lcm::LCM _lcm;
    const MillimeterWaveConfig _config;
};

}

}

}


#endif // _CVM_SENSOR_MILLIMETERWAVE_MILLIMETERWAVE_H_
