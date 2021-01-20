#ifndef SPHERE_H
#define SPHERE_H
#include "ray.h"
#include "hit.h"
#include "initializer_list"
/*
1.ray 用于获取origin和director
2.sphere center 圆心
3.radius 半径
*/
namespace pzyy {

//sphere
class sphere: public hit {
 public:
    sphere() {}
    sphere(double radius, const point& center) : _radius(radius), _center(center) {}
 public:
    virtual bool hitfunc(const ray& r, double tmin, double tmax, hitRecord& hitRec) const override;
 private:
    std::initializer_list<double> _hitSphere(const ray& r) const {
        //origin - center 
        vec3f co = r.orign() - _center;
        //squre root b^2-4ac
        double a = dot(r.director(), r.director());
        double b = 2.0*dot(r.director(), co);
        double c = dot(co, co)-_radius*_radius;
        double intersection = b*b-4*a*c;
        if(intersection < 0.0f) {
            return {};
        }
        //b是负值
        return {(-b - std::sqrt(intersection))/(2.0*a), (-b + std::sqrt(intersection))/(2.0*a)};
    }

private:
    double _radius = 0;
    point _center;
};

bool sphere::hitfunc(const ray& r, double tmin, double tmax, hitRecord& hitRec) const {
        auto rootList = _hitSphere(r);
        //find nearest root
        if(!rootList.size()) { return false; }
        double root = *rootList.begin();
        if(root < tmin || root > tmax) { 
            root = *(rootList.begin() + 1);
            if(root < tmin || root > tmax)
            {
                return false;
            }
        }
        
        hitRec.t = root;
        hitRec.p = r.at(root);
        hitRec.normal = identity(hitRec.p - _center);
        return true;
    }

}
#endif
