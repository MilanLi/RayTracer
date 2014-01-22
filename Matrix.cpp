#include "Matrix.h"

Matrix::Matrix(const Matrix& orig){
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      x[i][j] = rhs.x[i][j];
    }
  }
}

void Matrix::invert(){
  float det = determinant();
  Matrix inverse;
  inverse.x[0][0] = det3(x[1][1], x[1][2], x[1][3],
                         x[2][1], x[2][2], x[2][3],
                         x[3][1], x[3][2], x[3][3]) / det;
  inverse.x[0][1] =-det3(x[0][1], x[0][2], x[0][3],
                         x[2][1], x[2][2], x[2][3],
                         x[3][1], x[3][2], x[3][3]) / det;
  inverse.x[0][2] = det3(x[0][1], x[0][2], x[0][3],
                         x[1][1], x[1][2], x[1][3],
                         x[3][1], x[3][2], x[3][3]) / det;
  inverse.x[0][3] =-det3(x[0][1], x[0][2], x[0][3],
                         x[1][1], x[1][2], x[1][3],
                         x[2][1], x[2][2], x[2][3]) / det;

  inverse.x[1][0] =-det3(x[1][0], x[1][2], x[1][3],
                         x[2][0], x[2][2], x[2][3],
                         x[3][0], x[3][2], x[3][3]) / det;
  inverse.x[1][1] = det3(x[0][0], x[0][2], x[0][3],
                         x[2][0], x[2][2], x[2][3],
                         x[3][0], x[3][2], x[3][3]) / det;
  inverse.x[1][2] =-det3(x[0][0], x[0][2], x[0][3],
                         x[1][0], x[1][2], x[1][3],
                         x[3][0], x[3][2], x[3][3]) / det;
  inverse.x[1][3] = det3(x[0][0], x[0][2], x[0][3],
                         x[1][0], x[1][2], x[1][3],
                         x[2][0], x[2][2], x[2][3]) / det;

  inverse.x[2][0] = det3(x[1][0], x[1][1], x[1][3],
                         x[2][0], x[2][1], x[2][3],
                         x[3][0], x[3][1], x[3][3]) / det;
  inverse.x[2][1] =-det3(x[0][0], x[0][1], x[0][3],
                         x[2][0], x[2][1], x[2][3],
                         x[3][0], x[3][1], x[3][3]) / det;
  inverse.x[2][2] = det3(x[0][0], x[0][1], x[0][3],
                         x[1][0], x[1][1], x[1][3],
                         x[3][0], x[3][1], x[3][3]) / det;
  inverse.x[2][3] =-det3(x[0][0], x[0][1], x[0][3],
                         x[1][0], x[1][1], x[1][3],
                         x[2][0], x[2][1], x[2][3]) / det;

  inverse.x[3][0] =-det3(x[1][0], x[1][1], x[1][2],
                         x[2][0], x[2][1], x[2][2],
                         x[3][0], x[3][1], x[3][2]) / det;
  inverse.x[3][1] = det3(x[0][0], x[0][1], x[0][2],
                         x[2][0], x[2][1], x[2][2],
                         x[3][0], x[3][1], x[3][2]) / det;
  inverse.x[3][2] =-det3(x[0][0], x[0][1], x[0][2],
                         x[1][0], x[1][1], x[1][2],
                         x[3][0], x[3][1], x[3][2]) / det;
  inverse.x[3][3] = det3(x[0][0], x[0][1], x[0][2],
                         x[1][0], x[1][1], x[1][2],
                         x[2][0], x[2][1], x[2][2]) / det;
  *this = inverse;
}

void Matrix::transpose(){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      float temp = x[i][j];
      x[i][j] = x[j][i];
      xf[j][i] = temp;
    }
  }
}

Matrix Matrix::getInverse() const{
  Matrix ret = *this;
  ret.invert();
  return ret;
}

Matrix Matrix::getTranspose()const{
  Matrix ret = *this;
  ret.transpose();
  return ret;
}

