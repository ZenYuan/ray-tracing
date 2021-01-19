#ifndef UTILITY_H
#define UTILITY_H
#include <cmath>
#include <limits>
#include <random>
#include <cstdlib>

const double infinity = std::numeric_limits<double>::infinity();

inline double random_double() {
    return rand()/(RAND_MAX + 1.0);  //[0, 1)
}



#endif
