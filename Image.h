#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cmath>
#include <string>
#include <fstream>
#include "Vec.h"

class Image{
public:
  Image();
  Image(int width, int height);
  Image(int width, int height, Vec background);
  bool set(int x, int y, const Vec& color);
  void writePPM(std::ostream& out);
  void readPPM(const char* file_name);
  int width(){return nx;}
  int height(){return ny;}
  Vec getPixel(int i, int j){return raster[i][j];}
private:
  Vec ** raster;
  int nx;
  int ny;
};

#endif
