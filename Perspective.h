#ifndef _PERSPECTIVE_H_
#define _PERSPECTIVE_H_

#include <cmath>
#include "ONB.h"
#include "Ray.h"

class Perspective{
public:
  Vec center;
  float distance;
  ONB axis;
  float left, right, bottom, top;
  Perspective(){}
  Perspective(const Perspective& rhs){
    center = rhs.center;
    distance = rhs.distance;
    axis = rhs.axis;
    left = rhs.left;
    right = rhs.right;
    bottom = rhs.bottom;
    top = rhs.top;
  }
  Perspective(const Vec& c, const Vec& gaze, const Vec& up, float l, float r, float b, float t, float d){
    center = c;
    distance = d;
    axis.initFromVW(up, center-gaze);
    left = l;
    right = r;
    bottom = b;
    top = t;
  }

  Perspective(const Vec& c, const Vec& gaze, const Vec& up, float fovx, float fovy, float d){
    center = c;
    distance = d;
    axis.initFromVW(up, center-gaze);
    left = -tan(fovx/2) * d;
    right = -left;
    bottom = -tan(fovy/2) *d;
    top = -bottom;
  }

  Ray getRay(float i, float j){ // pixel i / nx
    float u0 = left + (right - left) * i;
    float v0 = bottom + (top - bottom) * j; 
    Vec Target = center + axis.U * u0 + axis.V * v0 - axis.W * distance;
    return Ray(center, normalize(Target - center));
  }
};

#endif
