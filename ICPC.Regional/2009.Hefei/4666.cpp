// CII 4666
// 2009 Hefei: Airport
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 1005
#define INF 1e30
#define EPS 1e-12
double sqr(double x) {
	return x * x;
}
struct POINT {
	double x, y, z;
	POINT() {
	}
	POINT(double x, double y, double z) :
		x(x), y(y), z(z) {
	}
	void get() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	POINT operator-(POINT &p) {
		return POINT(x - p.x, y - p.y, z - p.z);
	}
	POINT operator*(double k) {
		return POINT(k * x, k * y, k * z);
	}
	void tounit() {
		double d = sqrt(x * x + y * y + z * z);
		x /= d, y /= d, z /= d;
	}
	void print() {
		printf("%.3lf %.3lf %.3lf\n", x, y, z);
	}
};
int iszero(double x) {
	return x > -EPS && x < EPS;
}
 
POINT start[N], end[N], ve[N];
double radius[N], ti[N], speed[N];
int n;
 
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
}
void getv(int i) {
	ve[i] = end[i] - start[i];
	ve[i].tounit();
	ve[i] = ve[i] * speed[i];
}
int solveEQ(double A, double B, double C, double &x1, double &x2) {
	if (iszero(A)) {
		if (iszero(B)) return 0;
		x1 = x2 = -C / B;
		return 1;
	}
	double delta = B * B - 4 * A * C;
	if (delta < -EPS) return 0;
	delta = sqrt(fabs(delta));
	x1 = (-B + delta) / (2 * A), x2 = (-B - delta) / (2 * A);
	return 1;
}
 
void getpara(double x1, double x2, double v1, double v2, double t1, double t2, double &k2, double &k1, double &k0) {
	double A = v1 - v2;
	double B = x1 - x2 - v1 * t1 + v2 * t2;
	k2 = A * A, k1 = 2 * A * B, k0 = B * B;
}
 
int judge(POINT st1, POINT st2, POINT v1, POINT v2, int i, int j, double &x1, double &x2) {
	double d2, d1, d0, A = 0, B = 0, C = -sqr(radius[i] + radius[j]);
	getpara(st1.x, st2.x, v1.x, v2.x, ti[i], ti[j], d2, d1, d0);
	A += d2, B += d1, C += d0;
	getpara(st1.y, st2.y, v1.y, v2.y, ti[i], ti[j], d2, d1, d0);
	A += d2, B += d1, C += d0;
	getpara(st1.z, st2.z, v1.z, v2.z, ti[i], ti[j], d2, d1, d0);
	A += d2, B += d1, C += d0;
	if (!solveEQ(A, B, C, x1, x2)) return 0;
	return 1;
}
void solve() {
	int i, j;
	double ans = INF;
 
	for (i = 0; i < n; i++) {
		start[i].get();
		end[i].get();
		scanf("%lf%lf%lf", &radius[i], &ti[i], &speed[i]);
		getv(i);
	}
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			double t1s, t1e, t2s, t2e, x1, x2;
			POINT nospeed = POINT(0, 0, 0);
			t1s = ti[i], t2s = ti[j];
			t1e = dis(start[i], end[i]) / speed[i] + ti[i];
			t2e = dis(start[j], end[j]) / speed[j] + ti[j];
			// Hit when moving
			if (judge(start[i], start[j], ve[i], ve[j], i, j, x1, x2)) {
				if (x1 < t1s || x1 < t2s || x1 > t1e || x1 > t2e) x1 = INF;
				if (x2 < t1s || x2 < t2s || x2 > t1e || x2 > t2e) x2 = INF;
				ans = min(ans, x1);
				ans = min(ans, x2);
			}
			// Hit when A not Move, B Move
			if (judge(start[i], start[j], nospeed, ve[j], i, j, x1, x2)) {
				if (x1 > t1s || x1 < t2s || x1 > t2e) x1 = INF;
				if (x2 > t1s || x2 < t2s || x2 > t2e) x2 = INF;
				ans = min(ans, x1);
				ans = min(ans, x2);
			}
			if (judge(end[i], start[j], nospeed, ve[j], i, j, x1, x2)) {
				if (x1 < t1e || x1 < t2s || x1 > t2e) x1 = INF;
				if (x2 < t1e || x2 < t2s || x2 > t2e) x2 = INF;
				ans = min(ans, x1);
				ans = min(ans, x2);
			}
			// Hit when A Move, B not Move
			if (judge(start[i], start[j], ve[i], nospeed, i, j, x1, x2)) {
				if (x1 > t2s || x1 < t1s || x1 > t1e) x1 = INF;
				if (x2 > t2s || x2 < t1s || x2 > t1e) x2 = INF;
				ans = min(ans, x1);
				ans = min(ans, x2);
			}
			if (judge(start[i], end[j], ve[i], nospeed, i, j, x1, x2)) {
				if (x1 < t2e || x1 < t1s || x1 > t1e) x1 = INF;
				if (x2 < t2e || x2 < t1s || x2 > t1e) x2 = INF;
				ans = min(ans, x1);
				ans = min(ans, x2);
			}
	}
 
	if (ans == INF) printf("Never\n");
	else printf("%.2lf\n", ans);
 
}
int main() {
	while (scanf("%d", &n) && n != -1)
		solve();
}
