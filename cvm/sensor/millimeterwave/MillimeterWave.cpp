#include <cvm/base/Logging.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/sensor/millimeterwave/MillimeterWave.h>
#include <cvm/sensor/millimeterwave/MillimeterWaveConfig.h>

namespace cvm
{

namespace sensor
{

namespace millimeterwave
{

MillimeterWave::MillimeterWave(const MillimeterWaveConfig& config)
    : _config(config)
{
    // lcm
    if (!_lcm.good()) {
        DIE("Lcm init error");
    }

    // Your initialization code goes here
}

MillimeterWave::~MillimeterWave()
{
    // Your de-initialization code goes here
}


void MillimeterWave::loop()
{
    // Your main loop code goes here
}

}

}

}
