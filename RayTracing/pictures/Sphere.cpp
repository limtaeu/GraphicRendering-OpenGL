//============================================================
// STUDENT NAME: Lim Ta Eu
// MATRIC NO.  : A0126356E
// NUS EMAIL   : a0126356@u.nus.edu
// COMMENTS TO GRADER:
// <comments to grader, if any>
//
// ============================================================
//
// FILE: Sphere.cpp



#include <cmath>
#include "Sphere.h"
#include <algorithm>

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
	Vector3d newOrigin = r.origin() - center;
	
	double RdRd = dot(r.direction(), r.direction());
	double RdRo = dot(r.direction(), newOrigin);
	double RoRo = dot(newOrigin, newOrigin);

	double t, a, b, c, x1, x2, determinant;
	a = RdRd;
	b = 2*RdRo;
	c = RoRo - radius*radius;
	
	determinant = b*b - 4 * a * c;

	if (determinant == 0) {
		x1 = (-b + sqrt(determinant)) / (2 * a);
		t = x1;
	}
	else if (determinant > 0) {
		x1 = (-b + sqrt(determinant)) / (2 * a);
		x2 = (-b - sqrt(determinant)) / (2 * a);

		if (x1 < tmin) {
			t = x2;
		}
		else if (x2 < tmin) {
			t = x1;
		}
		else {
			t = min(x1, x2);
		}
	}
	else {
		return false;
	}

	if (t<tmin || t>tmax) return false;

	

	rec.t = t;
	rec.p = r.pointAtParam(t);

	Vector3d v = r.pointAtParam(t) - center;
	Vector3d N = v.unitVector();

	rec.normal = N;
	rec.mat_ptr = matp;

	return true; // You can remove/change this if needed.
}




bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
	Vector3d newOrigin = r.origin() - center;

	double RdRd = dot(r.direction(), r.direction());
	double RdRo = dot(r.direction(), newOrigin);
	double RoRo = dot(newOrigin, newOrigin);

	double t, a, b, c, x1, x2, determinant;
	a = RdRd;
	b = 2 * RdRo;
	c = RoRo - radius*radius;

	determinant = b*b - 4 * a * c;

	if (determinant == 0) {
		x1 = (-b + sqrt(determinant)) / (2 * a);
		t = x1;
	}
	else if (determinant > 0) {
		x1 = (-b + sqrt(determinant)) / (2 * a);
		x2 = (-b - sqrt(determinant)) / (2 * a);

		if (x1 < tmin) {
			t = x2;
		}
		else if (x2 < tmin) {
			t = x1;
		}
		else {
			t = min(x1, x2);
		}
	}
	else {
		return false;
	}

	return (t>=tmin && t<=tmax);

}

