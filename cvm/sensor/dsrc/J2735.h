/**
  * @file J2735.h
  * @brief J2735消息的编解码函数,按照2009版本的J2735编写
  */
#ifndef _CVM_SENSOR_DSRC_J2735_H_
#define _CVM_SENSOR_DSRC_J2735_H_

#include <vector>

#include <cvm/protocol/BsmData.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>

namespace cvm
{
    
namespace sensor
{

namespace dsrc
{
/**
 * @brief bsm编码函数
 * @param bsmData 待编码的Bsm结构体
 * @return 返回含有编码后的二进制数据的vector，档该vector为空时表明编码错误
 */
std::vector<char> bsmDataEncode(const protocol::BsmData& bsmData);

/**
 * @brief bsm解码函数
 * @param data 待解码的buffer
 * @param size buffer的长度
 * @return 返回解码后的bsm结构体，该bsm结构体中的carId为-1时表明解码错误
 */
protocol::BsmData bsmDataDecode(const char* data, int64_t size);

/**
 * @brief map解码函数
 * @param data 待解码的buffer
 * @param size buffer的长度
 * @return 返回解码后的map结构体，该map结构体中的intersectionId为-1时表明解码错误
 */
protocol::MapData mapDataDecode(const char* data, int64_t size);

/**
 * @brief spat解码函数
 * @param data 待解码的buffer
 * @param size buffer的长度
 * @return 返回解码后的spat结构体，该spat结构体中的intersectionId为-1时表明解码错误
 */
protocol::SpatData spatDataDecode(const char* data, int64_t size);


    
}

}

}

#endif // _CVM_SENSOR_DSRC_J2735_H_

