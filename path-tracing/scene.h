#include <vector>

#include "constants.h"
#include "shapes.h"

/* ASSERTION: DIFFERENT MATERIAL OBJECTS SHOULD NOT BE COLLIDED */

std::vector<sphere_object> objects = {
	sphere_object(sphere(point3d(0.0, 0.0, +0.9), 0.1), MATERIAL_LIGHT, point3d(1.3, 1.3, 1.3)),
	sphere_object(sphere(point3d(-100001.00, 0.0, 0.0), 100000.0), MATERIAL_LAMBERT, 0.0, point3d(0.75, 0.25, 0.25)),
	sphere_object(sphere(point3d(+100001.00, 0.0, 0.0), 100000.0), MATERIAL_LAMBERT, 0.0, point3d(0.25, 0.75, 0.25)),
	sphere_object(sphere(point3d(0.0, -100001.50, 0.0), 100000.0), MATERIAL_LAMBERT, 0.0, point3d(0.25, 0.25, 0.75)),
	sphere_object(sphere(point3d(0.0, +100001.50, 0.0), 100000.0), MATERIAL_LAMBERT, 0.0, point3d(0.75, 0.75, 0.75)),
	sphere_object(sphere(point3d(0.0, 0.0, -100001.00), 100000.0), MATERIAL_LAMBERT, 0.0, point3d(0.75, 0.75, 0.75)),
	sphere_object(sphere(point3d(0.0, 0.0, +100001.00), 100000.0), MATERIAL_LAMBERT, 0.0, point3d(0.75, 0.75, 0.75)),
	sphere_object(sphere(point3d(0.0, 0.0, -0.5), 0.5), MATERIAL_SPECULAR, REFRACTION_GLASS, point3d(0.99, 0.99, 0.99))
};