#include <iostream>
#include <Eigen/Dense>
#include "Ray.h"
#include "Primitive.h"

using std::cout, std::endl;

int main(int argc, char *argv[]) {
	Vector4d origin(1,2,3,1);
	Vector4d direction(0,0,-1,0);

	Primitive prime;
	Camera cam;
	Sphere sphere;
	Plane plane;

	Ray ray(origin, direction);

	cout << ray << endl;
	cout << prime << endl;
	cout << cam << endl;
	cout << sphere << endl;
	cout << plane << endl;
	return 0;
}
