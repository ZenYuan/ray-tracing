#include "header.h"
namespace pzyy {

bool lambertain::scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const {
        auto scatterDiretion = hitRec.normal + randomPoint();
        if(scatterDiretion.nearZero()) {
            scatterDiretion = hitRec.normal;
        }
        rayOut = ray(hitRec.p, scatterDiretion);
        attenuation = _attenuation;
        return true;
}

bool Metal::scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const {
        if(dot(rayIn.direction(), hitRec.normal) < 0) {
            auto unitRayDirection = identity(rayIn.direction());
            double normalLength = dot(unitRayDirection, hitRec.normal);
            rayOut = ray(hitRec.p, unitRayDirection - 2*normalLength*hitRec.normal); // 入射光线的投影有表面法线反向
            attenuation = _attenuation;
            return true;
        }
        return false;
}

}