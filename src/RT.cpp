//#include <iostream>
//#include "vec.h"
#include "color.h"

// Image
const int image_width = 256;
const int image_height = 256;

int main() {
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    // Render
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_c(static_cast<double>(i)/(image_width-1), static_cast<double>(j)/(image_height-1), 0.25);
            write_color(image_width, image_height, pixel_c);
        }
    }
}