#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vec.h"
#include <iostream>
#include "iomanip.h"
#include <math.h>

class Matrix{
public:
  Matrix(){}
  Matrix(const Matrix& orig);
  void invert();
  void transpose();
  Matrix getInverse() const;
  Matrix getTranspose()const;
  Matrix& operator+=(const Matrix& rhs);
  Matrix& operator-=(const Matrix& rhs);
  Matrix& operator*=(const Matrix& rhs);
  Matrix& operator*=(float rhs);
  
  friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
  friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
  friend Vec operator*(const Matrix& lhs, const Vec& rhs);
  friend Matrix operator*(const Matrix& lhs, float rhs);

  friend Vec transformLoc(const Matrix& lhs, const Vec& rhs);
  friend Vec transformVec(const Matrix& lhs, const Vec& rhs);
  friend Matrix zeroMatrix();
  friend Matrix identityMatrix();
  friend Matrix translate(float _x, float _y, float _z);
  friend Matrix scale(float _x, float _y, float _z);
  friend Matrix rotate(const Vec& axis, float angle);
  friend Matrix rotateX(float angle);
  friend Matrix rotateY(float angle);
  friend Matrix rotateZ(float angle);
  friend Matrix viewMatrix(const Vec& eye, const Vec& gaze, const Vec& up);
  float determinant();
  float x[4][4];
};

inline float det3(float a, float b, float c, float d, float e, float f, float g, float h, float i){
  return a*e*i + d*h*c + g*b*f + g*e*c + d*b*i + a*h*f;
}

#endif
