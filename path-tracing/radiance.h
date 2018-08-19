#include "random.h"
#include "scene.h"

const double russian_roulette = 0.70;

double sqr(double x) {
	return x * x;
}

double collision(const ray& r, const sphere& s) {
	// Find the minimum t (t > +EPS) that s collides r
	point3d p = r.src - s.center;
	double eq2 = r.dir.norm();
	double eq1 = r.dir.dot(p);
	double eq0 = p.norm() - sqr(s.radius);
	double d = eq1 * eq1 - eq0 * eq2;
	if (d < EPS) return INF;
	d = std::sqrt(d);
	double v1 = (-eq1 - d) / eq2;
	double v2 = (-eq1 + d) / eq2;
	if (v1 > EPS) return v1;
	if (v2 > EPS) return v2;
	return INF;
}
point3d random_vector(point3d normal, random* rnd) {
	point3d bx = normal.cross(point3d(1, 0, 0));
	if (bx.norm() < EPS) bx = normal.cross(point3d(0, 1, 0));
	bx.normalize();
	point3d by = normal.cross(bx);
	double theta = std::acos(std::sqrt(rnd->next())), phi = 2 * PI * rnd->next();
	point3d ans = bx * sin(theta) * cos(phi) + by * sin(theta) * sin(phi) + normal * cos(theta);
	return ans;
}
point3d radiance(const ray& r, random* rnd, double refraction, int depth) {
	double russian = (depth >= 6 ? russian_roulette : 1.0);
	if (rnd->next() > russian) return point3d();
	// Find the "first" cross point from ray (minimum t that (r.src + t * r.dir) collides some object)
	double mint = INF;
	int id = -1;
	for (int i = 0; i < objects.size(); ++i) {
		double res = collision(r, objects[i].s);
		if (res < mint) {
			mint = res;
			id = i;
		}
	}
	if (id == -1) return point3d();
	point3d p = r.src + r.dir * mint;
	sphere_object obj = objects[id];
	point3d normal = (p - obj.s.center).normalize();
	double pcos = -normal.dot(r.dir);
	point3d radi;
	if (obj.material == MATERIAL_LIGHT) return obj.flux;
	if (obj.material == MATERIAL_LAMBERT) {
		// Calculate the radiance came from the direct light
		for (sphere_object s : objects) {
			if (s.material != MATERIAL_LIGHT) continue;
			point3d snormal = (p - s.s.center).normalize();
			point3d q = s.s.center + random_vector(snormal, rnd) * s.s.radius;
			bool collide = false;
			point3d pqvec = q - p;
			double dist = pqvec.abs();
			pqvec.normalize();
			for (sphere_object s : objects) {
				if (s.material == MATERIAL_LIGHT) continue;
				double res = collision(ray(p, pqvec), s.s);
				if (res < dist * (1 - EPS)) {
					collide = true;
					break;
				}
			}
			if (!collide) {
				double pqcos = normal.dot(pqvec);
				double qcos = -snormal.dot(pqvec);
				radi += s.flux * pqcos * qcos / sqr(dist) / PI;
			}
		}
		point3d reflect = random_vector(normal, rnd);
		radi += radiance(ray(p, reflect), rnd, refraction, depth + 1);
	}
	if (obj.material == MATERIAL_SPECULAR) {
		double refraction_new = 0.0; int cnt = 0;
		for (sphere_object s : objects) {
			if ((s.s.center - p - r.dir * EPS).norm() < sqr(s.s.radius)) {
				refraction_new += s.refraction;
				++cnt;
			}
		}
		if (cnt != 0) refraction_new /= cnt;
		else refraction_new = REFRACTION_AIR;
		double ratio = refraction / refraction_new;
		double weight = 1.0;
		bool reflect_flag = (obj.refraction == 0.0);
		if (!reflect_flag) {
			double rcos = 1.0 - sqr(ratio) * (1 - sqr(pcos));
			if (rcos < 0.0) reflect_flag = true;
			else {
				double R0 = sqr((refraction - refraction_new) / (refraction + refraction_new));
				double albedo = R0 + (1 - R0) * pow(1.0 - std::abs(pcos), 5.0);
				if (rnd->next() < albedo) {
					weight = 1.0 / albedo;
					reflect_flag = true;
				}
				else {
					rcos = std::sqrt(rcos);
					weight = 1.0 / (1.0 - albedo);
					point3d refract = r.dir * ratio + normal * (ratio * std::abs(pcos) - rcos) * (pcos > 0.0 ? 1.0 : -1.0);
					refract.normalize();
					radi += radiance(ray(p, refract), rnd, refraction_new, depth + 1);
				}
			}
		}
		if(reflect_flag){
			point3d reflect = r.dir + normal * 2.0 * pcos;
			radi += radiance(ray(p, reflect), rnd, refraction, depth + 1);
		}
		radi *= weight;
	}
	return radi.multiply(obj.albedo) / russian;
}