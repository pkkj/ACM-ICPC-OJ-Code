// CII 4676
// 2009 Amritapuri: Geometry Problem
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define EPS 1e-11
#define INF 1e50
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
 
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	POINT operator /(const double & v) {
		return POINT(x / v, y / v);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
	void unit() {
		double k = sqrt(x * x + y * y);
		x /= k, y /= k;
	}
};
inline double sqr(double x) {
	return x * x;
}
double dis(const POINT &p1, const POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
inline double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
inline double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
 
POINT t1[4], t2[4];
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return -1;
}
double gettime(POINT ts[4], POINT tm[4]) {
	int i, j;
	double ans = INF;
	POINT v = tm[3] - ts[3], uv;
	uv = v;
	uv.unit();
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			POINT p1, p2, p3, p4, it;
			p1 = tm[i], p2 = tm[i] + v, p3 = ts[j], p4 = ts[(j + 1) % 3];
			if (!line_inter(p1, p2, p3, p4, it)) continue;
			double minx = min(p3.x, p4.x), maxx = max(p3.x, p4.x);
			double miny = min(p3.y, p4.y), maxy = max(p3.y, p4.y);
			if (it.x < minx || it.x > maxx || it.y < miny || it.y > maxy) continue;
			if (sgn(dot(p1, p2, it)) < 0) continue;
			ans = min(ans, dis(p1, it) / v.abs());
		}
	}
	return ans;
}
void solve() {
	int i;
	double ans = INF;
	for (i = 0; i < 4; i++)
		t1[i].get();
	for (i = 0; i < 4; i++)
		t2[i].get();
	ans = min(ans, gettime(t1, t2));
	ans = min(ans, gettime(t2, t1));
	if (ans == INF) printf("NO COLLISION\n");
	else printf("%.9lf\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
