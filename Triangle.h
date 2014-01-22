#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Shape.h"
#include "Vec.h"
#include "Ray.h"
#include "Texture.h"

class Triangle: public Shape{
public:
  Vec p0;
  Vec p1;
  Vec p2;
  float reflectionCoef;
  float refractionCoef;
  Texture* tex;
  Vec uv[3];
  Triangle(const Vec& _p0, const Vec& _uv0, const Vec& _p1, const Vec& _uv1,
           const Vec& _p2, const Vec& _uv2, float _reflectionCoef, float _refractionCoef, Texture* tex);
  virtual bool intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const;
  virtual bool isIntersect(const Ray& r, float tmin, float tmax, float time)const;
};

#endif
