#include "UVSphere.h"
#include "cmath"

UVSphere:: UVSphere(const Vec& _center, float _radius, float _reflectionCoef, float _refractionCoef, Texture* _tex)
  :center(_center), radius(_radius), reflectionCoef(_reflectionCoef), refractionCoef(_refractionCoef), tex(_tex){}

bool UVSphere::intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const{
  Vec temp = r.origin() - center;
  float a = r.direction().dot(r.direction());
  float b = 2 * r.direction().dot(temp);
  float c = temp.dot(temp) - radius * radius;

  float discriminant = b*b - 4*a*c;
  if(discriminant > 0){
    discriminant = sqrt(discriminant);
    float t = (-b -discriminant) /(2*a);
    if(t < tmin) t = (-b + discriminant) / (2*a);
    if(t < tmin || t > tmax) return false;
    
    record.t = t;
    record.hit_p = r.origin() + r.direction() * t;
    record.reflect = reflectionCoef;
    record.transparency = refractionCoef;
    Vec n = record.normal = normalize(r.origin() + r.direction()*t - center);
    
    //calculate UV coordinates
    float theta = acos(n.y);
    float phi = atan2(n.z, n.x);
    if(phi < 0) phi += M_PI * 2;
    record.uv = Vec(phi/(2* M_PI), (M_PI - theta)/M_PI, 0);
    record.hit_tex = tex;
    return true;
  }
  return false;
}

bool UVSphere::isIntersect(const Ray& r, float tmin, float tmax, float time)const{
  Vec temp = r.origin() - center;
  float a = r.direction().dot(r.direction());
  float b = 2 * r.direction().dot(temp);
  float c = temp.dot(temp) - radius * radius;

  float discriminant = b*b - 4*a*c;
  if(discriminant > 0){
    discriminant = sqrt(discriminant);
    float t = (-b -discriminant) /(2*a);
    if(t < tmin) t = (-b + discriminant) / (2*a);
    if(t < tmin || t > tmax) return false;
    
    return true;
  }
  return false;
}
