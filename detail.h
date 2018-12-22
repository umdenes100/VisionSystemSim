#ifndef DETAIL_H
#define DETAIL_H

#define PI 3.1415926f

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

struct Point {
    float x, y, theta;
};

#endif // DETAIL_H
