#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Ray.h"
#include "Vec.h"
#include "Texture.h"

struct HitRecord{
  float t;
  Vec normal;
  Vec uv; // 2D texture
  Vec hit_p; // intersection
  float reflect; // reflection coefficients
  float transparency; //refraction coefficients
  Texture* hit_tex; //nearest intersected object's texture
};

class Shape{
public:
  virtual bool intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const = 0;
  virtual bool isIntersect(const Ray& r, float tmin, float tmax, float time)const = 0;
};

#endif
