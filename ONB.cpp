#include "ONB.h"
#define ONB_EPSILON 0.01

void ONB:: initFromU(const Vec& u){
  Vec n(1, 0, 0);
  Vec m(0, 1, 0);
  U = normalize(u);
  V = U.cross(n);
  if(V.length() < ONB_EPSILON){
    V = U.cross(m);
  }
  W = U.cross(V);
}

void ONB:: initFromV(const Vec& v){
  Vec n(1, 0, 0);
  Vec m(0, 1, 0);
  V = normalize(v);
  U = V.cross(n);
  if(U.length() < ONB_EPSILON){
    U = V.cross(m);
  }
  W = U.cross(V);
}

void ONB:: initFromW(const Vec& w){
  Vec n(1, 0, 0);
  Vec m(0, 1, 0);
  W = normalize(w);
  U = W.cross(n);
  if(U.length() < ONB_EPSILON){
    U = W.cross(m);
  }
  V = W.cross(U);
}

void ONB:: initFromUV(const Vec& u, const Vec& v){
  U = normalize(u);
  W = normalize(U.cross(v));
  V = W.cross(U);
}

void ONB:: initFromUW(const Vec& u, const Vec& w){
  U = normalize(u);
  V = normalize(w.cross(U));
  W = U.cross(V);
}

void ONB:: initFromVW(const Vec& v, const Vec& w){
  W = normalize(w);
  U = normalize(v.cross(W));
  V = W.cross(U);
}

bool operator==(const ONB& o1, const ONB& o2){
  return(o1.U == o2.U && o1.V == o2.V &&  o1.W == o2.W);
}

// std::istream& operator>>(std::istream& is, ONB & t){
//   Vec new_u, new_v, new_w;
//   is >> new_u >> new_v >> new_w;
//   t. initFromUV(new_u, new_v);
//   return is;
// }

std::ostream& operator<<(std::ostream& os, const ONB& t){
  os << t.U << "\n" << t.V << "\n" << t.W << "\n";
  return os;
}
