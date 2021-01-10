#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include "vec.h"
namespace pzyy {
void write_color(const color& pixel_c) {
    int r = static_cast<int>(255.999 * pixel_c.r);
    int g = static_cast<int>(255.999 * pixel_c.g);
    int b = static_cast<int>(255.999 * pixel_c.b);
    std::cout << r << ' ' << g << ' ' << b <<std::endl;
}
}
#endif
