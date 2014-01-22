#include "Triangle.h"

Triangle:: Triangle(const Vec& _p0, const Vec& _uv0, const Vec& _p1, const Vec& _uv1,
                    const Vec& _p2, const Vec& _uv2, float _reflectionCoef, float _refractionCoef, Texture* _tex)
  :p0(_p0), p1(_p1), p2(_p2), reflectionCoef(_reflectionCoef), refractionCoef(_refractionCoef), tex(_tex)
{
  uv[0] = _uv0;
  uv[1] = _uv1;
  uv[2] = _uv2;
}

bool Triangle:: intersect(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const{
  float tval;
  float A(p0.x - p1.x), B(p0.y - p1.y), C(p0.z - p1.z);
  float D(p0.x - p2.x), E(p0.y - p2.y), F(p0.z - p2.z);
  float G(r.direction().x), H(r.direction().y), I(r.direction().z);
  float J(p0.x - r.origin().x), K(p0.y - r.origin().y), L(p0.z - r.origin().z);

  float denom = (A * (E*I - H*F) + B * (G*F - D*I) + C * (D*H - E*G));
  float beta = (J * (E*I - H*F) + K * (G*F - D*I) + L * (D*H - E*G)) / denom;
  if(beta <= 0 || beta >= 1) return false;

  float gamma = (I * (A*K - J*B) + H * (J*C - A*L) + G * (B*L - K*C)) / denom;
  if(gamma <= 0 || beta + gamma >= 1) return false;

  tval = -(F * (A*K - J*B) + E * (J*C - A*L) + D * (B*L - K*C)) / denom;
  if(tval >= tmin && tval <= tmax){
    record.t = tval;
    record.hit_p = (r.origin() + r.direction() * tval);
    record.reflect = reflectionCoef;
    record.transparency = refractionCoef;
    record.normal = normalize((p1-p0).cross(p2-p0));
    
    record.uv.x = uv[0].x + beta * (uv[1].x - uv[0].x) + gamma * (uv[2].x - uv[0].x); 
    record.uv.y = uv[0].y + beta * (uv[1].y - uv[0].y) + gamma * (uv[2].y - uv[0].y);
    record.uv.z = 0;
    record.hit_tex = tex;
    //record.color = color;
    return true;
  }
  return false;
}

bool Triangle:: isIntersect(const Ray& r, float tmin, float tmax, float time)const{
  float tval;
  float A(p0.x - p1.x), B(p0.y - p1.y), C(p0.z - p1.z);
  float D(p0.x - p2.x), E(p0.y - p2.y), F(p0.z - p2.z);
  float G(r.direction().x), H(r.direction().y), I(r.direction().z);
  float J(p0.x - r.origin().x), K(p0.y - r.origin().y), L(p0.z - r.origin().z);

  float denom = (A * (E*I - H*F) + B * (G*F - D*I) + C * (D*H - E*G));
  float beta = (J * (E*I - H*F) + K * (G*F - D*I) + L * (D*H - E*G)) / denom;
  if(beta <= 0 || beta >= 1) return false;

  float gamma = (I * (A*K - J*B) + H * (J*C - A*L) + G * (B*L - K*C)) / denom;
  if(gamma <= 0 || beta + gamma >= 1) return false;

  tval = -(F * (A*K - J*B) + E * (J*C - A*L) + D * (B*L - K*C)) / denom;
  return tval >= tmin && tval <= tmax;
}
