// CII 4428
// 2008 Tehran: Solar Eclipse
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define EPS 1e-8
#define PI 3.14159265358979323846
#define N 105
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	void print() {
		printf("%.3lf %.3lf\n", x, y);
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	double abs2() {
		return x * x + y * y;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void tounit() {
		x /= abs(), y /= abs();
	}
	POINT operator -(const POINT &p) {
		return POINT(x - p.x, y - p.y);
	}
	bool operator ==(const POINT &p) {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
};
POINT rotate(const POINT &p, double a) {
	POINT ret;
	ret.x = p.x * cos(a) - p.y * sin(a);
	ret.y = p.x * sin(a) + p.y * cos(a);
	return ret;
}
struct RANGE {
	double b, e;
	void print() {
		printf("[%.3lf  %.3lf]\n", b, e);
	}
	bool operator <(const RANGE r) const {
		if (sgn(b - r.b)) return b < r.b;
		return e < r.e;
 
	}
};
int n;
double R, R2;
POINT pl[N];
 
double sqr(double x) {
	return x * x;
}
double dis(POINT a, POINT b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double dis2(POINT a, POINT b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}
RANGE twocir(POINT &a, POINT &b) {
	RANGE ans;
	POINT c1, c2, mid;
	double d = dis(a, b) / 2, ang;
	ang = acos(d / R);
	mid = b - a;
	c1 = rotate(mid, -ang);
	c2 = rotate(mid, ang);
	ans.b = atan2(c1.y, c1.x);
	ans.e = atan2(c2.y, c2.x);
	if (ans.b < 0) ans.b += 2 * PI;
	if (ans.e < 0) ans.e += 2 * PI;
	return ans;
}
double bestd(POINT o, double a, double b) {
	double ang, d1, d2;
	POINT p1, p2;
	ang = atan2(-o.y, -o.x);
	if (ang < 0) ang += 2 * PI;
	if (a <= ang && ang <= b) {
		p1 = POINT(R * cos(ang), R * sin(ang));
		p1.x += o.x, p1.y += o.y;
		return dis(p1, POINT(0, 0));
	}
	p1 = POINT(R * cos(a), R * sin(a));
	p2 = POINT(R * cos(b), R * sin(b));
	p1.x += o.x, p1.y += o.y;
	p2.x += o.x, p2.y += o.y;
	d1 = dis(p1, POINT(0, 0));
	d2 = dis(p2, POINT(0, 0));
	return d1 < d2 ? d1 : d2;
}
RANGE rl[N];
double solve() {
	int i, j, tot, ok =1;
	double best = 1e30;
	bool zc;
	for (i = 0; i < n; i++)
		pl[i].get();
	R *= 2;
	R2 = R * R;
	for (i = 0; i < n && ok; i++)
		if (pl[i].abs2() < R2) ok=0;
	if(ok)return 0;
	for (i = 0; i < n; i++) {
		tot = 0;
		zc = 0;
		for (j = 0; j < n; j++) {
			if (i == j || pl[i] == pl[j]) continue;
			if (dis(pl[i], pl[j]) + EPS >= R + R) continue;
			rl[tot] = twocir(pl[i], pl[j]);
			if (rl[tot].e < rl[tot].b) {
				rl[tot + 1].b = 0, rl[tot + 1].e = rl[tot].e;
				rl[tot].e = 2 * PI;
				tot += 2;
				zc = 1;
			} else tot++;
		}

		if (tot) {
			sort(rl, rl + tot);
			if (!zc) best = min(best, bestd(pl[i], 0, rl[0].b));
			double pree = rl[0].e;
			for (j = 1; j < tot; j++) {
				if (rl[j].b > pree) best = min(best, bestd(pl[i], pree, rl[j].b));
				if (rl[j].e > pree) pree = rl[j].e;
			}
 
			if (!zc) min(best, bestd(pl[i], pree, 2 * PI));
		} else best = min(best, bestd(pl[i], 0, 2 * PI));
	}
	return best;
}
int main() {
	while (scanf("%d%lf", &n, &R) && n)
		printf("%.6lf\n", solve());
}
