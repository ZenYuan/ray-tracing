#ifndef RAY_H
#define RAY_H

#include <array>
#include "vec.h"
#include "utility.h"
namespace pzyy {

class ray {
 public:
    ray(){}
    ray(const point& origin, const vec3f& direction):_origin(origin), _direction(direction) {}
    point orign() const { return _origin; }
    vec3f direction() const { return _direction; }
    vec3f at(double t) const { return _origin + t * _direction; }
 private:
    point _origin;
    vec3f _direction;
};

}
#endif
