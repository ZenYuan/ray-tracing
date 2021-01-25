#ifndef MATERIALS_H
#define MATERIALS_H
#include "vec.h"

namespace pzyy {
class ray;
class hitRecord;

class Matrials {
 public:
    virtual bool scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const = 0;
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
    Metal(const color& attenuation) : _attenuation(attenuation) {}
    virtual bool scatter(const ray& rayIn, hitRecord& hitRec, color& attenuation, ray& rayOut) const override;
 private:
    color _attenuation;
};


}




#endif
