#include "Vec.h"
#include "Ray.h"
#include "Image.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Perspective.h"
#include "ImageTexture.h"
#include "UVSphere.h"

#include <vector>
#include <fstream>
#include <algorithm>

float width = 500;
float height = 500;

float fov = M_PI * 45 / 180;
//set light source
float ambient = 0.1;
Vec lightSource = Vec(0, 10, -10);

Vec trace(Ray& r, std::vector<Shape*>& obj){
  HitRecord record;
  bool is_a_hit = false;
  float tmax = INFINITY;
  for(int k = 0; k < (int)obj.size(); k ++){
    if(obj[k]->intersect(r, 1, tmax, 0, record)){
      tmax = record.t;
      is_a_hit = true;
    }
  }
  //found the nearest object
  if(is_a_hit){
    //find the ray from hit point to lighting source.
    Ray lightRay(record.hit_p, normalize(lightSource - record.hit_p));
    //verify if it intersects with any objects in the scene
    for(int k = 0; k < (int)obj.size(); k++){
      //if intersection exists, set ambient color/ texture.
      float dist = (lightSource - record.hit_p).length();
      if(obj[k]->isIntersect(lightRay, 0.01, dist, 0)){
	return ((record.hit_tex)->getValue(record.uv, record.hit_p)) * ambient;
      }
    }
    //if no intersection, getValue().
    Vec illumination = (record.hit_tex)->getValue(record.uv, record.hit_p);
    //add diffuse
    Vec diffuseMaterial = Vec(1, 1, 1);
    Vec diffuseCoef = std::max(float(0), (record.normal).dot(lightRay.direction()));
    //add specular
    Vec specularMaterial = Vec(1, 1, 1);
    Vec bisector = normalize(lightRay.direction() - r.direction());
    Vec specularCoef = pow(std::max(float(0), (record.normal).dot(bisector)), float(50));
    //in ambient + diffuse + specular coefficient
    Vec localLight = diffuseCoef * diffuseMaterial + specularCoef * specularMaterial + ambient;
    //std::cout << "illumination is: " << illumination << std::endl;
    //std::cout << "localLight is: " << localLight << std::endl;
    //std::cout << "product is: " << illumination * localLight << std::endl << std::endl;
    return illumination * localLight;
  }
  else{
    return Vec(0.2, 0.2, 0.2);
  }  
}


int main(){
  //Perspective(center, gazepoint, up, ...);
  Perspective* view = new Perspective(Vec(0, 5, 0), Vec(0, 0, -15), 
                                      Vec(0, 3, -1), fov, fov*height/width, 1.0);
  std::vector<Shape*> obj;
  ImageTexture** tex = new ImageTexture*[2];
  tex[0] = new ImageTexture("./texture1.ppm");
  tex[1] = new ImageTexture("./texture3.ppm");

  obj.push_back(new UVSphere(Vec(0, 2, -15), 2, tex[0]));
  //obj.push_back(new UVSphere(Vec(3, 1, -15), 1, tex[0]));
  //obj.push_back(new UVSphere(Vec(-3, 1, -15), 1, tex[0]));
  //obj.push_back(new UVSphere(Vec(400, 250, -1000), 200, tex[1]));
  
  //set ground texture
  obj.push_back(new Triangle(Vec(-25, 0, 0), Vec(0, 0, 0),
                             Vec(25, 0, -40), Vec(1, 1, 0),
                             Vec(-25, 0, -40), Vec(0, 1, 0),
                             tex[1]));
  obj.push_back(new Triangle(Vec(-25, 0, 0), Vec(0, 0, 0),
                             Vec(25, 0, 0), Vec(1, 0, 0),
                             Vec(25, 0, -40), Vec(1, 1, 0),
                             tex[1]));
  Image* im = new Image(500, 500);
  for(int i = 0; i < 500; i++){
    for(int j = 0; j < 500; j++){      
      //Ray pixelRay(Vec(i, j, 0), Vec(0, 0, -1));
      Ray pixelRay(view->getRay(i/width, j/height));
      Vec pixelValue = trace(pixelRay, obj);
      im->set(i, j, pixelValue);
    }
  }
  delete view;
  std::ofstream file("./view.ppm");
  im->writePPM(file);
  file.close();
  delete im;
  delete []tex;
  return 0;
}
