#include <cvm/application/activesafety/ActiveSafetyConfig.h>

namespace cvm
{

namespace application
{

namespace activesafety
{

/// Parameter for isDangerPossible()
const double isDanger_hv_speed_low_ = 0.3;
const double isDanger_ov_area_r_high_ = 200;

/// Parameter for calVehicleLocation()
const double calLoc_hv_wheelangle_high_ = 5;
const double calLoc_hv_wheelangle_low_ = -5;

/// -------------------- split line ------------------------

/// Parameter for is_DNPW_Warning()
//const double isDNPW_hv_wheelangle_high_ = -3;

/// Parameter for is_ICW_Warning()

/// Parameter for is_INCM_Warning()
const double isINCM_ov_area_y_low_ = 15;


/// Parameter for is_FCW_Warning()
const double isFCW_dis_speed = 1;

/// Parameter for is_PW_Wanring()
const double isPW_dis_speed = 2;

/// Parameter for is_LCW_Warning()
const double isLCW_dis_x_min = 1;
const double isLCW_dis_x_max = 15;
const double isLCW_dis_y_min = 1;
const double isLCW_dis_y_max = 15;


/// -------------------- split line ------------------------


/// front_left: REVERSE_DIRECT
const double FL_REVERSE_DIR_ov_heading_high_ = -70;
const double FL_REVERSE_DIR_ov_heading_low_ = -110;
const double FL_REVERSE_DIR_ov_area_x_low_ = -10;

/// front_left: INTERSECT_DIRECT
const double FL_INTERSECT_DIR_ov_heading_low_ = -20;
const double FL_INTERSECT_DIR_ov_heading_high_ = 20;

/// front_direct: SAME_DIRECT
const double FD_SAME_DIR_ov_heading_low_ = 70;
const double FD_SAME_DIR_ov_heading_high_ = 110;

/// front_direct: REVERSE_DIRECT
const double FD_REVERSE_DIR_ov_heading_low_ = -110;
const double FD_REVERSE_DIR_ov_heading_high_ = -70;

/// front_right: INTERSECT_DIRECT
const double FR_INTERSECT_DIR_ov_heading_low_ = 160;
const double FR_INTERSECT_DIR_ov_heading_high_ = -160;

/// back_left: SAME_DIRECT
const double BL_SAME_DIR_ov_heading_low_ = 70;
const double BL_SAME_DIR_ov_heading_high_ = 110;

/// back_right: SAME_DIRECT
const double BR_SAME_DIR_ov_heading_low_ = 70;
const double BR_SAME_DIR_ov_heading_high_ = 110;


/// -------------------- split line ------------------------


/// frequency of sending results to can
/// unit : 100 ms
const int NORMAL_FREQUENCY = 5;
const int DANGER_FREQUENCY = 3;

/// Time to live : detect results
/// unit : 100 ms
const int DETECTRESULTS_TTL = 10;

ActiveSafetyConfig::ActiveSafetyConfig(int argc, char** argv, const std::string& configFile)
{
    debug = true;
}

void ActiveSafetyConfig::printHelp()
{
}

void ActiveSafetyConfig::printConfig()
{

}

}

}

}

