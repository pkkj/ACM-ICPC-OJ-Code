// CII 4448
// 2009 World Final: Conduit Packing
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 10
#define EPS 1e-8
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct POINT {
	double x, y, r;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT(double x, double y, double r) :
		x(x), y(y), r(r) {
	}
	bool operator ==(const POINT &p) {
		return sgn(p.x - x) == 0 && sgn(p.y - y) == 0;
	}
	bool operator <(const POINT &p) const {
		if (sgn(x - p.x)) return x < p.x;
		return y < p.y;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void unit() {
		double k = abs();
		x /= k, y /= k;
	}
	POINT operator +(const POINT &p) {
		return POINT(x + p.x, y + p.y);
	}
	POINT operator *(double k) {
		return POINT(x * k, y * k);
	}
	void print() {
		printf("[%.3lf %.3lf] ", x, y);
	}
};
double sqr(double x) {
	return x * x;
}
double dis2(POINT &a, POINT &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
POINT rotate(const POINT &p, double a) {
	POINT ret;
	ret.x = p.x * cos(a) - p.y * sin(a);
	ret.y = p.x * sin(a) + p.y * cos(a);
	return ret;
}
bool intersect(POINT &a, POINT &b, POINT &p1, POINT &p2) {
	double d = dis2(a, b), ang;
	if (d > sqr(a.r + b.r)) return false;
	if (d < sqr(a.r - b.r)) return false;
	d = sqrt(d);
	ang = (sqr(a.r) + sqr(d) - sqr(b.r)) / 2 / d / a.r;
	ang = acos(ang);
	POINT v = POINT(b.x - a.x, b.y - a.y);
	v.unit();
	v = v * a.r;
	p1 = rotate(v, ang), p2 = rotate(v, -ang);
	p1 = a + p1, p2 = a + p2;
	return true;
}
 
double d[N], R;
bool vis[N];
POINT pc[N];
bool exam(int dep) {
	int i, j;
	POINT zero = POINT(0, 0);
	for (i = 0; i < dep; i++)
		for (j = i + 1; j < dep; j++)
			if (dis(pc[i], pc[j]) + EPS < pc[i].r + pc[j].r) return 0;
 
	for (i = 0; i < dep; i++)
		if (dis(pc[i], zero) - EPS > R - pc[i].r) return 0;
 
	return 1;
}
int dfs(int dep) {
	int i, j, k;
	POINT a, b, p1, p2;
	if (dep == 4) return 1;
	for (i = 0; i < 3; i++) {
		if (vis[i]) continue;
		vis[i] = 1;
		// Do with the outer circle
		for (j = 0; j < dep; j++) {
			a = POINT(0, 0, R - d[i]);
			b = POINT(pc[j].x, pc[j].y, pc[j].r + d[i]);
			intersect(a, b, p1, p2);
			p1.r = p2.r = d[i];
			pc[dep] = p1;
			if (exam(dep + 1)) if (dfs(dep + 1)) return 1;
			pc[dep] = p2;
			if (exam(dep + 1)) if (dfs(dep + 1)) return 1;
		}
		// Do with the existed inner circle
		for (j = 0; j < dep; j++) {
			for (k = j + 1; k < dep; k++) {
				a = pc[j], b = pc[k];
				a.r += d[i], b.r += d[i];
				intersect(a, b, p1, p2);
				p1.r = p2.r = d[i];
				pc[dep] = p1;
				if (exam(dep + 1)) if (dfs(dep + 1)) return 1;
				pc[dep] = p2;
				if (exam(dep + 1)) if (dfs(dep + 1)) return 1;
			}
		}
		vis[i] = 0;
	}
	return 0;
}
bool check(double R) {
	::R = R;
	memset(vis, 0, sizeof(vis));
	pc[0] = POINT(0, -(R - d[3]), d[3]);
	return dfs(1);
}
void solve() {
	double l, r, mid = 0;
	scanf("%lf%lf%lf", &d[1], &d[2], &d[3]);
	for (int i = 0; i < 4; i++)
		d[i] /= 2.0;
	sort(d, d + 4);
	l = d[3] + d[2], r = min(d[0] + d[1] + d[2] + d[3], 50000.0);
	while (l + 1e-1 < r) {
		mid = (l + r) / 2.0;
		if (check(mid)) r = mid;
		else l = mid;
	}
	mid *= 2;
	printf("%d\n", (int) (mid + 0.5));
}
int main() {
	int ca = 1;
	while (scanf("%lf", &d[0]) && d[0]) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
