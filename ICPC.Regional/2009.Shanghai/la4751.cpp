// 2009 Shanghai: Island Explorer
// ACM-ICPC Live Archive 4751
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 10005
 
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("%.3lf %.3lf\n", x, y);
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
};
#define EPS 1e-8
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
inline double sqr(double x) {
	return x * x;
}
double dis(const POINT &p1, const POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
inline double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
 
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return -1;
}
double t1[N], t2[N];
int n, m, ce;
POINT A, B, C, D, p1[N], p2[N];
struct EDGE {
	int a, b;
	double d;
	EDGE() {
	}
	EDGE(int a, int b, double d) :
		a(a), b(b), d(d) {
	}
	bool operator <(const EDGE &e) const {
		return d < e.d;
	}
};
int fa[N * 2];
EDGE E[N * 10];
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
double getvec(POINT p, POINT a, POINT b) {
	POINT r = a - b, it;
	swap(r.x, r.y);
	r.x *= -1.0;
	r = r + p;
	line_inter(a, b, r, p, it);
	if (sgn(b.x - a.x)) return (b.x - it.x) / (b.x - a.x);
	return (b.y - it.y) / (b.y - a.y);
}
void build() {
	int i, j;
	double t;
	for (i = 0; i < n; i++) {
		t = getvec(p1[i], C, D);
		j = lower_bound(t2, t2 + m, t) - t2;
		if (j < m) E[ce++] = EDGE(i, j + n, dis(p1[i], p2[j]));
		if (j - 1 >= 0) E[ce++] = EDGE(i, j - 1 + n, dis(p1[i], p2[j - 1]));
	}
	for (i = 0; i < m; i++) {
		t = getvec(p2[i], A, B);
		j = lower_bound(t1, t1 + n, t) - t1;
		if (j < n) E[ce++] = EDGE(j, i + n, dis(p1[j], p2[i]));
		if (j - 1 >= 0) E[ce++] = EDGE(j - 1, i + n, dis(p1[j - 1], p2[i]));
	}
 
}
double kruskal() {
	int i, has = 1;
	double ans = 0;
	for (i = 0; i < n + m; i++)
		fa[i] = i;
	sort(E, E + ce);
	for (i = 0; i < ce && has < n + m; i++) {
		int a = find(E[i].a), b = find(E[i].b);
		if (fa[a] == fa[b]) continue;
		fa[a] = b;
		ans += E[i].d;
		has++;
	}
	return ans;
}
int main() {
	int T, ca = 1, i;
	scanf("%d", &T);
	while (T--) {
		printf("Case #%d: ", ca++);
		scanf("%d%d", &n, &m);
		ce = 0;
		A.get();
		B.get();
		C.get();
		D.get();
		for (i = 0; i < n; i++)
			scanf("%lf", &t1[i]);
 
		for (i = 0; i < m; i++)
			scanf("%lf", &t2[i]);
		sort(t1, t1 + n);
		sort(t2, t2 + m);
		for (i = 0; i < n; i++) {
			p1[i] = POINT(A.x * t1[i] + (1 - t1[i]) * B.x, A.y * t1[i] + (1 - t1[i]) * B.y);
			if (i) E[ce++] = EDGE(i - 1, i, dis(p1[i - 1], p1[i]));
		}
		for (i = 0; i < m; i++) {
			p2[i] = POINT(C.x * t2[i] + (1 - t2[i]) * D.x, C.y * t2[i] + (1 - t2[i]) * D.y);
			if (i) E[ce++] = EDGE(i - 1 + n, i + n, dis(p2[i - 1], p2[i]));
		}
		build();
		printf("%.3lf\n", kruskal());
	}
	return 0;
}
