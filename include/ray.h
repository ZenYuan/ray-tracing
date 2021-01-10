#ifndef RAY_H
#define RAY_H
#include "vec.h"
#include "color.h"
#include <cmath>

namespace pzyy {
class ray {
 public:
    ray(){}
    ray(const point& origin, const vec3f& director):_origin(origin), _director(director) {}
    point orign() const { return _origin; }
    vec3f director() const { return _director; }
    vec3f at(double t) const { return _origin + t * _director; }
 private:
    point _origin;
    vec3f _director;
};

/*
1.ray 用于获取origin和director
2.sphere center 圆心
3.radius 半径
*/
double hitSphere(const ray& r, const point& SphereCenter, double radius) {
    //origin - center 
    vec3f co = r.orign() - SphereCenter;
    //squre root b^2-4ac
    double a = dot(r.director(), r.director());
    double b = 2.0*dot(r.director(), co);
    double c = dot(co, co)-radius*radius;
    double intersection = b*b-4*a*c;
    if(intersection < 0.0f) {
        return -1.0;
    }
    return (-b - std::sqrt(intersection))/(2.0*a);
}

color ray_color(const ray& r) {
    /*ray param of t*/  
    auto t = hitSphere(r, point(0, 0, -1), 0.5);
    if(t > 0.0) {
        //sphereNormal every component [-1.0, 1.0]
        vec3f sphereNormal = identity(r.at(t) - point(0, 0, -1));
        return 0.5*color(sphereNormal.x+1, sphereNormal.y+1, sphereNormal.z+1);
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
