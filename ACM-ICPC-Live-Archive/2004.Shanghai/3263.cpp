// 2004 Shanghai: That Nice Euler Circuit
// POJ 2284
// ACM-ICPC Live Archive 3263
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define EPS  1e-8
#define N 305
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
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
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator /(const double & v) {
		return POINT(x / v, y / v);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
	bool operator<(const POINT &p) const {
		if (sgn(x - p.x))
			return x < p.x;
		return y < p.y;
	}
	bool operator ==(const POINT &p) {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	bool operator !=(const POINT &p) {
		return sgn(x - p.x) != 0 || sgn(y - p.y) != 0;
	}
};
struct LINE {
	POINT a, b;
	LINE() {
	}
	LINE(POINT a, POINT b) :
			a(a), b(b) {
	}
};

inline double cross(POINT &a, POINT &b, POINT &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
double crossdet(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

int cross2(const POINT &a, const POINT &c, const POINT &d) {
	return sgn(crossdet(a.x - c.x, a.y - c.y, d.x - c.x, d.y - c.y));
}

// a->b.a->c
inline double dot(POINT &a, POINT &b, POINT &c) {
	return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}
double dotdet(double x1, double y1, double x2, double y2) {
	return x1 * x2 + y1 * y2;
}
int between(POINT &a, POINT &b, POINT &c) {
	return sgn(dotdet(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y)) != 1;
}
int seg_intersect(POINT &a, POINT &b, POINT &c, POINT &d) {
	if (a == c || a == d || b == c || b == d)
		return 0;
	int a_cd = cross2(a, c, d);
	if (a_cd == 0 && between(a, c, d))
		return 2;
	int b_cd = cross2(b, c, d);
	if (b_cd == 0 && between(b, c, d))
		return 2;
	int c_ab = cross2(c, a, b);
	if (c_ab == 0 && between(c, a, b))
		return 2;
	int d_ab = cross2(d, a, b);
	if (d_ab == 0 && between(d, a, b))
		return 2;
	if ((a_cd ^ b_cd) == -2 && (c_ab ^ d_ab) == -2)
		return 1;
	return 0;
}
bool point_in_segment(POINT &a, POINT &b, POINT &c) {
	return sgn(cross(a, b, c)) == 0 && sgn(dot(a, b, c)) <= 0;
}
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {

	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return -1;
}
int n;
POINT pl[N], its[N * N];
LINE ll[N];
/*
 * Euler characteristic:
 * V+F-E=2
 */
void solve() {
	int i, j, ni, V, F, E;
	POINT cp;
	for (i = 0; i < n; i++)
		pl[i].get();
	n--;
	for (i = 0; i < n; i++) {
		ll[i] = LINE(pl[i], pl[i + 1]);
	}
	ni = 0;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			if (seg_intersect(ll[i].a, ll[i].b, ll[j].a, ll[j].b)) {
				line_inter(ll[i].a, ll[i].b, ll[j].a, ll[j].b, cp);
				its[ni++] = cp;
			}
		}
	for (i = 0; i < n; i++)
		its[ni++] = pl[i];
	sort(its, its + ni);
	for (i = j = 0; i < ni; i++) {
		if (i == 0 || i != 0 && its[i] != its[i - 1])
			its[j++] = its[i];
	}
	ni = j;
	V = ni, E = n;
	for (i = 0; i < n; i++)
		for (j = 0; j < ni; j++) {
			if (point_in_segment(its[j], ll[i].a, ll[i].b) && ll[i].a != its[j] && ll[i].b != its[j])
				E++;
		}
	F = 2 + E - V;
	printf("There are %d pieces.\n", F);
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", T++);
		solve();
	}
	return 0;
}
