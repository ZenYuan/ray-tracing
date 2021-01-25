#ifndef UTILITY_H
#define UTILITY_H
#include <cmath>
#include <limits>
#include <random>
#include <cstdlib>
#include "vec.h"

const double infinity = std::numeric_limits<double>::infinity();

inline double randomDouble() {
    return rand()/(RAND_MAX + 1.0);  //[0, 1)
}

inline double randomRangeDouble(int min, int max) {
    return min + (1 - randomDouble())*max;
}

inline pzyy::point randomPointSphere() {
    while(1) {
        pzyy::point randomPoint(randomRangeDouble(-1, 1), randomRangeDouble(-1, 1), randomRangeDouble(-1, 1));
        if(randomPoint.length() < 1.0) {
            return randomPoint;
        }
    }
}

//获取漫反射点外接矩形圆中随机一点
inline pzyy::point randomPoint() {
    return identity(randomPointSphere());
}



#endif
