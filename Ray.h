#pragma once
#ifndef RAY_H
#define RAY_H
#include <Eigen/Dense>
#include <ostream>
#include <math.h>
#include "Primitive.h"

using namespace Eigen;

class Ray {
	private:	
		Vector4d origin;
		Vector4d direction;	

	public:
		Ray();
		Ray(Vector4d &origin, Vector4d &direction);
		Vector4d eval(float &t);
		void transform(Matrix4d &tMat);
		friend std::ostream &operator << (std::ostream &os, Ray &ray);
};

Ray *genereateRay(Camera *Cam, int iWidth, int iHeight, int i, int j, double fov = M_PI/2);

#endif
