// 2007 Tokyo: Most Distant Point from the Sea
// ACM-ICPC Live Archive 3890
// POJ 3525
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define EPS 1e-7
#define INF 1e7
#define N 105
double sqr(double x) {
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
	void unit() {
		double d = sqrt(sqr(x) + sqr(y));
		x /= d, y /= d;
	}
	void l90() {
		double nx = -y, ny = x;
		x = nx, y = ny;
	}
};
POINT operator -(const POINT &a, const POINT &b) {
	return POINT(a.x - b.x, a.y - b.y);
}
struct LINE {
	POINT a, b;
	LINE() {
	}
	LINE(double x1, double y1, double x2, double y2) :
		a(x1, y1), b(x2, y2) {
	}
};
int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
inline double cross(POINT &p, POINT &a, POINT &b) {
	return (a.x - p.x) * (b.y - p.y) - (b.x - p.x) * (a.y - p.y);
}
double at[N];
LINE orgin[N], ls[N];
struct POLY {
	POINT pl[N];
	int n;
	POLY() {
		n = 0;
	}
};
double poly_area(POLY &p) {
	double s = 0;
	for (int i = 0; i < p.n; i++)
		s += p.pl[i].x * p.pl[(i + 1) % p.n].y - p.pl[i].y * p.pl[(i + 1) % p.n].x;
	return s / 2;
}
inline bool cmp(int i, int j) {
	if (!sgn(at[i] - at[j])) return sgn(cross(orgin[j].a, orgin[j].b, orgin[i].b)) >= 0;
	return at[i] < at[j];
}
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return -1;
}
bool notin(int x, int y, int z) {
	POINT pt;
	line_inter(ls[x].a, ls[x].b, ls[y].a, ls[y].b, pt);
	return sgn(cross(ls[z].a, ls[z].b, pt)) < 0;
}
int ord[N], dq[N];
POLY ans;
 
void makeinside(int n, double R) {
	for (int i = 0; i < n; i++) {
		POINT v = orgin[i].b - orgin[i].a;
		v.unit();
		v.l90();
		v = v * R;
		ls[i].a = orgin[i].a + v, ls[i].b = orgin[i].b + v;
	}
}
bool halfplane(int n, double R) {
	int i, bot, top;
	makeinside(n, R);
	bot = 1, top = 2;
	dq[bot] = ord[0], dq[top] = ord[1];
	for (i = 2; i < n; i++) {
		while (bot < top && notin(dq[top - 1], dq[top], ord[i]))
			top--;
		while (bot < top && notin(dq[bot + 1], dq[bot], ord[i]))
			bot++;
		dq[++top] = ord[i];
	}
	while (bot < top && notin(dq[top - 1], dq[top], dq[bot]))
		top--;
	while (bot < top && notin(dq[bot + 1], dq[bot], dq[top]))
		bot++;
	dq[--bot] = dq[top];
	for (i = bot + 1, ans.n = 0; i <= top && ans.n < 3; i++)
		line_inter(ls[dq[i - 1]].a, ls[dq[i - 1]].b, ls[dq[i]].a, ls[dq[i]].b, ans.pl[ans.n++]);
	return ans.n == 3;
}
POINT pl[N];
int main() {
	int n, i, tn;
	double low, high, mid;
	while (scanf("%d", &n) && n) {
		for (i = 0; i < n; i++)
			pl[i].get();
		for (i = 0; i < n; i++)
			orgin[i].a = pl[i], orgin[i].b = pl[(i + 1) % n];
		for (i = 0; i < n; i++) {
			at[i] = atan2(orgin[i].b.y - orgin[i].a.y, orgin[i].b.x - orgin[i].a.x);
			ord[i] = i;
		}
		sort(ord, ord + n, cmp);
		for (i = tn = 1; i < n; i++)
			if (sgn(at[ord[i]] - at[ord[i - 1]])) ord[tn++] = ord[i];
		n = tn;
		low = 0, high = INF;
		while (high - low > EPS) {
			mid = (low + high) / 2.0;
			if (halfplane(n, mid)) low = mid;
			else high = mid;
		}
		printf("%.7lf\n", low);
	}
	return 0;
}