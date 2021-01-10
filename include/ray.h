#ifndef RAY_H
#define RAY_H
#include "vec.h"
#include "color.h"

namespace pzyy {
class ray {
 public:
    ray(){}
    ray(const point& origin, const vec3f& director):_origin(origin), _director(director) {}
    point orign() const { return _origin; }
    vec3f director() const { return _director; }
    vec3f at(double t) { return _origin + t * _director; }
 private:
    point _origin;
    vec3f _director;
};

/*
1.ray 用于获取origin和director
2.sphere center 圆心
3.radius 半径
*/
bool hitSphere(const ray& r, const point& SphereCenter, double radius) {
    //origin - center 
    vec3f co = r.orign() - SphereCenter;
    //squre root b^2-4ac
    double a = dot(r.director(), r.director());
    double b = 2.0*dot(r.director(), co);
    double c = dot(co, co)-radius*radius;
    bool intersection = (b*b-4*a*c >= 0)?1:0;
    return intersection;
}

color ray_color(const ray& r) {    
    /*define sphere equation*/
    if(hitSphere(r, point(0, 0, -1), 0.5)) {
        return color(1.0, 0.0, 0.0);
    }
    /*calculate backfround color*/
    //identity of ray director(-1.0 < y < 1.0)
    vec3f norm = identity(r.director());
    double lerp = (norm.y + 1)/2.0f;
    color tmp = (1 - lerp)*color(1.0, 1.0,1.0) + lerp*color(0.5, 0.7, 1.0);
    //calculate color

    return tmp;
}

}
#endif
