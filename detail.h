#ifndef DETAIL_H
#define DETAIL_H

#define PI 3.1415926

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

#define ENTROPY_STDDEV 0.06

struct Point {
    double x, y, theta;
};

#endif // DETAIL_H
