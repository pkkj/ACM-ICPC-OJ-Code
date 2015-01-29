// CII 4499
// 2009 Dhaka: Camera in the Museum
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define N 10005
#define EPS 1e-10
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
double sqr(double x) {
	return x * x;
}
struct POINT {
	double x, y;
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
	bool operator<(const POINT &p) const {
		if (sgn(p.x - x)) return x < p.x;
		return y < p.y;
	}
	void get() {
		scanf("%lf%lf", &x, &y);
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
LINE L[4];
struct EVENT {
#define IN 1
#define OUT 2
	double p;
	int type;
	EVENT() {
	}
	EVENT(POINT po, int type, int i) :
		type(type) {
		if (sgn(L[i].a.x - L[i].b.x)) p = po.x;
		else p = po.y;
	}
	bool operator <(const EVENT &e) const {
		return p < e.p;
	}
};
EVENT E[4][N * 4];
int ecnt[4], n;
POINT C;
double H, W, R;
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
bool line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return 0;
}
 
POINT rotate(const POINT &p, double sina, double cosa) {
	POINT ret;
	ret.x = p.x * cosa - p.y * sina;
	ret.y = p.x * sina + p.y * cosa;
	return ret;
}
bool point_in_line(POINT &p, LINE l) {
	if (sgn(l.a.x - l.b.x)) return p.x >= min(l.a.x, l.b.x) - EPS && p.x <= max(l.a.x, l.b.x) + EPS;
	return p.y >= min(l.a.y, l.b.y) - EPS && p.y <= max(l.a.y, l.b.y) + EPS;
}
void calc() {
	POINT p, vec, pa, pb;
	double dd, d2, sina, cosa;
	int i;
	p.get();
	dd = dis(p, C);
	d2 = sqrt(dd * dd - R * R);
	sina = R / dd, cosa = d2 / dd;
	vec = C - p;
	pa = rotate(vec, sina, cosa), pb = rotate(vec, -sina, cosa);
	pa = pa + p, pb = pb + p;
	for (i = 0; i < 4; i++) {
		POINT it1, it2;
		bool in1, in2;
		in1 = sgn(cross(p, L[i].a, pa)) >= 0 && sgn(cross(p, pb, L[i].a)) >= 0;
		in2 = sgn(cross(p, L[i].b, pa)) >= 0 && sgn(cross(p, pb, L[i].b)) >= 0;
		if (in1 && in2) {
		} else if (in1 || in2) {
			bool ok = line_inter(p, pa, L[i].a, L[i].b, it1);
			if (!ok || !point_in_line(it1, L[i]) || sgn(dot(p, pa, it1)) < 0) line_inter(p, pb, L[i].a, L[i].b, it1);
			if (in1) {
				E[i][ecnt[i]++] = EVENT(it1, IN, i);
				E[i][ecnt[i]++] = EVENT(L[i].b, OUT, i);
			} else {
				E[i][ecnt[i]++] = EVENT(L[i].a, IN, i);
				E[i][ecnt[i]++] = EVENT(it1, OUT, i);
			}
		} else {
			bool ok1 = line_inter(p, pa, L[i].a, L[i].b, it1);
			bool ok2 = line_inter(p, pb, L[i].a, L[i].b, it2);
			if (ok1 && ok2 && point_in_line(it1, L[i]) && point_in_line(it2, L[i]) && sgn(dot(p, pa, it1)) >= 0 && sgn(
					dot(p, pb, it2)) >= 0) {
				if (it2 < it1) swap(it1, it2);
				E[i][ecnt[i]++] = EVENT(L[i].a, IN, i);
				E[i][ecnt[i]++] = EVENT(it1, OUT, i);
				E[i][ecnt[i]++] = EVENT(it2, IN, i);
				E[i][ecnt[i]++] = EVENT(L[i].b, OUT, i);
			} else {
				E[i][ecnt[i]++] = EVENT(L[i].a, IN, i);
				E[i][ecnt[i]++] = EVENT(L[i].b, OUT, i);
			}
		}
	}
}
int solve() {
	int i, j, ans = 0;
	L[0] = LINE(POINT(0, 0), POINT(W, 0));
	L[1] = LINE(POINT(W, 0), POINT(W, H));
	L[2] = LINE(POINT(0, 0), POINT(0, H));
	L[3] = LINE(POINT(0, H), POINT(W, H));
	memset(ecnt, 0, sizeof(ecnt));
	for (i = 0; i < n; i++)
		calc();
	for (i = 0; i < 4; i++) {
		int tmp = 0;
		sort(E[i], E[i] + ecnt[i]);
		for (j = 0; j < ecnt[i]; j++) {
			if (E[i][j].type == IN) tmp++;
			else tmp--;
			ans = max(ans, tmp);
		}
	}
	return ans;
}
 
int main() {
	int ca = 1;
 
	while (scanf("%lf%lf%lf%lf%lf%d", &H, &W, &R, &C.x, &C.y, &n) && H)
		printf("Case %d: %d\n", ca++, solve());
	return 0;
}
