#include "header.h"

namespace pzyy {
bool hitList::hitfunc(const ray& r, double tmin, double tmax, hitRecord& hitRec) const {
    bool hitObject = false;
    double closest_t = tmax;

    for(const auto& object : _objectContiner) {
        if(object->hitfunc(r, tmin, closest_t, hitRec)) {
            closest_t = hitRec.t;
            hitObject = true;
        } 
    }
    
    return hitObject;
}

}