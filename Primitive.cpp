#include "Primitive.h"
#include <iostream>

//~~~~~~~~~~~~~~~~~~~~~~~ Primitive ~~~~~~~~~~~~~~~~~~~~~~~~~//
Primitive::Primitive() {
  this->name = "None";
	this->parent = (Primitive *) malloc(sizeof(Primitive *));
	this->children = nullptr;
  this->material = Material();
  this->mat = mat.Identity();
}

Primitive::~Primitive(){
	parent = nullptr;
  free(parent);
}

bool Primitive::isHit(Ray *ray, Hit &hit) {
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

std::ostream &operator <<(std::ostream &os, Primitive &prime) {
  prime.print(os);
  return os;
}
//~~~~~~~~~~~~~~~~~~~~~~~ Camera ~~~~~~~~~~~~~~~~~~~~~~~~~//
Camera::Camera() {
	this->parent = nullptr;
	this->children = nullptr;
  this->mat = mat.Identity();
}

bool Camera::isHit(Ray *ray, Hit &hit) {
  return false;
}
void Camera::print(std::ostream &os) {
	os << "Camera ( Eye:[" << (getWorld() * Vector4d(0,0,0,1)).transpose() << "], Direction:[" << (getWorld()*Vector4d(0,0,1,0)).transpose() <<
		"], Up:[" << (getWorld()*Vector4d(0,1,0,0)).transpose() << "], Side:[" << (getWorld()*Vector4d(1,0,0,0)).transpose() << "])";
}

//~~~~~~~~~~~~~~~~~~~~~~~ Sphere ~~~~~~~~~~~~~~~~~~~~~~~~~//
Sphere::Sphere() {
  this->material = Material();
}

Sphere::Sphere(Material &material) {
  this->material = material;
}

bool Sphere::isHit(Ray *ray, Hit &hit) {
  hit.material = material;
  Vector4d m = ray->origin - origin;
  double b = ray->direction.dot(m);
  double c = m.dot(m) - 4;
  
  double disc = (b*b)-c;
  if(disc < 0){
    return false;
  }
  
  double t0 = -b - sqrt(disc);
  double t1 = -b + sqrt(disc);


  if(t1 < 0) {
    return false;
  }

  if(t0 < 0){
    if(t1 > ray->tNear) return false;
    hit.t = t1;
    Vector4d point = ray->eval(hit.t);
    Vector4d normal((getLocal() * point)-Vector4d(0,0,0,1));
    hit.normal = (getWorld() * normal).normalized();
    return true;
  }

  if(t1 != t0) {
    hit.t = std::min(t0, t1);
    if(hit.t > ray->tNear) return false;
    Vector4d point = ray->eval(hit.t);
    Vector4d normal((getLocal() * point)-origin);
    hit.normal = (getWorld() * normal).normalized();
    return true;
  }
  
  if(t0 > ray->tNear) return false;
  hit.t = t0;
  Vector4d point = ray->eval(hit.t);
  Vector4d normal((getLocal() * point)-origin);
  hit.normal = (getWorld() * normal).normalized();
  return true;
}
void Sphere::print(std::ostream &os) {
	os << "Sphere ( Name: " << name << ", Origin:[" << (getWorld()*Vector4d(0,0,0,1)).transpose() << "], Radius: " 
		<< (getWorld()*Vector4d(1,0,0,0)).norm();
}

//~~~~~~~~~~~~~~~~~~~~~~~ Plane ~~~~~~~~~~~~~~~~~~~~~~~~~//
bool Plane::isHit(Ray *ray, Hit &hit) {
  hit.material = material;
  Vector4d eye = ray->origin;
  Vector4d direction = ray->direction;
  Vector4d normal = Vector4d(0,1, 0, 0);
  Vector4d origin = Vector4d(0,0,0,1);
  double bottom = normal.dot(direction);
  if(bottom == 0) return false;
  double invD = 1/bottom;
  double t = (origin-eye).dot(normal) * invD;

  if(t >= 0){
    if(t > ray->tNear) return false;
    hit.t = t;
    hit.normal = (getWorld()* Vector4d(0,-1,0,0)).normalized();
    return true;
  }

  return false;
}

void Plane::print(std::ostream &os) {
	os << "Plane ( Name: " << name << ", Origin:[" << (getWorld()*Vector4d(0,0,0,1)).transpose() << "], Normal:["
		<< (getWorld()*Vector4d(0,1,0,0)).transpose() << "]";
}


//----------------------- Mesh --------------------------------//
Mesh::Mesh() {
  this->vSize = 0;
  this->fSize = 0;
}

bool Mesh::isHit(Ray *ray, Hit &hit) {
  double t;
  hit.t = DBL_MAX;
  for(int i = 0; i < faces.size(); ++i){
    hit.material = material;
    Vector3d direction, eye, p, AB, AC, pvec,tvec,qvec;
    direction << ray->direction[0], ray->direction[1], ray->direction[2];
    direction.normalize();
    eye << ray->origin[0], ray->origin[1], ray->origin[2];
    p << vertices[faces[i].vertices[0]].coord[0], vertices[faces[i].vertices[0]].coord[1], vertices[faces[i].vertices[0]].coord[2];
    AB << vertices[faces[i].vertices[1]].coord[0]-p[0], vertices[faces[i].vertices[1]].coord[1]-p[1], vertices[faces[i].vertices[1]].coord[2]-p[2];
    AC << vertices[faces[i].vertices[2]].coord[0]-p[0], vertices[faces[i].vertices[2]].coord[1]-p[1], vertices[faces[i].vertices[2]].coord[2]-p[2];

    pvec << direction.cross(AC);
    double det = AB.dot(pvec);

    if(det < DBL_MIN && det > -DBL_MIN ) continue;

    double invDet = 1.0/det;

    tvec = eye - p;

    double beta = tvec.dot(pvec) * invDet;
    if(beta < 0 || beta > 1) continue;
    
    qvec << tvec.cross(AB);
    double gamma = direction.dot(qvec) * invDet;
    double alpha = 1 - (beta + gamma);

    if(gamma < 0 || alpha < 0) continue;

  
    t = AC.dot(qvec) * invDet;
    if(t > ray->tNear) return false;
    if(t < hit.t) {
      hit.t = t;
      hit.material = material;
      hit.normal << AB.cross(AC).normalized(), 0;
      hit.normal = getWorld() * hit.normal;
    }
  }
  if(hit.t == DBL_MAX) {
    return false;
  }

  return true; 
}

void Mesh::print(std::ostream &os){
  os << "Mesh: (Label: " << name << ", Parent: " << parent << ")";
}
// Ray generation function
Ray *generateRay(Camera &camera, int &iWidth, int &iHeight, int &i, int &j) {
  Vector4d eye(0,0,0,1);
  Vector4d pc(0,0,1,1);

  // Image plane axes (constant, will be changed by camera to world matrix)
  Vector4d ihat(1,0,0,0);
  Vector4d jhat(0,1,0,0);
  
  Vector4d pij = pc + (((((i + 0.5)/iWidth)-0.5))*ihat) + ((((j+0.5)/iHeight)-0.5)*jhat);
  Vector4d dir = pij - eye;

  Ray *ray = new Ray(eye, dir);
  ray->origin = camera.mat.inverse() * ray->origin;
  ray->direction = camera.mat.inverse() * ray->direction;
  return ray;
}
