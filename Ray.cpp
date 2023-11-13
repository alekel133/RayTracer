#include "Ray.h"

// Default constructor, defines ray from origin with no direction
Ray::Ray() {
	this->origin = Vector4d(0,0,0,0);
	this->direction = Vector4d(0,0,0,0);
}

// Defines a ray at origin, moving in direction
Ray::Ray(Vector4d &origin, Vector4d &direction) {
	this->origin = origin;
	this->origin(3) = 1;
	this->direction = direction;
}

// Returns Evaluated Ray Euation as a Ponit
Vector4d Ray::eval(float &t) {
	return (this->direction * t) + this->origin;
}

// Applies transformation to underlying data in a Ray
void Ray::transform(Matrix4d &tMat) {
	this->origin = tMat * this->origin;
	this->direction = tMat * this->origin;
}

std::ostream &operator << (std::ostream &os, Ray &ray) {
	os << "Ray: [" <<ray.origin.transpose() << "]" << " + " << "[" <<ray.direction.transpose() 
		<< "]" << "t";
	return os;
}

Ray *generateRay(Camera *Cam, int iWidth, int iHeight, int i, int j, double fov = M_PI/2) {

}

