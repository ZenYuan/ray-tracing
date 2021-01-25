#include "header.h"
#include "color.h"
using namespace pzyy;

color ray_color(const ray& r, const hitList& world, int depth) {
    hitRecord hitRec = {0};

    if(!depth) {
        return color(0, 0, 0);
    }

    //TODO：shadow acne problem not fix
    bool intersection = world.hitfunc(r, 0, infinity, hitRec);
    if(intersection)
    {
        ray scattered;
        color attenuation;
        //光线与物体交点产生的反射光线
        if(hitRec.matPtr->scatter(r, hitRec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        //光线全部被吸收
        return color(0, 0, 0);
    }
    /*calculate backfround color*/
    //identity of ray direction(-1.0 < y < 1.0)
    vec3f norm = identity(r.direction());
    double lerp = (norm.y + 1)/2.0f;
    return color((1 - lerp)*color(1.0, 1.0,1.0) + lerp*color(0.5, 0.7, 1.0));
}

int main() {
    // Image
    double aspect_ratio = 16.0f/9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width/aspect_ratio);

    //samples
    int samplesPixel = 100;

    //matrial
    auto matrialGround = std::make_shared<lambertain>(color(0.8, 0.8, 0.0));
    auto matrialCenter = std::make_shared<lambertain>(color(0.7, 0.3, 0.3));
    auto matrialLeft = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto matrialRight = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

    //objects
    hitList world;
    world.add(std::make_shared<sphere>(100, point(0.0, -100.5, -1.0), matrialGround));
    world.add(std::make_shared<sphere>(0.5, point(0.0, 0.0, -1.0), matrialCenter));
    world.add(std::make_shared<sphere>(0.5, point(-1.0, 0.0, -1.0), matrialLeft));
    world.add(std::make_shared<sphere>(0.5, point(1.0, -0.0, -1.0), matrialRight));

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
                ray r = cam.getRay(u, v);
                pixelColor = pixelColor + ray_color(r, world, depth);
            }
            write_color(pixelColor, samplesPixel);
        }
    }
}