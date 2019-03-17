#include <random>

#include <cvm/worldmodel/VehicleQueue.h>

namespace cvm
{

namespace worldmodel
{

namespace internal
{

int32_t random()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> uniformRandom((1 << 10), (1 << 20));
    return uniformRandom(gen);
}

}

VehicleQueue::VehicleQueue()
    : _thisVehicle(internal::random())
{
}

VehicleQueue::~VehicleQueue()
{
    for (auto it = _vehicles.begin(); it!=_vehicles.end(); it++) {
        delete it->second;
    }
}

int32_t VehicleQueue::updateFromBsm(const protocol::BsmData* bsmData)
{
    auto it = _vehicles.find(bsmData->carId);
//    assert(it->second->getVehicleData()->carId = bsmData->carId);

    Vehicle* vehicle = nullptr;
    if (it == _vehicles.end()) {
        vehicle = new Vehicle(bsmData->carId);
        vehicle->updateFromBsm(bsmData);
        _vehicles[bsmData->carId] = vehicle;
        LDEBUG << "New Vehicle = " << bsmData->carId;
    }else {
        vehicle = it->second;
        vehicle->updateFromBsm(bsmData);
        vehicle->resetExpiration();
//        LDEBUG << "Keep Vehicle = " << bsmData->carId;
    }

    Vehicle::transformToRelativeCordination(&_thisVehicle, vehicle);
    return bsmData->carId;
}

std::vector<int32_t> VehicleQueue::clearTimeoutVehicles()
{
    base::Timestamp now(base::Timestamp::now());
    std::vector<int32_t> carIds;
    for (auto it=_vehicles.begin(); it!=_vehicles.end(); ) {
        if (it->second->getExpiration() <= now) {
            carIds.push_back(it->second->getVehicleData()->carId);
            LDEBUG << "Delete Vehicle = " << it->second->getVehicleData()->carId;
            delete it->second;
            // DO NOT : _vehicles.erase(it); it++;
            // Since we access an invalid iterator after erasing it.
            _vehicles.erase(it++);
        }else {
            it++;
        }
    }
    return carIds;
}


}

}
