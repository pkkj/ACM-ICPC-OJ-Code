// 2007 Seoul: Metor
// ACM-ICPC Live Archive 3905
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 100005
#define PRECISION  1e-8
 
inline int sgn(double x) {
	return (x < -PRECISION) ? -1 : x > PRECISION;
}
inline double sqr(double x) {
	return x * x;
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
	bool operator ==(const POINT &p) {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	bool operator !=(const POINT &p) {
		return sgn(x - p.x) != 0 || sgn(y - p.y) != 0;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
};
inline double cross(POINT &a, POINT &b, POINT &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
// a->b.a->c
inline double dot(POINT &a, POINT &b, POINT &c) {
	return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}
int line_seg_intersect(POINT &a, POINT &b, POINT &c, POINT &d) {
	int c_ab = sgn(cross(a, c, b));
	if (c_ab == 0) return 2;
	int d_ab = sgn(cross(a, d, b));
	if (d_ab == 0) return 2;
	if ((c_ab ^ d_ab) == -2) return 1;
	return 0;
}
void line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	cp = (c * v + d * u) / (u + v);
}
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
struct LINE {
	POINT p1, p2;
};
LINE ll[4];
struct INFO {
	double x;
	int in;
	INFO() {
	}
	INFO(double x, int in) :
		x(x), in(in) {
	}
	bool operator<(const INFO &i) const {
		if (sgn(x - i.x)) return x < i.x;
		return in < i.in;
	}
};
POINT pl[N], vl[N], bo[4];
double w, h;
bool get_range(int idx, double &A, double &B) {
	int i, cnt;
	POINT a, b;
	a = pl[idx], b = POINT(pl[idx].x + 3 * vl[idx].x, pl[idx].y + 3 * vl[idx].y);
	// Inside the rectangle
	if (pl[idx].x > 0 && pl[idx].x < w && pl[idx].y > 0 && pl[idx].y < h) {
		POINT it;
		for (i = 0; i < 4; i++) {
			if (line_seg_intersect(a, b, ll[i].p1, ll[i].p2)) {
				line_inter(a, b, ll[i].p1, ll[i].p2, it);
				double dx = it.x - pl[idx].x, dy = it.y - pl[idx].y;
				if (dx && dx / vl[idx].x < 0) continue;
				if (dy && dy / vl[idx].y < 0) continue;
				break;
			}
		}
		double d = dis(pl[idx], it);
		A = 0, B = d / vl[idx].abs();
	}
	// Outside the rectangle
	else {
		POINT meet[8], it;
		// Check if the meteor run across the endpoint of the rectangle
		for (i = cnt = 0; i < 4; i++) {
			if (sgn(cross(a, b, bo[i])) == 0) {
				double dx = bo[i].x - a.x, dy = bo[i].y - a.y;
				if (dx && dx / vl[idx].x < 0) continue;
				if (dy && dy / vl[idx].y < 0) continue;
				meet[cnt++] = bo[i];
			}
		}
		if (cnt == 2) {
			if (meet[0].x == meet[1].x || meet[0].y == meet[1].y) return 0;
		} else {
			for (i = 0; i < 4; i++) {
				if (line_seg_intersect(a, b, ll[i].p1, ll[i].p2)) {
					line_inter(a, b, ll[i].p1, ll[i].p2, it);
					double dx = it.x - pl[idx].x, dy = it.y - pl[idx].y;
					if (dx && dx / vl[idx].x < 0) continue;
					if (dy && dy / vl[idx].y < 0) continue;
					if (it != ll[i].p1 && it != ll[i].p2) meet[cnt++] = it;
				}
			}
		}
		if (cnt <= 1) return 0;
		A = dis(a, meet[0]) / vl[idx].abs();
		B = dis(a, meet[1]) / vl[idx].abs();
		if (A > B) swap(A, B);
	}
	return 1;
}
INFO io[N * 2];
void solve() {
	int n, i, m, ans, dep;
	double a, b;
	scanf("%lf%lf%d", &w, &h, &n);
	for (i = 0; i < n; i++) {
		pl[i].get();
		vl[i].get();
	}
	bo[0] = POINT(0, 0);
	bo[1] = POINT(w, 0);
	bo[2] = POINT(0, h);
	bo[3] = POINT(w, h);
	ll[0].p1 = POINT(0, 0), ll[0].p2 = POINT(w, 0);
	ll[1].p1 = POINT(0, 0), ll[1].p2 = POINT(0, h);
	ll[2].p1 = POINT(w, 0), ll[2].p2 = POINT(w, h);
	ll[3].p1 = POINT(0, h), ll[3].p2 = POINT(w, h);
	m = 0;
	for (i = 0; i < n; i++)
		if (get_range(i, a, b)) {
			io[m++] = INFO(a, 1);
			io[m++] = INFO(b, 0);
		}
 
	sort(io, io + m);
	ans = 0, dep = 0;
	for (i = 0; i < m; i++) {
		if (io[i].in) dep++;
		else dep--;
		if (dep > ans) ans = dep;
	}
	printf("%d\n", ans);
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}