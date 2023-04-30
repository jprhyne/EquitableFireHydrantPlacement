#include "../include/distances.h"
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
    // Grab the converted angles.
    double lat1 = degreeToRadian(building.lat);
    double lon1 = degreeToRadian(building.lon);
    double lat2 = degreeToRadian(hydrant.lat);
    double lon2 = degreeToRadian(hydrant.lon);
    // Convert to Cartesian coordinates
    double x1 = RADIUS * cos(lat1) * cos(lon1);
    double y1 = RADIUS * cos(lat1) * sin(lon1);
    double z1 = RADIUS * sin(lat1);
    double x2 = RADIUS * cos(lat2) * cos(lon2);
    double y2 = RADIUS * cos(lat2) * sin(lon2);
    double z2 = RADIUS * sin(lat2);
    // Store the distances
    double deltaX = x2 - x1;
    double deltaY = y2 - y1;
    double deltaZ = z2 - z1;
    // return the euclidean distance in R^3
    return sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}
