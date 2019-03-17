#include <iostream>

#include <libconfig/libconfig.h++>

#include <cvm/sensor/gps/Gps.h>
#include <cvm/sensor/gps/GpsConfig.h>
#include <cvm/Main.h>

using namespace cvm::sensor::gps;

MAIN(Gps, GpsConfig, CVM_SENSOR_GPS_CONFIG_FILE)
