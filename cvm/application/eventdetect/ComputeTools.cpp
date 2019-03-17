#include <cvm/application/eventdetect/EventDetect.h>

namespace cvm {

namespace application {

namespace eventdetect {

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


}

}

}
