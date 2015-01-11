// POJ 3029
// Nordic 2006: Tour Guide
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 10
 
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
};
POINT pl[N], vl[N];
 
double gettime(POINT &p0, POINT &v0, POINT &p1, double v) {
	double X = p0.x - p1.x;
	double Y = p0.y - p1.y;
	double A = v0.x * v0.x + v0.y * v0.y - v * v;
	double B = 2 * Y * v0.y + 2 * X * v0.x;
	double C = X * X + Y * Y;
	double delta = sqrt(B * B - 4 * A * C);
	double x1 = (-B - delta) / (2 * A);
	double x2 = (-B + delta) / (2 * A);
	if (x1 >= 0) return x1;
	return x2;
}
int main() {
	int n, i, j;
	while (scanf("%d", &n) && n) {
		int idx[N];
		double v, a, vv;
		scanf("%lf", &v);
		for (i = 0; i < n; i++) {
			idx[i] = i;
			pl[i].get();
			scanf("%lf%lf", &vv, &a);
			vl[i].x = cos(a) * vv, vl[i].y = sin(a) * vv;
		}
		double ans = 1e50;
		do {
			POINT cur = POINT(0, 0);
			POINT p[N];
			double t = 0, tans = 0;
			memcpy(p, pl, sizeof(pl));
			for (i = 0; i < n; i++) {
				double dt = gettime(p[idx[i]], vl[idx[i]], cur, v);
				for (j = 0; j < n; j++) {
					double nx = p[j].x + vl[j].x * dt;
					double ny = p[j].y + vl[j].y * dt;
					p[j] = POINT(nx, ny);
				}
				tans = max(tans, dt + sqrt((p[idx[i]].x * p[idx[i]].x + p[idx[i]].y * p[idx[i]].y) / (vl[idx[i]].x * vl[idx[i]].x
						+ vl[idx[i]].y * vl[idx[i]].y)) + t);
				t += dt;
				cur = p[idx[i]];
			}
			ans = min(tans, ans);
		} while (next_permutation(idx, idx + n));
		printf("%.0lf\n", ans);
	}
	return 0;
}
