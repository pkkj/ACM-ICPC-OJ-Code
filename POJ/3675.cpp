// POJ 3675
// POJ Founder Monthly Contest – 2008.07.27: Telescope
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define EPS 1e-7
#define N 55
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	POINT() {
		x = 0, y = 0;
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT operator+(const POINT &p) {
		return POINT(x + p.x, y + p.y);
	}
	POINT operator-(const POINT &p) {
		return POINT(x - p.x, y - p.y);
	}
	POINT operator*(const double &v) {
		return POINT(x * v, y * v);
	}
	POINT operator/(const double &v) {
		return POINT(x / v, y / v);
	}
	double operator *(POINT &p) {
		return x * p.x + y * p.y;
	}
	double dis2() {
		return x * x + y * y;
	}
	double dis() {
		return sqrt(x * x + y * y);
	}
	POINT unit() {
		return *this / dis();
	}
};
int sgn(double x) {
	return x < -EPS ? -1 : (x > EPS);
}
 
POINT pl[N];
double R;
double cross(const POINT &a, const POINT &b, const POINT &c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
int inbound(POINT &a, POINT &b, POINT &c) {
	return a.x <= max(b.x, c.x) && a.x >= min(b.x, c.x) && a.y <= max(b.y, c.y) && a.y >= min(b.y, c.y);
}
int incircle(POINT &p) {
	return sgn(R - p.dis()) >= 0;
}
int solve_two_eq(double a, double b, double c, double &x1, double &x2) {
	double d = b * b - 4 * a * c;
	if (sgn(d) < 0) return -1;
	d = sqrt(d);
	x1 = (-b + d) / 2.0 / a;
	x2 = (-b - d) / 2.0 / a;
	if (sgn(d) == 0) return 0;
	return 1;
}
int line_inter_circle(POINT A, POINT B, POINT &C, POINT &D) {
	POINT v;
	double a, b, c, x1, x2;
	int ret;
	v = A - B;
	a = v.dis2();
	b = 2.0 * (B * v);
	c = B.dis2() - R * R;
	ret = solve_two_eq(a, b, c, x1, x2);
	if (ret < 0) return 0;
	C = B + v * x1;
	D = B + v * x2;
	return inbound(C, B, A) || inbound(D, B, A);
}
 
double area_sector(POINT &a, POINT &b) {
	double angle = asin((a - b).dis() / R / 2.0);
	return fabs(angle * R * R);
}
double tri_circle(POINT a, POINT b) {
	int t1 = incircle(a), t2 = incircle(b);
	int sign = sgn(cross(POINT(), a, b));
	if (sign == 0) return 0;
	if (t1 && t2) return fabs(cross(POINT(), a, b)) / 2.0 * sign;
	if (t1 || t2) {
		if (t1) swap(a, b);
		POINT c = a.unit() * R, d, e;
		line_inter_circle(a, b, d, e);
		if (!inbound(d, a, b)) d = e;
		return (area_sector(c, d) + fabs(cross(POINT(), b, d) / 2.0)) * sign;
	}
	POINT c, d, e, f;
	c = a.unit() * R;
	d = b.unit() * R;
	if (line_inter_circle(a, b, e, f)) return (area_sector(c, e) + area_sector(d, f) + fabs(cross(POINT(), e, f) / 2.0)) * sign;
	return area_sector(c, d) * sign;
}
 
int main() {
	int n;
	while (scanf("%lf", &R) != EOF) {
		double ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			pl[i].get();
		pl[n] = pl[0];
		for (int i = 0; i < n; i++)
			ans += tri_circle(pl[i], pl[i + 1]);
		printf("%.2lf\n", fabs(ans));
	}
	return 0;
}