Matrix& Matrix::operator+=(const Matrix& rhs){
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      x[i][j] += rhs.x[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs){
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      x[i][j] -= rhs.x[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(float rhs){
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      x[i][j] *= rhs;
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& rhs){
  Matrix ret = *this;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      float sum = 0;
      for(int k = 0; k < 4; k++){
	sum += ret.x[i][k] * rhs.x[k][j];
	x[i][j] = sum;
      }
    }
  }
  return *this;
}
  
Matrix operator-(const Matrix& lhs, const Matrix& rhs){
  Matrix ret;
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      ret.x[i][j] = lhs.x[i][j] - rhs.x[i][j];
    }
  }
  return ret;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs){
  Matrix ret;
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      ret.x[i][j] = lhs.x[i][j] + rhs.x[i][j];
    }
  }
  return ret;
}

Matrix operator*(const Matrix& lhs, float rhs){
    Matrix ret;
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      ret.x[i][j] = lhs.x[i][j] * rhs;
    }
  }
  return ret;
}
Vec operator*(const Matrix& lhs, const Vec& rhs){
  Vec ret;
  ret[0] = rhs[0] * lhs.x[0][0] + rhs[1] * lhs.x[0][1] + rhs[2] * lhs.x[0][2] + lhs.x[0][3];
  ret[1] = rhs[0] * lhs.x[1][0] + rhs[1] * lhs.x[1][1] + rhs[2] * lhs.x[1][2] + lhs.x[1][3];
  ret[2] = rhs[0] * lhs.x[2][0] + rhs[1] * lhs.x[2][1] + rhs[2] * lhs.x[2][2] + lhs.x[2][3];
  float temp = rhs[0] * lhs.x[3][0] + rhs[1] * lhs.x[3][1] + rhs[2] * lhs.x[3][2] + lhs.x[3][3];
  ret /= temp;
  return ret;
}
Matrix operator*(const Matrix& lhs, const Matrix& rhs){
  Matrix ret;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      float sum = 0;
      for(int k = 0; k < 4; k++){
	sum += lhs.x[i][k] * rhs.x[k][j];
	ret.x[i][j] = sum;
      }
    }
  }
  return ret;
}

Vec transformLoc(const Matrix& lhs, const Vec& rhs){
  return lhs * rhs;
}

Vec transformVec(const Matrix& lhs, const Vec& rhs){
  Vec ret;
  ret[0] = rhs[0] * lhs.x[0][0] + rhs[1] * lhs.x[0][1] + rhs[2] * lhs.x[0][2];
  ret[1] = rhs[0] * lhs.x[1][0] + rhs[1] * lhs.x[1][1] + rhs[2] * lhs.x[1][2];
  ret[2] = rhs[0] * lhs.x[2][0] + rhs[1] * lhs.x[2][1] + rhs[2] * lhs.x[2][2];
  return ret;
}

Matrix zeroMatrix(){
  Matrix ret;
  for(int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      ret.x[i][j] = 0.0;
    }
  }
  return ret;
}

Matrix identityMatrix(){
  Matrix ret;
  ret.x[0][0] = 1;
  ret.x[0][1] = 0;
  ret.x[0][2] = 0;
  ret.x[0][3] = 0;
  ret.x[1][0] = 0;
  ret.x[1][1] = 1;
  ret.x[1][2] = 0;
  ret.x[1][3] = 0;
  ret.x[2][0] = 0;
  ret.x[2][1] = 0;
  ret.x[2][2] = 1;
  ret.x[2][3] = 0;
  ret.x[3][0] = 0;
  ret.x[3][1] = 0;
  ret.x[3][2] = 0;
  ret.x[3][3] = 1;
  return ret;
}

Matrix translate(float _x, float _y, float _z){
  Matrix ret = identityMatrix();
  ret.x[0][3] = _x;
  ret.x[1][3] = _y;
  ret.x[2][3] = _z;
  return ret;
}

