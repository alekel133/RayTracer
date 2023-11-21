#include "Light.h"
#include <iostream>

//------------------------- Point Light-------------------------//
PointLight::PointLight() {
  this->point = Vector4d(0,0,0,1);
  this->color = nullptr;
}

PointLight::PointLight(Vector4d &point, int *color) {
  this->point = point;
  this->color = color;
}

bool PointLight::isHit(Ray* ray, Hit &hit) {
  return false;
}

int *PointLight::illuminate(Ray* ray, Hit &hit, bool vis){
  ret[0] = 0;
  ret[1] = 0;
  ret[2] = 0;
  if(!vis) return ret;
  Vector4d l = point - getLocal() * ray->eval(hit.t);
  Vector4d v = (getLocal() * -ray->direction);
  Vector4d h = (l+v).normalized();
  double distance = l.norm();
  l.normalize();
  double invDist = 1/(distance * distance);
  double aofi = l.dot(hit.normal);

  for(int i = 0; i < 3; ++i) {
    ret[i] = int((pow(hit.normal.dot(h), hit.material.shine) * hit.material.specular[i])+(intensity * aofi * hit.material.diffuse[i] * invDist * 100));
    if(ret[i] > 255) ret[i] = 255;
    if(ret[i < 0]) ret[i] = 0;
  }

  return ret;
}

Vector4d PointLight::getDirection(Vector4d p) {
  Vector4d ret = point -  getLocal() *p;
  ret(3) = 0;
  ret.normalize();
  return getWorld() * ret;
}

Vector4d PointLight::getPoint() {
  return getWorld() * point;
};

void PointLight::print(std::ostream &os) {
    return;
}
//------------------------ Directional Light ------------------//
DirectionalLight::DirectionalLight() {
  this->direction = Vector4d(0,0,1,0);
  this->color = nullptr;
}

DirectionalLight::DirectionalLight(Vector4d &direction, int *color) {
  this->direction = direction;
  this->color = color;
}

bool DirectionalLight::isHit(Ray* ray , Hit &hit) {
  return false;
}

int *DirectionalLight::illuminate(Ray *ray, Hit &hit, bool vis) {
  ret[0] = 0;
  ret[1] = 0;
  ret[2] = 0;
  if(!vis) return ret;
  Vector4d dir = getLocal() * direction;
  dir.normalize();
  Vector4d v = (getLocal() * -ray->direction);
  Vector4d h = (dir+v).normalized();
  double aofi = dir.dot(hit.normal);

  for(int i = 0; i < 3; ++i) {
    ret[i] = int((pow(hit.normal.dot(h), hit.material.shine) * hit.material.specular[i])+(intensity * aofi * hit.material.diffuse[i]));
    if(ret[i] > 255) ret[i] = 255;
    if(ret[i] < 0) ret[i] = 0;
  }

  return ret;
}

Vector4d DirectionalLight::getDirection(Vector4d point){
  return (getWorld()*(direction)).normalized();
}


Vector4d DirectionalLight::getPoint() {
  return Vector4d(DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX);
}

void DirectionalLight::print(std::ostream &os) {
  return;
}
