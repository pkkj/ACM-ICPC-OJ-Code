// 2007 Northwestern Europe: Flight Safety
// ACM-ICPC Live Archive 3976
// POJ 3502
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

const int N = 40;
const double EPS = 1e-8;
const double INF = 1e30;
const int IN = 0;
const int OUT = 1;

inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

struct POINT {
	double x, y;
	POINT() : x(0), y(0) { }
	POINT(double x, double y) : x(x), y(y) { }
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	POINT operator /(const double & v) {
		return POINT(x / v, y / v);
	}
	double operator *(POINT &p) {
		return x * p.x + y * p.y;
	}
	POINT operator *(const double &v) {
		return POINT(x * v, y * v);
	}
	bool operator<(const POINT &p) const {
		return sgn(y - p.y) < 0;
	}
	bool operator==(const POINT &p) const {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	double abs2() {
		return x * x + y * y;
	}
	POINT toLen(double len) {
		double unit = abs();
		return POINT(x * len / unit, y * len / unit);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

struct POLYGON {
	POINT p[N];
	int size;
	void read() {
		scanf("%d", &size);
		for (int i = 0; i < size; i++)
			p[i].read();
		p[size] = p[0];
	}
};

double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
int between(POINT &o, POINT &a, POINT &b) {
	return sgn(dot(o, a, b)) != 1;
}

int seg_intersect(POINT &a, POINT &b, POINT &c, POINT &d) {
	int a_cd = sgn(cross(c, a, d));
	if (a_cd == 0 && between(a, c, d)) return 2;
	int b_cd = sgn(cross(c, b, d));
	if (b_cd == 0 && between(b, c, d)) return 2;
	int c_ab = sgn(cross(a, c, b));
	if (c_ab == 0 && between(c, a, b)) return 2;
	int d_ab = sgn(cross(a, d, b));
	if (d_ab == 0 && between(d, a, b)) return 2;
	if ((a_cd ^ b_cd) == -2 && (c_ab ^ d_ab) == -2) return 1;
	return 0;
}

int point_in_poly(POINT &pt, POLYGON &p) {
	int num = 0;
	POINT inf(3e10, 1e10);
	for (int i = 0; i < p.size; i++)
		if (seg_intersect(pt, inf, p.p[i], p.p[i + 1]))
			num++;
	return num % 2;
}

int line_intersect(POINT &a, POINT &b, POINT &c, POINT &d, POINT &intersect) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		intersect = (c * v + d * u) / (u + v);
		return 1;
	}
	return 0;
}

// Find the intersection of a segment and a circle.
bool seg_circle_intersect(POINT A, POINT B, POINT O, double R, POINT intersect[]) {
	POINT toO = O - POINT(0, 0);
	A = A - toO, B = B - toO;
	POINT v = A - B;
	double a = v.abs2();
	double b = 2.0 * (B * v);
	double c = B.abs2() - R * R;
	double d = b * b - 4 * a * c;
	if (sgn(d) < 0)
		return false;
	d = sqrt(d);
	double x1 = (-b + d) / 2.0 / a;
	double x2 = (-b - d) / 2.0 / a;

	POINT C = B + v * x1, D = B + v * x2;
	intersect[0] = C + toO, intersect[1] = D + toO;
	return true;

}

// Find the intersection of a segment and a polygon.
// Be very careful when handling some tricky data.
bool seg_convex_intersect(POINT &A, POINT &B, POLYGON &poly, POINT intersect[]) {
	intersect[0] = POINT(INF, INF), intersect[1] = POINT(-INF, -INF);
	for (int i = 0; i < poly.size; i++) {
		POINT tmp;
		if (line_intersect(poly.p[i], poly.p[i + 1], A, B, tmp)) {
			if (between(tmp, poly.p[i], poly.p[i + 1])){
				intersect[0] = min(intersect[0], tmp);
				intersect[1] = max(intersect[1], tmp);
			}
		}
		else if (sgn(cross(poly.p[i], A, B)) == 0){
			intersect[0] = poly.p[i], intersect[1] = poly.p[i + 1];
			break;
		}
	}

	return intersect[0].x != INF;
}

// Create a rectangle from an edge. Moving the edge by a given distance
void make_rect(POINT &p1, POINT &p2, POLYGON &rect, double distance) {
	POINT v = p2 - p1;
	POINT nv = POINT(v.y, -v.x).toLen(distance);

	rect.size = 4;
	rect.p[0] = rect.p[4] = p1 + nv;
	rect.p[1] = p2 + nv;	
	rect.p[2] = p2 - nv;
	rect.p[3] = p1 - nv;
}

// Insert an interval (range covered by the extension of polygons' edge abd vertex) into the list.
void insert_interval(vector< pair<POINT, int> > &internvals, POINT &r0, POINT &r1, POINT &its0, POINT &its1) {
	if (its0 == its1)
		return;
	if (its1 < its0)
		swap(its1, its0);
	if (r0 < its1 && its0 < r1){
		if (its0 < r0) its0 = r0;
		if (r1 < its1) its1 = r1;
		internvals.push_back(make_pair(its0, IN));
		internvals.push_back(make_pair(its1, OUT));
	}
}
POLYGON polys[N], rects[N][N];
POINT route[N][2];
int np, nr, T;

bool check(double distance) {
	POINT intersect[2];

	for (int i = 0; i < np; i++)
		for (int j = 0; j < polys[i].size; j++)
			make_rect(polys[i].p[j], polys[i].p[j + 1], rects[i][j], distance);

	for (int ir = 0; ir < nr - 1; ir++) {
		vector< pair<POINT, int> > internvals;

		// Extend polygons' edge and vertex, forming rectangles and circles.
		// Find the range of current segments covered by the extension of continents.
		for (int i = 0; i < np; i++) {
			for (int j = 0; j < polys[i].size; j++) {
				if (seg_convex_intersect(route[ir][0], route[ir][1], rects[i][j], intersect)) {
					insert_interval(internvals, route[ir][0], route[ir][1], intersect[0], intersect[1]);
				}
				if (seg_circle_intersect(route[ir][0], route[ir][1], polys[i].p[j], distance, intersect)) {
					insert_interval(internvals, route[ir][0], route[ir][1], intersect[0], intersect[1]);
				}
			}
		}

		POINT begin = route[ir][0], end = route[ir][1];
		insert_interval(internvals, begin, end, begin, end);
		sort(internvals.begin(), internvals.end());

		// Check the parts which are not covered by any extension of continents. 
		// If we can find a part outside all continents, we can confirm that the given distance cannot cover all the routes. We need to enlarge the distance in next iteration.
		int coverCnt = 0;
		for (size_t i = 0; i < internvals.size(); i++) {
			internvals[i].second == IN ? coverCnt++ : coverCnt--;

			if (coverCnt == 1 && i + 1 < internvals.size() && !(internvals[i].first == internvals[i + 1].first)) {
				// We only need to check whether an endpoint of current interval is inside a continent.
				bool ok = true;
				for (int j = 0; j < np; j++ && ok) {
					if (point_in_poly(internvals[i].first, polys[j]) || point_in_poly(internvals[i + 1].first, polys[j]))
						ok = false;
				}
				if (ok) return true;
			}
		}
	}

	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &np, &nr);
		for (int i = 0; i < nr; i++) {
			route[i][0].read();
			if (i){
				route[i - 1][1] = route[i][0];
				if (route[i - 1][1] < route[i - 1][0])
					swap(route[i - 1][0], route[i - 1][1]);
			}
		}
		for (int i = 0; i < np; i++) 
			polys[i].read();

		double l = 0, h = 5e4;
		while (h - l > 1e-4) {
			double mid = (l + h) / 2.0;
			check(mid) ? l = mid : h = mid;
		}
		printf("%.8lf\n", l);
	}
	return 0;
}
