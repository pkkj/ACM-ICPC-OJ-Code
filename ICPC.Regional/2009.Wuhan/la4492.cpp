// 2009 Wuhan: Jiajia's Robot
// ACM-ICPC Live Archive 4492
// HDU 3239 
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define PI 3.14159265358979323846
#define EPS 1e-8
#define IN 1
#define OUT 2
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
double fix(double x) {
	return x + EPS;
}
#define NP 1005
struct POINT {
	double x, y, r, ang;
	int st;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT(double x, double y, double r) :
		x(x), y(y), r(r) {
	}
	POINT(double x, double y, double ang, int st) :
		x(x), y(y), ang(ang), st(st) {
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
	bool operator ==(const POINT &p) {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	bool operator !=(const POINT &p) {
		return sgn(x - p.x) != 0 || sgn(y - p.y) != 0;
	}
	POINT toLength(double k) {
		double v = k / abs();
		return POINT(x * v, y * v);
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
bool cmpang(const POINT &p1, const POINT &p2) {
	if (p1.ang != p2.ang) return p1.ang < p2.ang;
	return p1.st < p2.st;
}
double sqr(double x) {
	return x * x;
}

inline double cross(POINT o, POINT a, POINT b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

POINT rotate(const POINT &p, double sina, double cosa) {
	POINT ret;
	ret.x = p.x * cosa - p.y * sina;
	ret.y = p.x * sina + p.y * cosa;
	return ret;
}

bool intersect(POINT &a, POINT &b, POINT &p1, POINT &p2) {
	double d = sqr(a.x - b.x) + sqr(a.y - b.y), sina, cosa;
	if (d >= sqr(a.r + b.r)) return false;
	if (d <= sqr(a.r - b.r)) return false;
	d = sqrt(d);
	cosa = (sqr(a.r) + sqr(d) - sqr(b.r)) / 2 / d / a.r;
	sina = sqrt(1 - cosa * cosa);
	POINT v = b - a;
	v = v.toLength(a.r);
	p1 = rotate(v, sina, cosa), p2 = rotate(v, -sina, cosa);

	p1 = a + p1, p2 = a + p2;
	return true;
}
double calcfan(POINT &o, POINT &a, POINT &b) {
	double ans = o.r * o.r * (b.ang - a.ang) * 0.5;
	ans -= fabs(cross(o, a, b) / 2.0);
	return ans;
}
double calcang(POINT &o, POINT &p) {
	double ans = atan2(p.y - o.y, p.x - o.x);
	if (ans < 0) ans = 2 * PI + ans;
	return ans;
}
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
POINT intset[NP];
double area(vector<POINT> &oldp) {
	int i, j, n = (int) oldp.size();
	vector<POINT> p;
	double ans = 0;

	for (i = 0; i < n; i++) {
		bool ok = true;
		for (j = 0; j < n; j++) {
			if (i == j) continue;
			double dis2 = sqr(oldp[i].x - oldp[j].x) + sqr(oldp[i].y - oldp[j].y);
			if (sgn(dis2 - sqr(oldp[i].r - oldp[j].r)) == 0 && sgn(oldp[i].r - oldp[j].r) == 0 && i > j) ok = false;
		}
		if (ok) p.push_back(oldp[i]);
	}
	n = (int) p.size();
	for (i = 0; i < n; i++) {
		POINT p1, p2;
		int cnt = 0;
		intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 0, IN);
		intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 0, OUT);
		intset[cnt++] = POINT(p[i].x - p[i].r, p[i].y, PI, IN);
		intset[cnt++] = POINT(p[i].x - p[i].r, p[i].y, PI, OUT);
		intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 2 * PI, IN);
		intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 2 * PI, OUT);

		for (j = 0; j < n; j++) {
			if (i == j) continue;
			double dis2 = sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y);
			if (sgn(dis2 - sqr(p[i].r - p[j].r)) <= 0 && sgn(p[i].r - p[j].r) == -1) {
				intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 0, IN);
				intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 2 * PI, OUT);
				continue;
			}

			if (intersect(p[i], p[j], p1, p2)) {
				p1.ang = calcang(p[i], p1);
				p2.ang = calcang(p[i], p2);
				if (p1.ang < p2.ang) {
					intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 0, IN);
					intset[cnt++] = POINT(p[i].x + p[i].r, p[i].y, 2 * PI, OUT);
				}
				intset[cnt++] = POINT(p1.x, p1.y, p1.ang, OUT);
				intset[cnt++] = POINT(p2.x, p2.y, p2.ang, IN);
			}
		}
		sort(intset, intset + cnt, cmpang);
		int cov = 0;
		for (j = 0; j < cnt; j++) {
			(intset[j].st == IN) ? cov++ : cov--;
			if (!cov && j + 1 < cnt) {
				ans += cross(POINT(0, 0), intset[j], intset[j + 1]) / 2.0;
				ans += calcfan(p[i], intset[j], intset[j + 1]);
			}
			if (cov == n - 1 && j + 1 < cnt) {
				ans -= cross(POINT(0, 0), intset[j], intset[j + 1]) / 2.0;
				ans -= calcfan(p[i], intset[j], intset[j + 1]);
			}
		}
	}

	return ans;
}
double solve() {
	POINT p[4];
	vector<POINT> pl;
	for (int i = 0; i < 4; i++)
		p[i].get();
	bool has = false;
	for (int i = 0; i < 4; i++)
		if (p[i] != POINT(0, 0)) has = true;
	if (!has) return -1.0;
	pl.push_back(POINT((p[0] + p[2]).x / 2.0, (p[0] + p[2]).y / 2.0, dis(p[0], p[2]) / 2.0));
	pl.push_back(POINT((p[0] + p[3]).x / 2.0, (p[0] + p[3]).y / 2.0, dis(p[0], p[3]) / 2.0));
	pl.push_back(POINT((p[1] + p[2]).x / 2.0, (p[1] + p[2]).y / 2.0, dis(p[1], p[2]) / 2.0));
	pl.push_back(POINT((p[1] + p[3]).x / 2.0, (p[1] + p[3]).y / 2.0, dis(p[1], p[3]) / 2.0));
	return area(pl);
}

int main() {
	int ca = 1;
	double ans = 0;
	while ((ans = solve()) > 0)
		printf("Case %d: %.3lf\n\n", ca++, ans);

	return 0;
}

