#include "point3d.h"

#ifndef ___SHAPES
#define ___SHAPES

class ray {
	// Ray with starting point "src", direction "dir" (dir is a unit vector)
public:
	point3d src, dir;
	ray() : src(point3d()), dir(point3d()) {};
	ray(point3d src_, point3d dir_) : src(src_), dir(dir_) {};
};

class sphere {
	// Sphere with center and radius
public:
	point3d center; double radius;
	sphere() : center(), radius(0.0) {};
	sphere(const point3d& center_, double radius_) : center(center_), radius(radius_) {};
};

class sphere_object {
public:
	sphere s; int material; double refraction; point3d albedo, flux;
	sphere_object() : s(), material(-1), refraction(), albedo(), flux() {};
	sphere_object(sphere s_, int material_, double refraction_, const point3d& albedo_) : s(s_), material(material_), refraction(refraction_), albedo(albedo_), flux() {};
	sphere_object(sphere s_, int material_, const point3d& flux_) : s(s_), material(material_), flux(flux_) { /* assert(material_ == MATERIAL_LIGHT); */ };
};

#endif