#include <iostream>

#include <libconfig/libconfig.h++>

#include <cvm/sensor/dsrc/Dsrc.h>
#include <cvm/Main.h>

using namespace cvm::sensor::dsrc;

MAIN(Dsrc, DsrcConfig, CVM_SENSOR_DSRC_CONFIG_FILE)
