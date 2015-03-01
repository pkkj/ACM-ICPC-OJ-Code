// 2000 Tehran: 3002 Rubbery
// ACM-ICPC Live Archive 2060
// POJ 1689

#include <cstdio>
#include <cmath>
#include <cstring>
#include <set>
using namespace std;

#define NP 55
#define PRECISION  1e-8

inline int sgn(double x) {
	return (x < -PRECISION) ? -1 : x > PRECISION;
}

struct POINT {
	double x, y;

	POINT(double x, double y) :
			x(x), y(y) {
	}

	POINT() :
			x(0), y(0) {
	}

};

struct POLY {
	int n;
	POINT data[NP];
	double area;
};

double poly_area(POLY &p) {
	double s = p.data[0].y * (p.data[p.n - 1].x - p.data[1].x);
	for (int i = 1; i < p.n; i++)
		s += p.data[i].y * (p.data[i - 1].x - p.data[(i + 1) % p.n].x);
	return s / 2;
}

double cross(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}
int crossi(const POINT &a, const POINT &c, const POINT &d) {
	return sgn(cross(a.x - c.x, a.y - c.y, d.x - c.x, d.y - c.y));
}
double dotdet(double x1, double y1, double x2, double y2) {
	return x1 * x2 + y1 * y2;
}

int between(const POINT &a, const POINT &c, const POINT &d) {
	return sgn(dotdet(c.x - a.x, c.y - a.y, d.x - a.x, d.y - a.y)) != 1;
}
int seg_intersect(const POINT &a, const POINT &b, const POINT &c, const POINT &d) {
	int a_cd = crossi(a, c, d);
	if (a_cd == 0 && between(a, c, d))
		return 2;
	int b_cd = crossi(b, c, d);
	if (b_cd == 0 && between(b, c, d))
		return 2;
	int c_ab = crossi(c, a, b);
	if (c_ab == 0 && between(c, a, b))
		return 2;
	int d_ab = crossi(d, a, b);
	if (d_ab == 0 && between(d, a, b))
		return 2;
	if ((a_cd ^ b_cd) == -2 && (c_ab ^ d_ab) == -2)
		return 1;
	return 0;
}
int point_in_poly(POLY &p, POINT pt) {
	int num = 0;
	p.data[p.n] = p.data[0];
	POINT inf;
	inf.x = 3e9, inf.y = 1e7;
	for (int i = 0; i < p.n; i++)
		if (seg_intersect(pt, inf, p.data[i], p.data[i + 1]))
			num++;
	if (num % 2)
		return 1;
	else
		return 0;
}

#define N 60
POLY polygon[N];
int fmap[500][500];
set<double> gx, gy;
int px, py;
int ans;
void dfs(int x, int y) {
	if (x == 0 || y == 0 || x == px + 1 || y == py + 1 || fmap[x][y] == -1)
		return;
	ans += fmap[x][y];
	fmap[x][y] = -1;
	if (fmap[x + 1][y] != -1)
		dfs(x + 1, y);
	if (fmap[x][y - 1] != -1)
		dfs(x, y - 1);
}

void solve() {
	int i, n, ok;
	double w, h, dx, dy, curs = 0;

	scanf("%lf%lf", &w, &h);
	scanf("%d", &n);
	for (int k = 0; k < n; k++) {
		scanf("%d", &polygon[k].n);
		for (i = 0; i < polygon[k].n; i++)
			scanf("%lf%lf", &polygon[k].data[i].x, &polygon[k].data[i].y);
		curs += fabs(poly_area(polygon[k]));
	}
	gx.clear(), gy.clear();
	gx.insert(0), gx.insert(w);
	gy.insert(0), gy.insert(h);
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < polygon[k].n; i++)
			gx.insert(polygon[k].data[i].x), gy.insert(polygon[k].data[i].y);
	}
	set<double>::iterator iy, ix;
	memset(fmap, -1, sizeof(fmap));
	for (iy = gy.begin(), py = 0; iy != gy.end(); ++iy, py++) {

		if (py == 0) {
			dy = *iy;
			continue;
		}

		for (ix = gx.begin(), px = 0; ix != gx.end(); ++ix, px++) {
			if (px == 0) {
				dx = *ix;
				continue;
			}
			POINT md = POINT((*ix + dx) / 2.0, (*iy + dy) / 2.0);
			for (i = 0, ok = 1; i < n; i++) {
				if (point_in_poly(polygon[i], md)) {
					fmap[py][px] = -1, ok = 0;
					break;
				}
			}
			if (ok == 1)
				fmap[py][px] = (int) ((*ix - dx) * (*iy - dy));
			dx = *ix;
		}
		dy = *iy;
	}
	ans = 0;
	dfs(1, px - 1);
	printf("%d\n", (int) (w * h - ans - curs));
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
