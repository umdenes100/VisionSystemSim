#ifndef DETAIL_H
#define DETAIL_H

#define PI 3.1415926

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

#define OSV_MIN_DIMENSION_METERS 0.15
#define OSV_MAX_DIMENSION_METERS 0.30

//#define DEFAULT_OSV_WIDTH 0.229
//#define DEFAULT_OSV_LENGTH 0.239
#define DEFAULT_OSV_WIDTH 0.25
#define DEFAULT_OSV_LENGTH 0.25

#define ENTROPY_STDDEV 0.06

struct Point {
    double x, y, theta;
};

#endif // DETAIL_H
