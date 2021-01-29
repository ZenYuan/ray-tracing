#include "header.h"

namespace pzyy {
    std::initializer_list<double> sphere::_hitSphere(const ray& r) const {
        //origin - center
        vec3f co = r.orign() - _center;
        //squre root b^2-4ac
        double a = dot(r.direction(), r.direction());
        double b = 2.0*dot(r.direction(), co);
        double c = dot(co, co)-_radius*_radius;
        double intersection = b*b-4*a*c;
        if(intersection < 0.0f) {
            return {};
        }
        //b是负值
        return {(-b - std::sqrt(intersection))/(2.0*a), (-b + std::sqrt(intersection))/(2.0*a)};
    }

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
        //itRec.normal = identity(hitRec.p - _center);
        hitRec.matPtr = _matPtr;
        hitRec.setFaceNormal(r, (hitRec.p - _center)/getRadius());
        return true;
    }
}
