/**
  * @file IntersectionQueue.h
  * @brief Implememtation of class IntersectionQueue
  */
#ifndef _CVM_WORLDMODEL_INTERSECTIONQUEUE_H_
#define _CVM_WORLDMODEL_INTERSECTIONQUEUE_H_

#include <map>

#include <cvm/base/NonCopyable.h>
#include <cvm/worldmodel/IntersectionQueue.h>

namespace cvm
{

namespace protocol
{
class SpatData;
class MapData;
class VehicleData;
class IntersectionData;
}

namespace worldmodel
{

class Intersection;

/**
 * @class IntersectionQueue
 * @brief Maintain information about all the intersections
 */
class IntersectionQueue : public base::NonCopyable
{
public:
    const cvm::protocol::IntersectionData* getAnIntersection(int32_t id);
    void updateFromMap(const protocol::MapData* msg);
    void updateFromSpat(const protocol::SpatData* msg);

    /**
     * @brief Clear expired intersections
     */
    void clearExpiredIntersections();
    void chooseLight(const protocol::VehicleData* vehicleData);

private:
    std::map<int32_t, Intersection*> _intersections;
};

}

}

#endif // _CVM_WORLDMODEL_INTERSECTIONQUEUE_H_
