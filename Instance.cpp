#include "Instance.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape* _primitive)
  : M(trans), N(trans_inverse), primitive(_primitive){}

Instance::Instance(Matrix trans, Shape* _primitive)
  : M(trans), N(trans), primitive(_primitive)
{N.inverst();}

bool Instance::intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const{
  Vec no = transformLoc(N, r.origin());
  Vec nd = transformVec(N, r.direction());
  Ray tray(no, nd);

  if(primitive->intersect(tray, tmin, tmax, time, record)){
    record.hit_p = transformLoc(M, record.hit_p);
  }
}
