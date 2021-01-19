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
#if 0
    //camera
    pzyy::point origin; //(0, 0, 0)
    int viewport_height = 2;
    int viewport_width = static_cast<int>(viewport_height * aspect_ratio);
    int focus = 1;

    pzyy::point vertical(0, viewport_height, 0);
    pzyy::point horizontal(viewport_width, 0, 0);
    pzyy::point low_left_conor = origin - horizontal/2.0 - vertical/2.0 - pzyy::vec3f(0, 0, focus);
#endif

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixelColor;
            for(int s = 0; s < 100; s++) {
                //一个像素点中取多个采样值
                double u = static_cast<double>(i + random_double())/(image_width-1);
                double v = static_cast<double>(j + random_double())/(image_height-1);
                pzyy::ray r = cam.getRay(u, v);
                pixelColor = pixelColor + ray_color(r, world);
            }
            write_color(pixelColor, samplesPixel);
        }
    }
}