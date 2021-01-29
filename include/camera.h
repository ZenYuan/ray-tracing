#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"
#include "ray.h"

namespace pzyy {
class camera {
 public:
    //vfov视角的度数
    camera(double vfov, double aspect_ratio, const point& lookfrom, const vec3f& lookat, const vec3f& upTemp) {
        // Image
        int focus = 5;
        double h = std::tan(degreeToRadius(vfov)/2) * focus;
        int viewport_height = 2 * h;
        int viewport_width = static_cast<int>(viewport_height * aspect_ratio);

        //camera locl coordinate
        auto dir = identity(lookfrom - lookat);
        auto right = identity(cross(upTemp, dir));
        auto up = cross(dir, right);

        origin = lookfrom;
        vertical =  up * viewport_height;
        horizontal = right * viewport_width;
        low_left_conor = origin - horizontal/2.0 - vertical/2.0 - dir * focus;
    }

    ray getRay(double u, double v) const {
        return  ray(origin, low_left_conor + u*horizontal + v*vertical - origin);
    }

 private:
    point origin;
    point vertical;
    point horizontal;
    point low_left_conor;
};
}
#endif
