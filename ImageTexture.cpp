#include "ImageTexture.h"
#include <iostream>

ImageTexture:: ImageTexture(const char* filename){
  image = new Image();
  image->readPPM(filename);
  //std::cout << filename << " successfully loaded!\n";
}

Vec ImageTexture:: getValue(const Vec& uv, const Vec& p)const{
  float u = uv.x - int(uv.x);
  float v = uv.y - int(uv.y);
  u *= (image->width() -3);
  v *= (image->height() -3);

  int iu = (int)u;
  int iv = (int)v;
  float tu = u - iu;
  float tv = v - iv;
  //std::cout << u << " " << v << std::endl;

  //bilinear interpolate
  Vec c = image->getPixel(iu, iv)*(1-tu)*(1-tv)+
          image->getPixel(iu+1, iv)*tu*(1-tv)+
          image->getPixel(iu, iv+1)*(1-tu)*tv+
          image->getPixel(iu+1, iv+1)*tu*tv;
  return c;
}
