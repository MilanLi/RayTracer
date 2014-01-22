#ifndef _ONB_H_
#define _ONB_H_

#include "Vec.h"

class ONB{
public:
  Vec U,V,W;
  ONB(){};
  ONB(const Vec& a, const Vec& b, const Vec& c){
    U = a; V = b; W = c;
  }
  void initFromU(const Vec& u);
  void initFromV(const Vec& v);
  void initFromW(const Vec& w);

  void set(const Vec& a, const Vec& b, const Vec& c){
    U = a; V = b; W = c;
  }
  void initFromUV(const Vec& u, const Vec& v);
  void initFromUW(const Vec& u, const Vec& w);
  void initFromVW(const Vec& v, const Vec& w);
  
  friend std::istream& operator>>(std::istream& is, ONB& t);
  friend std::ostream& operator<<(std::ostream& os, const ONB& t);
  friend bool operator==(const ONB& o1, const ONB& o2);

};

#endif
