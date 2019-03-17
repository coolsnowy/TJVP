#include <cvm/application/activesafety/ComputeTools.h>
#include <vector>
#include <math.h>
#include <assert.h>

namespace cvm {

namespace application {

namespace activesafety {

point endPoint(const point &sPoint, const double length, double angle)
{
    angle = angle * PI /180.0;
    double xDis = length * cos(angle);
    double yDis = length * sin(angle);

    point ePoint = {sPoint.x_ + xDis, sPoint.y_ + yDis};
    return ePoint;
}

void predictPath(const point &sPoint, const double heading, const double wAngle,
                 const double speed, const double vehicleWidth, const double vehicleLength,
                 const double vehicleWheelDis, std::vector<point> &path)
{
    ///clear the vector path
    path.clear();
    assert(path.size() == 0);

    double arrowLength = disOfPoints(0, 0, vehicleWidth, vehicleLength);
    assert(arrowLength > 1);

    /// Take speed into consideration when define arrowNum.
    /// Generally, arrowNum is proportional to speed.
    /// Constraint condition:
    /// 1.If speed is low, at least define arrowNum = arrowNumConstraint;
    /// 2.The longest distance must within distanceConstraint.
    const static int arrowNumRatio = 5;
    const static int arrowNumConstraint = 3;
    const static int distanceConstraint = 200;

    int arrowNum = round(arrowNumRatio * speed);
    if(arrowNum < arrowNumConstraint) arrowNum = arrowNumConstraint;
    if((int)(arrowNum * arrowLength) > distanceConstraint)
        arrowNum = (int)distanceConstraint/arrowLength;
    assert(arrowNum >= arrowNumConstraint);
    assert((int)(arrowNum * arrowLength) <= distanceConstraint);

    ///
    point startPoint = sPoint;
    point nextPoint;
    path.push_back(startPoint);
    std::vector<double> headings;
    headings.push_back(heading);

    ///
    double r =  vehicleWheelDis/(sin(wAngle*PI/180)+0.000001);
    double lengthAngle = arrowLength/r;
    double length = fabs(r * sin(lengthAngle/2)*2);
    double rotateAngle = lengthAngle/2/PI*180;
    for(int i=1;i<=arrowNum;i++)
    {
        if(fabs(rotateAngle * i) > 180)
            break;
        headings.push_back(heading - rotateAngle * i);
        nextPoint = endPoint(startPoint, length, headings[i]);
        path.push_back(nextPoint);
        startPoint = nextPoint;
    }
}

double disOfPoints(const double x1, const double y1,
                   const double x2, const double y2)
{
    return (double)sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

double DVofAngle(const double angle1, const double angle2)
{
    double temp = fabs(angle1 - angle2);
    assert(temp >= 0);
    if(temp > 360){
        int integer = round(temp);
        double decimal = temp - integer;
        integer = integer % 360;
        temp = (double)integer + decimal;
    }
    if(temp > 180){
        temp = 360 - temp;
    }
    return temp;
}

double disOfGPS(const double lon1, const double lati1,
                const double lon2, const double lati2)
{
    double ratio1 = 102834.74258026089;
    double ratio2 = 111712.69150641056;
    double lon_dis = fabs((double) ((lon1 - lon2) * ratio1));
    double lati_dis = fabs((double) ((lati1 - lati2) * ratio2));
    return (double)sqrt((lati_dis * lati_dis) + (lon_dis * lon_dis));
}


double gpsAngle_to_coorAngle(double angle)
{
    angle = - angle + 90.0;
    if (angle < -180.0)
    {
        return (angle + 360);
    }
    assert(angle >= -180 && angle <= 180);
    return angle;
}

point pointRotate(const point& rcenter, const point& originPoint, double angle)
{
    angle = angle * PI/180.0;
    point endPoint;

    endPoint.x_ = (originPoint.x_ - rcenter.x_) * cos(angle) +
            (originPoint.y_ - rcenter.y_) * sin(angle) + rcenter.x_;
    endPoint.y_ = -(originPoint.x_ - rcenter.x_) * sin(angle) +
            (originPoint.y_ - rcenter.y_) * cos(angle) + rcenter.y_;

    return endPoint;
}





//v2p
void transformGPStoRS(double lat1,double long1,double lat2,double long2, double heading,
                      double &x, double &y){
    double LatiRatio = 111712.69150641056;   //6371004*PI/180
    double LonRatio = LatiRatio*cos(lat1/180.0*PI);

    double gps_x = (long2  - long1) * LonRatio;
    double gps_y = (lat2 - lat1) * LatiRatio;

    double angle = - heading * PI/180.0;

    /// Rotate center is (0, 0)
    x = (gps_x - 0) * cos(angle) +
            (gps_y - 0) * sin(angle) + 0;
    y = -(gps_x - 0) * sin(angle) +
            (gps_y - 0) * cos(angle) + 0;
}


}

}

}





