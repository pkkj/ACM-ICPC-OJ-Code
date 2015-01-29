// 2006 Yokohama: Polygons on the Grid
// ACM-ICPC Live Archive 3622
// POJ 3135
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
using namespace std;
#define N 10
#define EPS 1e-7


inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
struct POINT {
	int x, y;
	POINT() { }
	POINT(int x, int y) : x(x), y(y) { }
	POINT operator+(const POINT &p) {
		return POINT(x + p.x, y + p.y);
	}
	int abs() {
		return x * x + y * y;
	}
};

int cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int cross2(const POINT &a, const POINT &b) {
	return a.x * b.y - a.y * b.x;
}
int dis2(POINT &a, POINT &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
bool isInteger(double x) {
	return sgn(floor(x) - x) == 0 || sgn(ceil(x) - x) == 0;
}
struct POINTF {
	double x, y;
	POINTF() { }
	POINTF(double x, double y) : x(x), y(y) { }
	POINTF(POINT p) : x(p.x), y(p.y) { }
	POINT toPoint() {
		int ix = sgn(floor(x) - x) == 0 ? int(floor(x)) : int(ceil(x));
		int iy = sgn(floor(y) - y) == 0 ? int(floor(y)) : int(ceil(y));
		return POINT(ix, iy);
	}
	POINTF operator +(const POINTF & b) {
		return POINTF(x + b.x, y + b.y);
	}
	POINTF operator *(const double & v) {
		return POINTF(x * v, y * v);
	}
	void unit() {
		double k = sqrt(x * x + y * y);
		x /= k, y /= k;
	}
	bool isGridPoint() {
		return isInteger(x) && isInteger(y);
	}
};

// Find the intersections of two circles
double dis2f(const POINTF &p1, const POINTF &p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);;
}
bool intersect(const POINTF &a, double ra, const POINTF &b, double rb,
	POINTF &p1, POINTF &p2) {
	double d = dis2f(a, b);
	if (d > (ra + rb) * (ra + rb))
		return false;
	if (d < (ra - rb) * (ra - rb))
		return false;
	double cosa = (ra * ra + d - rb * rb) / 2 / sqrt(d) / ra;
	double sina = sqrt(1 - cosa * cosa);
	POINTF v = POINTF(b.x - a.x, b.y - a.y);
	v.unit();
	v = v * ra;
	p1 = POINTF(v.x * cosa - v.y * sina, v.x * sina + v.y * cosa) + a;
	p2 = POINTF(v.x * cosa + v.y * sina, -v.x * sina + v.y * cosa) + a;
	return true;
}

#define RANGE 300
vector<POINT> fast[RANGE * RANGE * 2 + 10];
POINT poly[N];
int len[N], lenFromRight[N], n;
int maxArea, totalLen;
void dfs(int dep) {
	if (lenFromRight[dep] < poly[dep].abs())
		return;

	// When two edges left, you can find the final one by calculation. No more searching requires.
	if (dep == n - 2) {
		POINTF p1, p2;
		if (intersect(POINTF(poly[0]), len[n - 1], POINTF(poly[dep]), len[dep], p1, p2)) {
			POINT ip1 = p1.toPoint(), ip2 = p2.toPoint();
			if (p1.isGridPoint() && cross(poly[dep], ip1, poly[0]) >= 0 && cross(ip1, poly[0], poly[1]) >= 0) {
				int area = 0;
				poly[dep + 1] = ip1;
				for (int i = 0; i < n; i++)
					area += cross2(poly[i], poly[(i + 1) % n]);
				if (area > 0)
					maxArea = max(area, maxArea);
			}
			if (p2.isGridPoint() && cross(poly[dep], ip2, poly[0]) >= 0 && cross(ip2, poly[0], poly[1]) >= 0) {
				int area = 0;
				poly[dep + 1] = ip2;
				for (int i = 0; i < n; i++)
					area += cross2(poly[i], poly[(i + 1) % n]);
				if (area > 0)
					maxArea = max(area, maxArea);
			}
		}
		return;
	}

	int l2 = len[dep] * len[dep];
	for (int i = 0; i < fast[l2].size(); i++) {
		POINT newPoint = poly[dep] + fast[l2][i];
		// Use the convex-polygon condition to cut the branches.
		if (cross2(poly[1], newPoint) < 0 || cross(poly[dep], POINT(0, 0), newPoint) > 0 || cross(poly[dep - 1], poly[dep], newPoint) < 0)
			continue;
		poly[dep + 1] = newPoint;
		dfs(dep + 1);
	}
}
void solve() {
	maxArea = -2;
	sort(len, len + n);
	totalLen = 0;
	for (int i = 0; i < n; i++)
		totalLen += len[i];

	swap(len[0], len[n - 1]);
	sort(len + 1, len + n);
	do {
		poly[0] = POINT(0, 0);
		int l2 = len[0] * len[0];
		for (int i = n - 1; i >= 0; i--)
			lenFromRight[i] = lenFromRight[i + 1] + len[i];

		for (int i = 0; i < n; i++)
			lenFromRight[i] = lenFromRight[i] * lenFromRight[i];

		for (int i = 0; i < fast[l2].size(); i++) {
			if (fast[l2][i].x >= 0 && fast[l2][i].y >= 0
				&& fast[l2][i].y <= fast[l2][i].x) {
				poly[1] = fast[l2][i];
				dfs(1);
			}
		}
	} while (next_permutation(len + 1, len + n));
	printf("%d\n", maxArea / 2);
}

int main() {
	for (int x = -RANGE; x <= RANGE; x++)
		for (int y = -RANGE; y <= RANGE; y++)
			fast[x * x + y * y].push_back(POINT(x, y));

	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &len[i]);
		solve();
	}
	return 0;
}
