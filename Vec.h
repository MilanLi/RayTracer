#ifndef __VEC_H__
#define __VEC_H__
#include <math.h>
#include <iostream>

class Vec{
public:
  float x, y, z;
  Vec(): x(float(0)), y(float(0)), z(float(0)){}
  Vec(const float t): x(t), y(t), z(t){}
  Vec(float _x, float _y, float _z): x(_x), y(_y), z(_z){}
  Vec(const Vec& v): x(v.x), y(v.y), z(v.z){}
  
  float length()const{
    return sqrt(x*x + y*y + z*z);
  }
  
  Vec operator*(const Vec& rhs) const{
    Vec ret;
    ret.x = x * rhs.x;
    ret.y = y * rhs.y;
    ret.z = z * rhs.z;
    return ret;
  }
  Vec operator*(float t) const{
    Vec ret;
    ret.x = x * t;
    ret.y = y * t;
    ret.z = z * t;
    return ret;
  }
  float dot(const Vec& rhs) const{
    return x*rhs.x + y*rhs.y + z*rhs.z;
  }
  Vec cross(const Vec& rhs) const{
    Vec ret;
    ret.x = y * rhs.z - z * rhs.y;
    ret.y = z * rhs.x - x * rhs.z;
    ret.z = x * rhs.y - y * rhs.x;
    return ret;
  }
  Vec operator-(const Vec& rhs) const{
    Vec ret;
    ret.x = x - rhs.x;
    ret.y = y - rhs.y;
    ret.z = z - rhs.z;
    return ret;
  }
  Vec operator+(const Vec& rhs) const{
    return Vec(x+rhs.x, y+rhs.y, z+rhs.z);
  }
  Vec& operator+=(const Vec& rhs){
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }
  Vec& operator-=(const Vec& rhs){
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }
  bool operator==(const Vec& rhs)const{
    return (x == rhs.x && y == rhs.y && z == rhs.z);
  }
  Vec operator-() const{
    return Vec(-x, -y, -z);
  }
  Vec operator/(float t) const{
    return Vec(x/t, y/t, z/t);
  }
  friend Vec normalize(const Vec& rhs){
    float len = rhs.length();
    if(len){
      return rhs/len;  
    }
    return rhs;
  }

  friend std::ostream& operator<<(std::ostream& s, const Vec& v){
    s << '[' << v.x << ", " << v.y << ", " << v.z <<']';
    return s;
  }
};

#endif
