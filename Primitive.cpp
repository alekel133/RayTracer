#include "Primitive.h"

//~~~~~~~~~~~~~~~~~~~~~~~ Primitive ~~~~~~~~~~~~~~~~~~~~~~~~~//
Primitive::Primitive() {
	this->name = (char *) malloc(32*sizeof(char*));
	strcpy(name, "None");
	this->parent = nullptr;	
	this->children = nullptr;
	this->color = (double *) malloc(3*sizeof(double*));
	this->color[0] = 0;
	this->color[1] = 0;
	this->color[2] = 0;
	this->mat = mat.Identity();
}

Primitive::~Primitive(){
	name = nullptr;
	free(name);
	color = nullptr;
	free(color);
}

bool Primitive::isHit(Ray &ray, hit &hit) {
	hit.t = 0;
	return false;
}

Matrix4d Primitive::getLocal() {
	if(parent == nullptr) {
		return this->mat;
	}
	return this->mat * this->parent->getLocal();
}

Matrix4d Primitive::getWorld() {
	if(parent == nullptr) {
		return this->mat.inverse();
	}

	return this->parent->getWorld() * this->mat.inverse();
}

std::ostream &operator<<(std::ostream &os, Primitive &prime) {
	os << "Primitve ( Name: " << prime.name << ", Color: (" << prime.color[0] <<
		"," << prime.color[1] << "," << prime.color[2] << "))";

	return os;
}

//~~~~~~~~~~~~~~~~~~~~~~~ Camera ~~~~~~~~~~~~~~~~~~~~~~~~~//
Camera::Camera() {
	this->parent = nullptr;
	this->children = nullptr;
	this->eye = Vector4d(0,0,0,1);
	this->direction = Vector4d(0,0,-1,0);
	this->up = Vector4d(0,1,0,0);
	this->side = Vector4d(1,0,0,0);
	this->mat << side, up, direction, Vector4d(0,0,0,1);
}

std::ostream &operator<<(std::ostream &os, Camera &cam) {
	os << "Camera ( Eye:[" << cam.eye.transpose() << "], Direction:[" << cam.direction.transpose() <<
		"], Up:[" << cam.up.transpose() << "], Side:[" << cam.side.transpose() << "])";
	
	return os;
}

//~~~~~~~~~~~~~~~~~~~~~~~ Sphere ~~~~~~~~~~~~~~~~~~~~~~~~~//
Sphere::Sphere() {
	this->radius = 1;
	this->origin = Vector4d(0,0,0,1);
}

Sphere::Sphere(double *color) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}

bool Sphere::isHit(Ray &ray, hit &hit) {
	return false;	
}

std::ostream &operator<<(std::ostream &os, Sphere &sphere) {
	os << "Sphere ( Name: " << sphere.name << ", Origin:[" << sphere.origin.transpose() << "], Radius: " 
		<< sphere.radius << ", Color: (" << sphere.color[0] << "," 
		<< sphere.color[1] << "," << sphere.color[2] << "))";
	return os;
}

//~~~~~~~~~~~~~~~~~~~~~~~ Plane ~~~~~~~~~~~~~~~~~~~~~~~~~//
Plane::Plane() {
	this->origin = Vector4d(0,0,0,1);
	this->normal = Vector4d(0,1,0,0);
}

bool Plane::isHit(Ray &ray, hit &hit) {
	return false;
}

std::ostream &operator<<(std::ostream &os, Plane &plane) {
	os << "Plane ( Name: " << plane.name << ", Origin:[" << plane.origin.transpose() << "], Normal:["
		<< plane.normal.transpose() << "]";
	return os;
}
