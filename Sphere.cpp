#include "Sphere.h"

Sphere:: Sphere(const Vec& _center, float _radius, const Vec& _color)
  :center(_center), radius(_radius), color(_color){}

bool Sphere::intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const{
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
    record.normal = normalize(r.origin() + r.direction()*t - center);
    //record.color = color;
    return true;
  }
  return false;
}

bool Sphere::isIntersect(const Ray& r, float tmin, float tmax, float time)const{
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
