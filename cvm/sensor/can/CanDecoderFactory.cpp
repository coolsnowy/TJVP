#include <cvm/sensor/can/decoder/RoeweE50CanDecoder.h>
#include <cvm/sensor/can/decoder/PanAsiaCanDecoder.h>
#include <cvm/sensor/can/decoder/BaicCanDecoder.h>
#include <cvm/sensor/can/CanDecoderFactory.h>

namespace cvm
{

namespace sensor
{

namespace can
{

CanDecoderFactory::CanDecoderFactory()
{
    regist(RoeweE50, [](){ return new RoeweE50CanDecoder; });
    regist(PanAsia, [](){ return new PanAsiaCanDecoder; });
    regist(Baic, [](){ return new BaicCanDecoder; });
}

CanDecoderFactory& CanDecoderFactory::instance()
{
    static CanDecoderFactory canDecoderFactory;
    return canDecoderFactory;
}

}

}

}
