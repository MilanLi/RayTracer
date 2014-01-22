#include "Vec.h"
#include "Ray.h"
#include "Image.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Perspective.h"

#include <vector>
#include <fstream>

int main(){
  float width = 500;
  float height = 500;
  HitRecord record;
  bool is_a_hit;
  float tmax;
  float fov = M_PI * 30 / 180;
  Perspective* view = new Perspective(Vec(0, 0, -400), Vec(250, 250, -1000), 
                                      Vec(0, 1, 0), fov, fov*height/width, 1.0);
  std::vector<Shape*> obj;
  obj.push_back(new Sphere(Vec(250, 250, -1000), 150, Vec(0, 0, 1)));
  obj.push_back(new Triangle(Vec(300, 600, -800), Vec(0, 100, -1000), Vec(450, 20, -1000), Vec(1, 0, 0)));
  Image* im = new Image(500, 500);
  for(int i = 0; i < 500; i++){
    for(int j = 0; j < 500; j++){
      tmax = 100000;
      is_a_hit = false;
      //Ray pixelRay(Vec(i, j, 0), Vec(0, 0, -1));
      Ray pixelRay(view->getRay(i/width, j/height));
      for(int k = 0; k < (int)obj.size(); k ++){
	if(obj[k]->intersect(pixelRay, 0.00001, tmax, 0, record)){
	  tmax = record.t;
	  is_a_hit = true;
	}
      }
      if(is_a_hit){
	im->set(i, j, record.color);
      }
      else{
	im->set(i, j, Vec(0.2, 0.2, 0.2));
      }
    }
  }
  std::ofstream file("./view.ppm");
  im->writePPM(file);
  file.close();
  return 0;
}
