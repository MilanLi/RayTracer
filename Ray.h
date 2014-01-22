#ifndef _RAY_H_
#define _RAY_H_

#include "Vec.h"

class Ray{
public:
  //source and normalized direction
  Vec data[2];
  Ray(){}
  Ray(const Vec& a, const Vec& b){
    data[0] = a;
    data[1] = b;
  }
  Ray(const Ray& r){
    *this = r;
  }
  Vec origin()const{return data[0];}
  Vec direction()const{return data[1];}
  Vec pointAtParameter(float t)const{
    return data[0] + data[1]*t;
  }
};

#endif
