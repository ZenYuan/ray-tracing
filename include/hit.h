#ifndef HIT_H
#define HIT_H
#include <memory>
#include <vector>

//different matrial has vary hit function
namespace pzyy {
class ray;
class Matrials;

struct hitRecord {
    double t;     //光线传播时间
    point p;      //交点
    vec3f normal;
    std::shared_ptr<Matrials> matPtr;
};

class hit {
 public:
    /*scene object intersection with ray, return bool value which if has intersection*/
    virtual bool hitfunc(const ray& r, double tmin, double tmax, hitRecord& hitRec) const = 0;
};

class hitList : public hit {
 public:
    hitList(){}
    hitList(const std::shared_ptr<hit>& object){ _objectContiner.push_back(object); }
 public:   
    void add(const std::shared_ptr<hit>& object){ _objectContiner.push_back(object); }
    void clear(){ _objectContiner.clear(); }
    virtual bool hitfunc(const ray& r, double tmin, double tmax, hitRecord& hitRec) const override;

 private:
    std::vector<std::shared_ptr<hit>> _objectContiner;   //store sphere square etc. objects
};

}
#endif
