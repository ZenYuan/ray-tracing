#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include "vec.h"
namespace pzyy {
void write_color(const color& pixel_c, int samplesPixel) {
    auto scale = 1.0 / samplesPixel;

    //应当是开根号2.2，gamma correction的系数是2.2
    int r = static_cast<int>(256 * sqrt(pixel_c.r * scale));
    int g = static_cast<int>(256 * sqrt(pixel_c.g * scale));
    int b = static_cast<int>(256 * sqrt(pixel_c.b * scale));
    std::cout << r << ' ' << g << ' ' << b <<std::endl;
}
}
#endif
