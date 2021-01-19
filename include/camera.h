#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"
#include "ray.h"

namespace pzyy {
class camera {
 public:
    camera() {
        // Image
        double aspect_ratio = 16.0f/9.0f;
        int viewport_height = 2;
        int viewport_width = static_cast<int>(viewport_height * aspect_ratio);
        int focus = 1; 

        origin = point(0, 0, 0);
        vertical = point(0, viewport_height, 0);
        horizontal = point(viewport_width, 0, 0);
        low_left_conor = origin - horizontal/2.0 - vertical/2.0 - pzyy::vec3f(0, 0, focus);
    }

    ray getRay(double u, double v) const {
        return  ray(origin, low_left_conor + u*horizontal + v*vertical);
    }
    
 private:
    point origin;
    point vertical;
    point horizontal;
    point low_left_conor;
};
}
#endif
