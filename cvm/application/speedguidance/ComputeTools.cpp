#include <cvm/application/speedguidance/ComputeTools.h>
#include <math.h>
#include <iostream>

namespace cvm {

namespace application {

namespace speedguidance {


double cal_dis_of_GPS(double lat1, double long1, double lat2, double long2){

    lat1 = lat1/180*PI;
    long1 = long1/180*PI;
    lat2 = lat2/180*PI;
    long2 = long2/180*PI;
    double x=0;
    double y=0;
    x = 6371004*(lat2-lat1);
    y = 6371004*cos(lat1)*(long2-long1);

    return sqrt(x*x+y*y);
}

/**
 * @brief compute the angle between vector A & vector B
 * @param A
 * @param B
 * @return
 */
double cal_angle_vec_vec(double x1,double y1,double x2,double y2){
    double d1 = sqrt(x1*x1+y1*y1);
    double d2 = sqrt(x2*x2+y2*y2);
    double d3 = x1*x2+y1*y2;
    double theat = d3/(d1*d2);
    return theat;
}

void transformGPStoRS(double lat1, double long1, double lat2,
                           double long2, double heading, VectorPP &PP){

    double LatiRatio = 111712.69150641056;   //6371004*PI/180
    double LonRatio = LatiRatio*cos(lat1/180.0*PI);

    double gps_x = (long2  - long1) * LonRatio;
    double gps_y = (lat2 - lat1) * LatiRatio;

    double angle = - heading * PI/180.0;

    /// Rotate center is (0, 0)
    PP.x = (gps_x - 0) * cos(angle) +
            (gps_y - 0) * sin(angle) + 0;
    PP.y = -(gps_x - 0) * sin(angle) +
            (gps_y - 0) * cos(angle) + 0;
    //std::cout<<"relative point:   x ="<<relative_x<<"  y= "<<relative_y<<std::endl;
}


}

}

}
