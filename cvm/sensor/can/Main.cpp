#include <iostream>

#include <libconfig/libconfig.h++>

#include <cvm/sensor/can/Can.h>
#include <cvm/Main.h>

using namespace cvm::sensor::can;

MAIN(Can, CanConfig, CVM_SENSOR_CAN_CONFIG_FILE)
