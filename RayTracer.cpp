#include <iostream>
#include <vector>
//#include <CL/opencl.hpp>
#include "eigen-3.4.0/Eigen/Dense"
#include "Ray.h"
#include "Primitive.h"
#include "Parser.h"
#include "Light.h"
#include "CImg-3.3.1/CImg.h"

using std::cout, std::endl;
using namespace cimg_library;

int main(int argc, char *argv[]) {
  if(argc <= 1) {
    cout << "Error, No Input File Specified." << endl;
    exit(EXIT_FAILURE);
  }
  if(argc <= 2) {
    cout << "Error, No Output File Specified." << endl;
    exit(EXIT_FAILURE);
  }

  int *color;
  int render = 0;
  double ambient;
  char *filename = argv[1] ;
  char *outfile = argv[2];
  ParseData data;
  int height, width, FOV;
  Camera *camera;
  Ray *ray;
  vector<Primitive*> prims;
  vector<Light*> lights;
  double minT;
  Hit hit, minHit;
  
  parseFile(filename, data);
  height = data.height;
  width = data.width;
  FOV = data.FOV;
  ambient = data.ambient;
  camera = data.camera;
  prims = data.prims;
  lights = data.lights;
  

  CImg<unsigned char> outImage(width, height, 1, 3, 0);

  int count = 0;
  cout << "Rendering: " << endl;
  for(int i = 0; i < width; ++i)  {
    for(int j = 0; j < height; ++j) {
      minT = DBL_MAX;
      ray = generateRay(*camera, width, height, i, j) ;
      
      // Determine Visible Pixels, and there associated color data.
      for(int k = 0; k < prims.size(); ++k){
        if(prims[k]->isHit(transformRay(ray,prims[k]->getLocal() ), hit)) {
          if(hit.t < minT){
            minT = hit.t;
            minHit = hit;
            render = 1;
          }
        }
      }
      Ray* shadowRay = new Ray;
      if(render){
        Hit shadowHit;
        bool vis = true;
        for(int l = 0; l < lights.size(); ++l) {
          Ray *shadowRay = new Ray;
          shadowRay->origin = ray->eval(minT) + 2 * minHit.normal;
          shadowRay->direction = lights[l]->getDirection(shadowRay->origin);
          shadowRay->tNear = (lights[l]->getPoint() - shadowRay->origin).norm();
          for(int m = 0; m < prims.size(); ++m) {
            if(prims[m]->isHit(transformRay(shadowRay, prims[m]->getLocal()), shadowHit)) {
              vis = false;
              break;
            }
          }
          color = lights[l]->illuminate(transformRay(ray, lights[l]->getLocal()), minHit, vis);
        }

        for(int m = 0; m < 3; ++m) {
          color[m] += (ambient * minHit.material.diffuse[m]);
          if(color[m] > 255) color[m] = 255;
          if(color[m] < 0) color[m] = 0;
        }
        outImage(i,j,0,0) = color[0];
        outImage(i,j,0,1) = color[1];
        outImage(i,j,0,2) = color[2];
        render = 0;
      }
    } 
  }

  outImage.save_png(outfile);
  cout << "Displaying Image: " << endl;
  CImgDisplay disp(outImage);

  while(!disp.is_closed()){
    disp.wait();
  }

  cout << "Done." << endl;
	return 0;
}
