#include "Vec.h"
#include "Ray.h"
#include "Image.h"
#include "Perspective.h"
#include "ImageTexture.h"
#include "UVSphere.h"
#include "Triangle.h"

#include <vector>
#include <fstream>
#include <algorithm>

float width = 800;
float height = 600;

//float attenuation = 0.2;
float fov = M_PI * 45 / 180;
//set light source
float ambient = 0.1;
Vec lightSource[3];

Ray reflection(const Ray& r, const Vec& normal, const Vec& p){
  return Ray(p, r.direction() - normal * (2 * (normal.dot(r.direction())) ));
}

template<typename T>
T mix(T a, T b, float m){
  return b*m + a*(1-m);
}

Vec trace(const Ray& r, const std::vector<Shape*>& obj, int times){
  if(times == 0){
    return Vec(0, 0, 0);
  }
  Vec retColor = Vec(0, 0, 0);
  HitRecord record;
  bool is_a_hit = false;
  float tmax = INFINITY;
  for(int k = 0; k < (int)obj.size(); k ++){
    if(obj[k]->intersect(r, 0.01, tmax, 0, record)){
      tmax = record.t;
      is_a_hit = true;
    }
  }
  //found the nearest object
  if(is_a_hit){
    //find the ray from hit point to lighting source. 
    bool inside = false;
    
    if(r.direction().dot(record.normal) > 0){
      record.normal = -record.normal;
      inside = true;
    }
    
    //fresneleffect!!
    float facingratio = -r.direction().dot(record.normal);
    float fresneleffect = mix<float>(pow(1 - facingratio, 3), 1, 0.1);    
    
    Ray reflectRay = reflection(r, record.normal, record.hit_p);
    //Vec reflectionValue = trace(reflectRay, obj, times-1);
    //refraction!!!    
    //Vec refractionValue = Vec(0, 0, 0);
    
    float ratio = 1.1;
    float eta_ratio = (inside)? ratio : 1/ratio;
    float cos_angle = -record.normal.dot(r.direction());
    float cosine_theta = sqrt(1 - eta_ratio*eta_ratio*(1 - cos_angle * cos_angle));
    Vec refraDir = normalize(r.direction() * eta_ratio + record.normal * (eta_ratio*cos_angle - cosine_theta));
    Ray refractRay = Ray(record.hit_p, refraDir);

    Vec reflec_refract = trace(reflectRay, obj, times-1) * record.reflect * fresneleffect
      + trace(refractRay, obj, times-1) * record.transparency * (1-fresneleffect);
    
    Ray lightRay[3];
    for(int i = 0; i < 3; i++){
      lightRay[i] = Ray(record.hit_p, normalize(lightSource[i] - record.hit_p));
      //verify if it intersects with any objects in the scene
      bool is_blocked = false;
      for(int k = 0; k < (int)obj.size(); k++){
	//if intersection exists, set ambient color/ texture.
	float dist = (lightSource[i] - record.hit_p).length();
	if(obj[k]->isIntersect(lightRay[i], 0.001, dist, 0)){
	  retColor += ((record.hit_tex)->getValue(record.uv, record.hit_p)) * ambient;
	  is_blocked = true;
	  break;
	}
      }
      //if no intersection, getValue().
      if(!is_blocked){
	Vec illumination = (record.hit_tex)->getValue(record.uv, record.hit_p);
	//add diffuse
	Vec diffuseMaterial = Vec(1, 1, 1);
	Vec diffuseCoef = std::max(float(0), (record.normal).dot(lightRay[i].direction()));
	//add specular
	Vec specularMaterial = Vec(1, 1, 1);
	Vec bisector = normalize(lightRay[i].direction() - r.direction());
	Vec specularCoef = pow(std::max(float(0), (record.normal).dot(bisector)), float(50));
	//in ambient + diffuse + specular coefficient
	Vec localLight = diffuseCoef * diffuseMaterial + specularCoef * specularMaterial + ambient;
	retColor += illumination * localLight;
      }
      retColor += reflec_refract;
    }
      
  }
  else{
    retColor += Vec(0, 0, 0);
  }
  return retColor/3;
}


int main(){
  lightSource[0] = Vec(0, 10, -15);
  lightSource[1] = Vec(5, 10, -15);
  lightSource[2] = Vec(-5, 10, -15);
  //lightSource[1] = Vec(-2, 5, 0);
  //lightSource[2] = Vec(2, 5, 0);
  
  //Perspective(center, gazepoint, up, ...);
  Perspective* view = new Perspective(Vec(0, 10, 0), Vec(0, 2, -15), 
                                      Vec(0, 3, -1), fov, fov*height/width, 1.0);
  std::vector<Shape*> obj;
  ImageTexture** tex = new ImageTexture*[5];
  tex[0] = new ImageTexture("./black.ppm");
  tex[1] = new ImageTexture("./football.ppm");
  tex[2] = new ImageTexture("./texture1.ppm");
  tex[3] = new ImageTexture("./checker.ppm");
  tex[4] = new ImageTexture("./wood.ppm");

  obj.push_back(new UVSphere(Vec(4.5, 2, -16), 2, 1, 1, tex[0]));
  obj.push_back(new UVSphere(Vec(0, 2, -15), 2, 0.1, 0, tex[1]));
  obj.push_back(new UVSphere(Vec(-4.5, 2, -14), 2, 0.1, 0, tex[2]));
  //obj.push_back(new UVSphere(Vec(400, 250, -1000), 200, tex[1]));
  
  //set ground texture
  obj.push_back(new Triangle(Vec(-25, 0, 0), Vec(0, 0, 0),
                             Vec(25, 0, -40), Vec(1, 1, 0),
                             Vec(-25, 0, -40), Vec(0, 1, 0),
                             1, 0, tex[3]));
  obj.push_back(new Triangle(Vec(-25, 0, 0), Vec(0, 0, 0),
                             Vec(25, 0, 0), Vec(1, 0, 0),
                             Vec(25, 0, -40), Vec(1, 1, 0),
                             1, 0, tex[3]));
  Image* im = new Image(width, height);
  for(int i = 0; i < width; i++){
    for(int j = 0; j < height; j++){      
      //Ray pixelRay(Vec(i, j, 0), Vec(0, 0, -1));
      Ray pixelRay(view->getRay(i/width, j/height));
      Vec pixelValue = trace(pixelRay, obj, 4);
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
