//#include <iostream>
//#include "vec.h"
#include "color.h"
#include "ray.h"
#include "hit.h"
#include "sphere.h"
#include "utility.h"
#include "camera.h"
using namespace pzyy;

int main() {
    // Image
    double aspect_ratio = 16.0f/9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //samples
    int samplesPixel = 100; 

    //objects
    pzyy::hitList world;
    world.add(std::make_shared<sphere>(0.5, point(0.0, 0.0, -1.0)));
    world.add(std::make_shared<sphere>(100, point(0.0, -100.5, -1.0)));

    //camera
    camera cam;
    //ray reflect times
    int depth = 10;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixelColor;
            for(int s = 0; s < 100; s++) {
                //一个像素点中取多个采样值
                double u = static_cast<double>(i + randomDouble())/(image_width-1);
                double v = static_cast<double>(j + randomDouble())/(image_height-1);
                pzyy::ray r = cam.getRay(u, v);
                pixelColor = pixelColor + ray_color(r, world, depth);
            }
            write_color(pixelColor, samplesPixel);
        }
    }
}