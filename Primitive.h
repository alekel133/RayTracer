#pragma once
#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <Eigen/Dense>
#include <ostream>
#include "Ray.h"

typedef struct{
	int t;
} hit;

typedef struct{
	Vector4d coord;	
	double *color;
}Vertex;

class Primitive {
	public:
		// Data for recursive transform application
		char * name;
		Primitive *parent;
		Primitive **children;
		Matrix4d mat;
		double *color;

		// Virtual class functions
		Primitive();
		~Primitive();
		// Virtual Functions for Ray Tracing and Ray Acceleration
		bool isHit(Ray &ray, hit &hit);
	   Matrix4d getLocal();
	   Matrix4d getWorld();
		friend std::ostream &operator << (std::ostream &os, Primitive &prim);
};

class Camera: public Primitive {
	public:
		// Data for Camera Directions and Ray Generation
		Vector4d eye;
		Vector4d direction;
		Vector4d up;
		Vector4d side;

		// Camera, like all Prmitives, is initialized at the origin, and moved by a series of transformations
		Camera(void);
		
		// Function for outputing the data stored in the Camera object.
	   friend std::ostream &operator << (std::ostream &os, Camera &cam);
};

class Sphere: public Primitive {
	public:
		float radius;
		Vector4d origin;
		
		Sphere();
		Sphere(double *color);
		bool isHit(Ray &ray, hit &hit);
		friend std::ostream &operator<<(std::ostream &os, Sphere &sphere);
};

class Plane: public Primitive {
	public:
		Vector4d origin;
		Vector4d normal;
		
		Plane();
		bool isHit(Ray &ray, hit &hit);
		friend std::ostream &operator<<(std::ostream &os, Plane &plane);
};

class Triangle:public Primitive {
	Vertex *points[3];

	bool isHit(Ray &ray, hit &hit);
	friend std::ostream &operator<<(std::ostream &os, Triangle &tri);
};

class Mesh: public Primitive {
	Vertex *vertices;
	Triangle *triangles;

	bool isHit(Ray &ray, hit &hit);
	friend std::ostream &operator<<(std::ostream &os, Mesh &mesh);
};

class AABB: public Primitive {
	Vector4d maxPoint;
	Vector4d minPoint;
	float clip;

	bool isHit(Ray &ray, hit &hit);
	friend std::ostream &operator<<(std::ostream &os, Mesh &mesh);
	
};

class BVH: public Primitive {
	AABB *root;
	AABB **children;
	float clip;

	bool isHit(Ray &ray, hit &hit);
	friend std::ostream &operator<<(std::ostream &os, Mesh &mesh);
};
#endif
