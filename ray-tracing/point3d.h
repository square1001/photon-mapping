#include <cmath>

#ifndef ___POINT3D
#define ___POINT3D

class point3d {
public:
	double x, y, z;
	point3d() : x(0.0), y(0.0), z(0.0) {};
	point3d(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};
	bool operator==(const point3d& p) const { return x == p.x && y == p.y && z == p.z; }
	bool operator!=(const point3d& p) const { return x != p.x || y != p.y || z != p.z; }
	point3d& operator+=(const point3d& p) { x += p.x; y += p.y; z += p.z; return *this; }
	point3d& operator-=(const point3d& p) { x -= p.x; y -= p.y; z -= p.z; return *this; }
	point3d& operator*=(const double v) { x *= v; y *= v; z *= v; return *this; }
	point3d& operator/=(const double v) { x /= v; y /= v; z /= v; return *this; }
	point3d operator-() const { return point3d(*this) *= -1.0; }
	point3d operator+(const point3d& p) const { return point3d(*this) += p; }
	point3d operator-(const point3d& p) const { return point3d(*this) -= p; }
	point3d operator*(const double v) const { return point3d(*this) *= v; }
	point3d operator/(const double v) const { return point3d(*this) /= v; }
	double norm() const { return x * x + y * y + z * z; }
	double abs() const { return std::sqrt(x * x + y * y + z * z); }
	double dot(const point3d& p) const { return x * p.x + y * p.y + z * p.z; }
	point3d cross(const point3d& p) const { return point3d(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
	point3d multiply(const point3d& p) const { return point3d(x * p.x, y * p.y, z * p.z); }
	point3d divide(const point3d& p) const { return point3d(x / p.x, y / p.y, z / p.z); }
	point3d sqr() const { return point3d(x * x, y * y, z * z); }
	point3d& normalize() { (*this) /= point3d(*this).abs(); return *this; }
};

#endif