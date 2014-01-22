#ifndef _UV_SPHERE_H_
#define _UV_SPHERE_H_

#include "Shape.h"
#include "Vec.h"
#include "Ray.h"
#include "Texture.h"

class UVSphere : public Shape{
public:
  Vec center;
  float radius;
  float reflectionCoef;  
  float refractionCoef;
  Texture* tex;
  
  UVSphere(const Vec& _center, float _radius, float _reflectionCoef, float _refractionCoef, Texture* _tex);
  virtual bool intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const;
  virtual bool isIntersect(const Ray& r, float tmin, float tmax, float time)const;
};

#endif
