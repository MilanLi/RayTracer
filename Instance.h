#ifndef _INSTANCE_H_
#define _INSTANCE_H_

#include "Shape.h"
#include "Matrix.h"

class Instance : public shape{
public:
  Matrix M;
  Matrix N; //inverse of M
  Shape* primitive;
  Instance(){}
  ~Instance(){}
  Instance(Matrix trans, Matrix trans_inverse, Shape* _primitive);
  Instance(Matrix trans, Shape* _primitive);
  bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const;

};

#endif
