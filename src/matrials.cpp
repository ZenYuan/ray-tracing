#include "header.h"
namespace pzyy {

vec3f Matrials::refract(vec3f& rayUnit, vec3f& normal, double refractRatio) {
    //入射光线和法线夹角
    double cosAngle = dot(-rayUnit, normal);
    // auto perp = refractRatio*(rayUnit + normal * cosAngle);
    // auto parallel = -normal*sqrt(fabs(1.0 - perp.lengthSquared()));
    // return perp + parallel;
    auto refractDirection = refractRatio*(rayUnit + normal * cosAngle) - normal*sqrt(1.0 - refractRatio*refractRatio*(1.0-cosAngle*cosAngle));
    return refractDirection;

}

vec3f Matrials::reflect(vec3f& rayUnit, vec3f& normal) {
    auto reflectDirection = rayUnit - 2*dot(rayUnit, normal)*normal;
    return reflectDirection;
}

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
            //反射光线的单位向量position为圆心， fuzz为半径
            //这点需要注意，需要先获取到单位随机方向再去缩小该方向的长度
            point reflectDirection = reflect(unitRayDirection, hitRec.normal) + _fuzz * randomPoint();
            rayOut = ray(hitRec.p, reflectDirection); // 入射光线的投影有表面法线反向
            attenuation = _attenuation;
            return true;
        }
        return false;
}

//Fresnel equation:得到这一点的反射比
double Dielectric::reflectance(double cosine, double ref_idx) {
      // Use Schlick's approximation for reflectance.
      auto r0 = (1-ref_idx) / (1+ref_idx);
      r0 = r0*r0;
      return r0 + (1-r0)*pow((1 - cosine),5);
}

bool Dielectric::scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const{
    double refractRatio =  hitRec.outSide ? (1.0/_RafractRatio) : _RafractRatio; //n/n`  //空气折射率1.0
    auto rayUnit = identity(rayIn.direction());

    vec3f rayDirection;
    double cosAngle = dot(-rayUnit, hitRec.normal);
    double sinAngle = sqrt(1 - cosAngle*cosAngle);
    double probility = reflectance(cosAngle, refractRatio);
    //实际一个平面一条光线符合能量守恒定律，一部分折射，一部分反射；这里简单一条光线反射概率大的话就没有折射
    //如果入射折射率大于出射折射率可能产生无折射的现象，此时为全内反射
    if(refractRatio*sinAngle > 1.0 || reflectance(cosAngle, refractRatio) > randomDouble()) {
        rayDirection = reflect(rayUnit, hitRec.normal);
    }else {
        //计算折射需要将normal设置为nagtive
        rayDirection = refract(rayUnit, hitRec.normal, refractRatio);
    }
    rayOut = ray(hitRec.p, rayDirection);
    //glass dielectric not absorb
    attenuation = color(1.0, 1.0, 1.0);
    return true;
}

}

