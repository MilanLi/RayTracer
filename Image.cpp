#include "Image.h"
#include <iostream>
#include <stdlib.h>

Image:: Image(){}

Image:: Image(int width, int height){
  nx = width;
  ny = height;
  raster = new Vec* [nx];
  for(int i = 0; i < nx; i++){
    raster[i] = new Vec[ny];
  }
}

Image:: Image(int width, int height, Vec background){
  nx = width;
  ny = height;
  raster = new Vec*[nx];
  for(int i = 0; i < nx; i++){
    raster[i] = new Vec[ny];
    for(int j = 0; j < ny; j++){
      raster[i][j] = background;
    }
  }
}

bool Image:: set(int x , int y, const Vec& color){
  if(x < 0 || x > nx) return false;
  if(y < 0 || y > ny) return false;

  raster[x][y] = color;
  return true;
}

void Image:: writePPM(std::ostream& out){
  out << "P3\n";
  out << nx << ' ' << ny << '\n';
  out << "255\n";

  int i, j;
  int red, green, blue;

  for(i = ny-1; i >=0; i--){
    for (j = 0; j < nx; j++){
      red = (int)(255 * raster[j][i].x);
      green = (int)(255 * raster[j][i].y);
      blue = (int)(255 * raster[j][i].z);

      if(red > 255) red = 255;
      if(green > 255) green = 255;
      if(blue > 255) blue = 255;
      
      out << red << '\n' << green << '\n' << blue << '\n';
    }
  }
}

void Image:: readPPM(const char* file_name){
  std::ifstream in;
  in.open(file_name);
  if(!in.is_open()){
    std::cerr << "error open file!\n";
    exit(1);
  }

  char ch, type;
  int red, green, blue;
  int i, j, cols, rows;
  int num;
  in.get(ch);
  in.get(type);
  in >> cols >> rows >> num;
  nx = cols;
  ny = rows;
  raster = new Vec*[nx];
  for(i = 0; i < nx; i++){
    raster[i] = new Vec[ny];
  }
  //clean up newline
  in.get(ch);

  for(i = ny-1; i >=0; i--){
    for(j = 0; j < nx; j++){
      in >> red >> green >> blue;
      //in.get(green);
      //in.get(blue);
      raster[j][i] = Vec(float(red)/255.0,
                         float(green)/255.0,
                         float(blue)/255.0);
    }
  }
}
