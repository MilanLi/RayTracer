#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Vec.h"

//ADT
class Texture{
public:
  virtual Vec getValue(const Vec&, const Vec&) const = 0;
};

#endif
