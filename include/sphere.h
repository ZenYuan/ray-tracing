#ifndef SPHERE_H
#define SPHERE_H
#include <memory>
#include <initializer_list>
#include "vec.h"
/*
1.ray 用于获取origin和direction
2.sphere center 圆心
3.radius 半径
*/
namespace pzyy {

class ray;
class hitRecord;
class Matrials;
//sphere
class sphere: public hit {
 public:
    sphere() {}
    sphere(double radius, const point& center) 
    : _radius(radius), _center(center){}
    sphere(double radius, const point& center, const std::shared_ptr<Matrials>& matPtr) 
    : _radius(radius), _center(center), _matPtr(matPtr) {}
 public:
    virtual bool hitfunc(const ray& r, double tmin, double tmax, hitRecord& hitRec) const override;
 private:
    std::initializer_list<double> _hitSphere(const ray& r) const;

private:
    double _radius = 0;
    point _center;
    std::shared_ptr<Matrials> _matPtr;
};

}
#endif
