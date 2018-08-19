#include "radiance.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>
#pragma warning(disable : 4996)
using namespace std;

int main() {
	point3d camera_center(0.0, -1.5, 0.0);
	ofstream fos("render.ppm");
	int N = 500, M = 50;
	fos << "P3" << endl;
	fos << N << ' ' << N << endl;
	fos << 255 << endl;
	for (int i = N - 1; i >= 0; --i) {
		for (int j = 0; j < N; ++j) {
			random rnd(i * 257 + j * 311);
			point3d sum;
			for (int k = 0; k < M; ++k) {
				double sx = 2.0 * (j + rnd.next()) / N - 1.0;
				double sz = 2.0 * (i + rnd.next()) / N - 1.0;
				point3d dir = point3d(sx, -0.6, sz) - camera_center;
				dir.normalize();
				point3d res = radiance(ray(camera_center, dir), &rnd, REFRACTION_AIR, 0);
				sum += res;
			}
			sum /= M;
			sum = point3d(min(sum.x, 1.0), min(sum.y, 1.0), min(sum.z, 1.0));
			sum = point3d(pow(sum.x, 1.0 / 2.2), pow(sum.y, 1.0 / 2.2), pow(sum.z, 1.0 / 2.2));
			sum = sum * 255 + point3d(0.5, 0.5, 0.5);
			fos << (int)sum.x << ' ' << (int)sum.y << ' ' << (int)sum.z << ' ';
			//cout << setw(5) << color;
		}
		fos << endl;
		//cout << endl;
	}
	fos.close();
	return 0;
}