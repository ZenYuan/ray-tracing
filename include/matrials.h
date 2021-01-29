#ifndef MATERIALS_H
#define MATERIALS_H
#include "vec.h"

namespace pzyy {
class ray;
class hitRecord;

class Matrials {
 public:
   virtual bool scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const = 0;
 public:
   static vec3f refract(vec3f& rayUnit, vec3f& normal, double refractRatio);
   static vec3f reflect(vec3f& rayUnit, vec3f& normal);
};

class lambertain : public Matrials {
 public:
    lambertain(const color& attenuation) : _attenuation(attenuation) {}
    virtual bool scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const override;
 private:
    color _attenuation;
};

class Metal : public Matrials {
 public:
    Metal(const color& attenuation, double fuzz) : _attenuation(attenuation), _fuzz(std::fabs(fuzz) < 1.0? fuzz:1.0) {}
    virtual bool scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const override;
 private:
    color _attenuation;
    double _fuzz;    //通过球体来确定反射光线， 球体越大反射越模糊
};

class Dielectric : public Matrials {
 public:
   Dielectric(double RafractRatio) : _RafractRatio(RafractRatio) {}
   virtual bool scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const override;
 private:
   static double reflectance(double cosine, double ref_idx);
 private:
   double _RafractRatio;
   //折射的能量衰减为0；
};

}

#endif
