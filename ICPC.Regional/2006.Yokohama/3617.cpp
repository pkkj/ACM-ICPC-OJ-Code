// 2006 Yokohama: How I Mathematician Wonder What You Are!
// ACM-ICPC Live Archive 3617
// POJ 3130
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define PRECISION  1e-8

int cmpzero(double d) {
	return (fabs(d) < PRECISION) ? 0 : (d > 0 ? 1 : -1);
}

inline bool zero(double x) {
	return (fabs(x) < PRECISION);
}

inline double sqr(double x) {
	return x * x;
}

struct POINT {
	double x, y;
	POINT() : x(0), y(0) { }
	POINT(double x, double y) : x(x), y(y) { }
};

inline bool operator==(const POINT &a, const POINT & b) {
	return cmpzero(a.x - b.x) == 0 && cmpzero(a.y - b.y) == 0;
}

inline bool operator<(const POINT &a, const POINT & b) {
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

inline bool operator!=(const POINT &a, const POINT &b) {
	return !(a == b);
}

typedef POINT VECTOR;

struct LINE_EQ {
	double a, b, c;
};

struct LINE {
	POINT p1, p2;
	LINE() : p1(0, 0), p2(0, 0) { }
	LINE(POINT x, POINT y) : p1(x), p2(y) { }
};

VECTOR make_vec(const POINT &ps, const POINT &pe) {
	return VECTOR(pe.x - ps.x, pe.y - ps.y);
}

double crossdet(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

double crossdet(const VECTOR &v1, const VECTOR &v2) {
	return v1.x * v2.y - v2.x * v1.y;
}

LINE_EQ make_line(const LINE &l) {
	LINE_EQ tl;
	int sign = 1;
	tl.a = l.p2.y - l.p1.y;
	if (tl.a < 0) {
		sign = -1;
		tl.a = sign * tl.a;
	}
	tl.b = sign * (l.p1.x - l.p2.x);
	tl.c = sign * (l.p1.y * l.p2.x - l.p1.x * l.p2.y);
	return tl;
}

void line_intersect_pt(const LINE_EQ &l1, const LINE_EQ &l2, POINT &p) {
	double d = l1.a * l2.b - l2.a * l1.b;
	p.x = (l2.c * l1.b - l1.c * l2.b) / d;
	p.y = (l2.a * l1.c - l1.a * l2.c) / d;
}

struct POLY {
	int n;
	double area;
	POINT data[2000];
};

double polyArea(POLY &p) {
	double s = p.data[0].y * (p.data[p.n - 1].x - p.data[1].x);
	for (int i = 1; i < p.n; i++)
		s += p.data[i].y * (p.data[i - 1].x - p.data[(i + 1) % p.n].x);
	p.area = s / 2;
	return s / 2;
}

void polyChangeClockwise(POLY &p) {
	for (int i = 0; i <= (p.n - 1) / 2; i++)
		swap(p.data[i], p.data[p.n - i - 1]);
}

POLY polygonCut(const POINT &p1, const POINT &p2, POLY polygon) {
	POLY new_polygon;	// The new polygon after half-plane cut
	POINT interp;		// Record the intersecting points
	LINE l1, l2;
	double t1, t2;
	new_polygon.n = 0;
	for (int i = 0; i <= polygon.n - 1; i++) { 
		// Cut p[i]p[i+1] with p1p2
		t1 = crossdet(make_vec(p1, p2), make_vec(p1, polygon.data[i]));
		t2 = crossdet(make_vec(p1, p2), make_vec(p1, polygon.data[i + 1]));
		if (zero(t1) || zero(t2)) {	
			// Case I: p1p2 and p[i]p[i+1] are in the same line
			if (zero(t1)) new_polygon.data[new_polygon.n++] = polygon.data[i];   
			if (zero(t2)) new_polygon.data[new_polygon.n++] = polygon.data[i + 1];
		}
		else if (t1 < 0 && t2 < 0) { 
			// Case II: no intersecting point found. The current edge in the polygon should be kept (it's in the convex hull)
			new_polygon.data[new_polygon.n++] = polygon.data[i];
			new_polygon.data[new_polygon.n++] = polygon.data[i + 1];
		}
		else if (t1 * t2 < 0) {	
			// Case III: two segments intersect
			l1.p1 = p1, l1.p2 = p2;
			l2.p1 = polygon.data[i], l2.p2 = polygon.data[i + 1];
			line_intersect_pt(make_line(l1), make_line(l2), interp);
			if (t1 < 0) {
				new_polygon.data[new_polygon.n++] = polygon.data[i];
				new_polygon.data[new_polygon.n++] = interp;
			}
			else {
				new_polygon.data[new_polygon.n++] = interp;
				new_polygon.data[new_polygon.n++] = polygon.data[i + 1];
			}
		}
	}
	polygon.n = 0;
	if (new_polygon.n == 0) return polygon;
	polygon.data[polygon.n++] = new_polygon.data[0];
	// Remove duplicated points
	for (int i = 1; i < new_polygon.n; i++) {
		if (new_polygon.data[i] != new_polygon.data[i - 1]) {
			polygon.data[polygon.n++] = new_polygon.data[i];
		}
	}
	if (polygon.n != 1 && polygon.data[polygon.n - 1] == polygon.data[0]) polygon.n--;
	polygon.data[polygon.n] = polygon.data[0];
	return polygon;
}

int main() {
	int i, n;
	while (scanf("%d", &n) && n) {
		POLY polygon, new_polygon;

		polygon.n = n;
		for (i = 0; i < n; i++)
			scanf("%lf %lf", &polygon.data[i].x, &polygon.data[i].y);
		// The input must be in clockwise. Change the order if necessary
		if (polyArea(polygon) > 0)
			polyChangeClockwise(polygon);
		polygon.data[polygon.n] = polygon.data[0];
		new_polygon = polygon;
		for (i = 0; i < polygon.n; i++)
			new_polygon = polygonCut(polygon.data[i], polygon.data[i + 1], new_polygon);
		if (new_polygon.n >= 1)
			printf("1\n");
		else
			printf("0\n");
	}
	return 0;
}
