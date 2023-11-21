#pragma once
#ifndef MATHUTILS_H
#define MATHUTILS_H
#include "eigen-3.4.0/Eigen/Dense"

using namespace Eigen;

//----------- Rotations ---------------//
// Returns a matrix corresponding to a rotation (in degrees) about the x axis
Matrix4d rotateX(double theta);
// Returns a matrix corresponding to a rotation (in degrees) about the y axis
Matrix4d rotateY(double theta);
// Returns a matrix corresponding to a rotation (in degrees) about the z axis
Matrix4d rotateZ(double theta);

//----------- Translations ---------------//
//Returns a matrix corresponding to a translation on the x axis by n units
Matrix4d translateX(double units);
//Returns a matrix corresponding to a translation on the x axis by n units
Matrix4d translateY(double units);
//Returns a matrix corresponding to a translation on the x axis by n units
Matrix4d translateZ(double units);

//----------- Scale ---------------//
//Returns a matrix corresponding to a scale by factor
Matrix4d scale(double factor);


#endif
