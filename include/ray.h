#ifndef RAY_H
#define RAY_H
#include "vec.h"
#include "color.h"
#include <cmath>
#include <array>
#include "hit.h"
#include "utility.h"

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

//用当前交点获取漫反射随机一点
inline point randomPointSphere(hitRecord& hitRec) {
    while(1) {
        //cube中任取内接圆中的一点
        point randomPoint(randomRangeDouble(-1, 1), randomRangeDouble(-1, 1), randomRangeDouble(-1, 1));
        if(randomPoint.length() < 1.0) {
            //漫反射点在世界坐标系下的位置
            point target = hitRec.p + (hitRec.normal + randomPoint);
            return target;
        }
    }
}


color ray_color(const ray& r, const hitList& world, int depth) {
    hitRecord hitRec = {0};

    if(!depth) {
        return color(0, 0, 0);
    }

    bool intersection = world.hitfunc(r, 0, infinity, hitRec);
    if(intersection)
    {   
        //光线与物体交点产生的新光线
        ray diffuseRay(hitRec.p, randomPointSphere(hitRec) - hitRec.p);
        return 0.5 * ray_color(diffuseRay, world, depth-1);
    }
    /*calculate backfround color*/
    //identity of ray director(-1.0 < y < 1.0)
    vec3f norm = identity(r.director());
    double lerp = (norm.y + 1)/2.0f;
    return color((1 - lerp)*color(1.0, 1.0,1.0) + lerp*color(0.5, 0.7, 1.0));
}

}
#endif
