#include "MathUtils.h"

Matrix4d rotateX(double theta){
  double angle = theta * M_PI/180;
  Matrix4d rotation;
  rotation << 1,0,0,0,
              0,cos(angle),-sin(angle),0,
              0,sin(angle),cos(angle),0,
              0,0,0,1;

  return rotation; 
}

Matrix4d rotateY(double theta){
  double angle = theta * M_PI/180;
  Matrix4d rotation;
  rotation << cos(angle),0,sin(angle),0,
              0,1,0,0,
              -sin(angle),0,cos(angle),0,
              0,0,0,1;
 
  return rotation;
}

Matrix4d rotateZ(double theta){
  double angle = theta * M_PI/180;
  Matrix4d rotation;
  rotation << cos(angle), -sin(angle),0,0,
              sin(angle),cos(angle),0,0,
              0,0,1,0,
              0,0,0,1;
 
  return rotation;
}

Matrix4d translateX(double units){
  Matrix4d translation;
  translation << 1,0,0,units,
                 0,1,0,0,
                 0,0,1,0,
                 0,0,0,1;
  
  return translation;
}

Matrix4d translateY(double units){
  Matrix4d translation;
  translation << 1,0,0,0,
                 0,1,0,units,
                 0,0,1,0,
                 0,0,0,1;
  
  return translation;
}

Matrix4d translateZ(double units){
  Matrix4d translation;
  translation << 1,0,0,0,
                 0,1,0,0,
                 0,0,1,units,
                 0,0,0,1;
 
  return translation;
}

Matrix4d scale(double factor){
  Matrix4d scale;
  scale << factor,0,0,0,
           0,factor,0,0,
           0,0,factor,0,
           0,0,0,1;

  return scale; 
}
