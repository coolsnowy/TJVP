#include <random>

#include <cvm/worldmodel/Vehicle.h>

namespace cvm
{

namespace worldmodel
{

namespace internal
{

double arrangeWithRange(double value, double start = 0.0, double end = 360.0)
{
    assert(start < end);
    double range = end - start;
    value = value - start;
    int times = static_cast<int>(value / range);
    return value - range * times;
}

}

Vehicle::Vehicle(int32_t carId)
{
    assert(carId > 0);
    _vehicleData.carId = carId;
    _vehicleData.acceleration = 0;
    _vehicleData.relativeX = 0;
    _vehicleData.relativeY = 0;
    _vehicleData.relativeZ = 0;
    _vehicleData.relativeAzimuth = 90;
    _vehicleData.azimuth = 0;
    _vehicleData.location.latitude = 0;
    _vehicleData.location.longitude = 0;
    _vehicleData.location.altitude = 0;

    resetExpiration();
}

Vehicle::~Vehicle()
{

}

void Vehicle::updateFromCan(const protocol::CanData* canData)
{
    assert(_vehicleData.carId > 0);
    _vehicleData.speed = canData->speed;
    _vehicleData.acceleration = canData->acceleration;
    _vehicleData.steeringWheelAngle = canData->steeringWheelAngle;
    _vehicleData.turnLight = canData->turnLight;
}

void Vehicle::updateFromGps(const protocol::GpsData* gpsData)
{
    assert(_vehicleData.carId > 0);
    _vehicleData.location = gpsData->location;
    _vehicleData.azimuth  = gpsData->azimuth;
}

void Vehicle::updateFromBsm(const protocol::BsmData* bsmData)
{
    assert(_vehicleData.carId == bsmData->carId);
    _vehicleData.location = bsmData->location;
    _vehicleData.speed    = bsmData->speed;
    _vehicleData.acceleration = bsmData->acceleration;
    _vehicleData.steeringWheelAngle = bsmData->steeringWheelAngle;
    _vehicleData.azimuth = bsmData->azimuth;

}

void Vehicle::transformToRelativeCordination(const Vehicle* reference, Vehicle* other)
{
    double PI = 3.1415926;
    //r = 6371.004km (earth)
    //ratios of longitude and latitude
    double LatiRatio = 111712.69150641056;   //6371004*PI/180
    double LonRatio = LatiRatio*cos(reference->getVehicleData()->location.latitude/180.0*PI);

    double gps_x = (other->getVehicleData()->location.longitude  - reference->getVehicleData()->location.longitude) * LonRatio;
    double gps_y = (other->getVehicleData()->location.latitude - reference->getVehicleData()->location.latitude) * LatiRatio;

    double angle = - reference->getVehicleData()->azimuth * PI/180.0;

    /// Rotate center is (0, 0)
    double relative_x = (gps_x - 0) * cos(angle) +
            (gps_y - 0) * sin(angle) + 0;
    double relative_y = -(gps_x - 0) * sin(angle) +
            (gps_y - 0) * cos(angle) + 0;


    other->_vehicleData.relativeX = relative_x;
    other->_vehicleData.relativeY = relative_y;
    other->_vehicleData.relativeZ = 0;

    transformToRelativeAzimuth(reference, other);
}

void Vehicle::transformToRelativeAzimuth(const Vehicle* reference, Vehicle* other)
{
    double relativeAzimuth = 90 - (360.0 - reference->_vehicleData.azimuth) + (360.0 - other->_vehicleData.azimuth);
    if(relativeAzimuth < -180) {
        relativeAzimuth += 360;
    }
    if(relativeAzimuth >180) {
        relativeAzimuth = relativeAzimuth - 360;
    }
    other->_vehicleData.relativeAzimuth = relativeAzimuth;
}


}

}
