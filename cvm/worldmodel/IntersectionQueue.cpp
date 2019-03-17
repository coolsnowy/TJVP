#include <cvm/base/Logging.h>
#include <cvm/protocol/MapData.hpp>
#include <cvm/protocol/SpatData.hpp>
#include <cvm/worldmodel/Intersection.h>
#include <cvm/worldmodel/IntersectionQueue.h>
#include <iostream>
namespace cvm
{

namespace worldmodel
{

const protocol::IntersectionData* IntersectionQueue::getAnIntersection(int32_t id)
{
    auto it = _intersections.find(id);
    assert(it != _intersections.end());
    return it->second->getIntersectionData();
}

void IntersectionQueue::updateFromMap(const protocol::MapData* msg)
{
    auto it = _intersections.find(msg->intersectionId);

    Intersection* intersection = nullptr;
    if (it == _intersections.end()) {
        intersection = new Intersection(msg->intersectionId);
        intersection->updateFromMap(msg);
        _intersections[msg->intersectionId] = intersection;
        LDEBUG << "New Intersection = " << msg->intersectionId;

    }else {
        intersection = it->second;
        intersection->updateFromMap(msg);
        intersection->resetExpiration();
        LDEBUG << "Keep Intersection = " << msg->intersectionId;
    }
}

void IntersectionQueue::updateFromSpat(const protocol::SpatData* msg)
{
    auto it = _intersections.find(msg->intersectionId);

    Intersection* intersection = nullptr;
    if (it == _intersections.end()) {
        intersection = new Intersection(msg->intersectionId);
        intersection->updateFromSpat(msg);
        _intersections[msg->intersectionId] = intersection;
        LDEBUG << "New Intersection = " << msg->intersectionId;
    }else {
        intersection = it->second;
        intersection->updateFromSpat(msg);
        intersection->resetExpiration();
        LDEBUG << "Keep Intersection = " << msg->intersectionId;
    }
}

void IntersectionQueue::clearExpiredIntersections()
{
    base::Timestamp now(base::Timestamp::now());
    for (auto it=_intersections.begin(); it!=_intersections.end(); ) {
        if (it->second->getExpiration() <= now) {
            LDEBUG << "Delete Intersection = " << it->second->getIntersectionData()->intersectionId;
            delete it->second;
            // DO NOT : _intersections.erase(it); it++;
            // Since we access an invalid iterator after erasing it.
            _intersections.erase(it++);
        }else {
            it++;
        }
    }
}

void IntersectionQueue::chooseLight(const protocol::VehicleData* vehicleData)
{

}


}

}
