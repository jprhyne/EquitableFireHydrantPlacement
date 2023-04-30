#include <math.h>
#include "coordinate.h"

// Approximate radius of the earth in meters
#define RADIUS 6372797.56085

#define PI 3.14159265358979323846

double degreeToRadian(double angle)
{
    //return angle;
    return angle * PI / 180.;
}

double distanceInM(Coordinate building, Coordinate hydrant)
{
    /*
    double dist;
    double lat1 = degreeToRadian(building.lat);
    double lon1 = degreeToRadian(building.lon);
    double lat2 = degreeToRadian(hydrant.lat);
    double lon2 = degreeToRadian(hydrant.lon);
    double latDiff = lat2 - lat1;
    double lonDiff = lon2 - lon1;
    dist = sqrt(sin(latDiff/2.)*sin(latDiff/2.) + cos(lat1)*cos(lat2)*sin(lonDiff/2.)*sin(lonDiff/2.));
    dist = asin(dist);
    return 2*dist * RADIUS;
    */
    double dist;
    double lat1 = building.lat;
    double lat2 = hydrant.lat;
    double lon1 = building.lon;
    double lon2 = hydrant.lon;

    double x1 = RADIUS * sin(lat1) * cos(lon1);
    double y1 = RADIUS * sin(lat1) * sin(lon1);
    double z1 = RADIUS * cos(lat1);
    double x2 = RADIUS * sin(lat2) * cos(lon2);
    double y2 = RADIUS * sin(lat2) * sin(lon2);
    double z2 = RADIUS * cos(lat2);

    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;

    return sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}
