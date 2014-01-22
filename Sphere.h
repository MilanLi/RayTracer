#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Shape.h"
#include "Vec.h"
#include "Ray.h"

class Sphere : public Shape{
public:
  Vec center;
  float radius;
  Vec color;
  Sphere(const Vec& _center, float _radius, const Vec& _color);
  virtual bool intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const;
  virtual bool isIntersect(const Ray& r, float tmin, float tmax, float time)const;
};

#endif