Matrix scale(float _x, float _y, float _z){
  Matrix ret = zeroMatrix();
  ret.x[0][0] = _x;
  ret.x[1][1] = _y;
  ret.x[2][2] = _z;
  ret.x[3][3] = 1;
  return ret;
}

Matrix rotate(const Vec& axis, float angle){
  Vec _axis = normalize(axis);
  Matrix ret;
  float x = _axis.x;
  float y = _axis.y;
  float z = _axis.z;
  float cosine = cos(angle);
  float sine = sin(angle);
  float t = 1 - cosine;

  ret.x[0][0] = t*x*x + cosine; 
  ret.x[0][1] = t*x*y - sine*y;
  ret.x[0][2] = t*x*z + sine*y;
  ret.x[0][3] = 0;

  ret.x[1][0] = t*x*y + sine*z; 
  ret.x[1][1] = t*y*y - cosine;
  ret.x[1][2] = t*y*z - sine*x;
  ret.x[1][3] = 0;

  ret.x[2][0] = t*x*z - sine*y;
  ret.x[2][1] = t*y*z + sine*y;
  ret.x[2][2] = t*z*z + cosine;
  ret.x[2][3] = 0;

  ret.x[3][0] = 0;
  ret.x[3][1] = 0;
  ret.x[3][2] = 0;
  ret.x[3][3] = 1;

  return ret;
}

Matrix rotateX(float angle){
  Matrix ret = identityMatrix();
  float cosine = cos(angle);
  float sine = sin(angle);
  ret.x[1][1] = cosine;
  ret.x[1][2] = -sine;
  ret.x[2][1] = sine;
  ret.x[2][2] = cosine;
  return ret;
}

Matrix rotateY(float angle){
  Matrix ret = identityMatrix();
  float cosine = cos(angle);
  float sine = sin(angle);
  ret.x[0][0] = cosine;
  ret.x[0][2] = sine;
  ret.x[2][0] = -sine;
  ret.x[2][2] = cosine;
  return ret;
}

Matrix rotateZ(float angle){
  Matrix ret = identityMatrix();
  float cosine = cos(angle);
  float sine = sin(angle);
  ret.x[0][0] = cosine;
  ret.x[0][1] = -sine;
  ret.x[1][0] = sine;
  ret.x[1][1] = cosine;
  return ret;
}

Matrix viewMatrix(const Vec& eye, const Vec& gaze, const Vec& up){
  Matrix ret = identityMatrix();

  Vec w = -(normalize(gaze - eye));
  Vec u = normalize(up.cross(w));
  Vec v = w.cross(u);

  ret.x[0][0] = u.x;
  ret.x[0][1] = u.y;
  ret.x[0][2] = u.z;
  ret.x[1][0] = v.x;
  ret.x[1][1] = v.y;
  ret.x[1][2] = v.z;
  ret.x[2][0] = w.x;
  ret.x[2][1] = w.y;
  ret.x[2][2] = w.z;

  Matrix move = identityMatrix();
  move.x[0][3] = -(eye.x);
  move.x[1][3] = -(eye.y);
  move.x[2][3] = -(eye.z);
  ret = ret * move;
  return ret;
}

float determinant(){
  float det;
  det  = x[0][0] * det3(x[1][1], x[1][2], x[1][3],
                        x[2][1], x[2][2], x[2][3],
                        x[3][1], x[3][2], x[3][3]);
  det -= x[0][1] * det3(x[1][0], x[1][2], x[1][3],
                        x[2][0], x[2][2], x[2][3],
                        x[3][0], x[3][2], x[3][3]);
  det += x[0][2] * det3(x[1][0], x[1][1], x[1][3],
                        x[2][0], x[2][1], x[2][3],
                        x[3][0], x[3][1], x[3][3]);
  det -= x[0][3] * det3(x[1][0], x[1][1], x[1][2],
                        x[2][0], x[2][1], x[2][2],
                        x[3][0], x[3][1], x[3][2]);
  return det;
}

