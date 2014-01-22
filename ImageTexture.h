#ifndef _IMAGE_TEXTURE_H_
#define _IMAGE_TEXTURE_H_

#include "Texture.h"
#include "Image.h"

class ImageTexture : public Texture{
public:
  Image* image;
  ImageTexture(const char* filename);
  virtual Vec getValue(const Vec& uv, const Vec& p)const;
};

#endif
