/**
  * @file Intersection.h
  * @brief Implememtation of class Intersection
  */
#ifndef _CVM_WORLDMODEL_INTERSECTION_H_
#define _CVM_WORLDMODEL_INTERSECTION_H_

#include <cvm/base/Timestamp.h>
#include <cvm/base/NonCopyable.h>
#include <cvm/protocol/IntersectionData.hpp>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>
#include <cvm/protocol/Approach.hpp>
#include <cvm/protocol/Lane.hpp>

namespace cvm
{

namespace protocol
{
class SpatData;
class MapData;
}


namespace worldmodel
{
/**
 * @class Intersection
 * @brief Maintain information about an intersection
 */
class Intersection : public base::NonCopyable
{
public:
    Intersection(int32_t intersectionId);

    ~Intersection();

    /**
     * @brief Get information about this intersection
     * @return A porinter to this intersection
     */
    const cvm::protocol::IntersectionData* getIntersectionData() const { return &_intersectionData; }

    void resetExpiration()
    {
        _expiration = base::addTime(base::Timestamp::now(),
                                  kIntersectionExpireTimeSeconds * 1000 * 1000);
    }

    /**
     * @brief Get expiration
     * @return Timestamp about expiration
     */
    base::Timestamp getExpiration() const { return _expiration; }

    void updateFromMap(const protocol::MapData* msg);
    void updateFromSpat(const protocol::SpatData* msg);//在这里对map和spat消息进行整合,整合成IntersectionData类型

private:

    const static int kIntersectionExpireTimeSeconds = 4;

    protocol::IntersectionData _intersectionData;
    protocol::MapData _tempMapData;
    bool readMapMsg;
    base::Timestamp _expiration;
};

}

}
#endif // _CVM_WORLDMODEL_INTERSECTION_H_
