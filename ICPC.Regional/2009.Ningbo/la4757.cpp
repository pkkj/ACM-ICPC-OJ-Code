// 2009 Ningbo: Open-air shopping malls
// ACM-ICPC Live Archive 4757
#include <cstdio>
#include <cmath>
#include <cstring>
#define N 25
#define EPS 1e-10
#define PI 3.1415926535897
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}

struct POINT {
	double x, y, r, a2;
	void get() {
		scanf("%lf%lf%lf", &x, &y, &r);
		a2 = r * r * PI / 2;
	}
	POINT() {
	}
	POINT(double x, double y) :
			x(x), y(y) {
	}
	POINT(double x, double y, double r) :
			x(x), y(y), r(r) {
	}
	bool operator ==(const POINT &p) {
		return sgn(p.x - x) == 0 && sgn(p.y - y) == 0;
	}
	bool operator <(const POINT &p) const {
		if (sgn(x - p.x))
			return x < p.x;
		return y < p.y;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void unit() {
		double k = abs();
		x /= k, y /= k;
	}
	POINT operator +(const POINT &p) {
		return POINT(x + p.x, y + p.y);
	}
	POINT operator *(double k) {
		return POINT(x * k, y * k);
	}
	void print() {
		printf("%lf %lf ", x, y);
	}
};

double sqr(double x) {
	return x * x;
}
double dis(POINT &a, POINT &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}
double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
POINT rotate(const POINT &p, double a) {
	POINT ret;
	ret.x = p.x * cos(a) - p.y * sin(a);
	ret.y = p.x * sin(a) + p.y * cos(a);
	return ret;
}

double intersect(POINT &a, POINT &b) {
	double d = dis(a, b), ang, ans = 0;
	POINT p1, p2;
	if (d >= sqr(a.r + b.r))
		return 0;
	if (d <= sqr(a.r - b.r))
		return 1e50;
	d = sqrt(d);
	ang = (sqr(a.r) + sqr(d) - sqr(b.r)) / 2 / d / a.r;
	ang = acos(ang);
	POINT v = POINT(b.x - a.x, b.y - a.y);
	v.unit();
	v = v * a.r;
	p1 = rotate(v, ang), p2 = rotate(v, -ang);
	p1 = a + p1, p2 = a + p2;
	if (2 * ang < PI)
		ans += a.r * a.r * ang - fabs(cross(a, p1, p2)) / 2.0;
	else
		ans += a.r * a.r * ang + fabs(cross(a, p1, p2)) / 2.0;
	ang = (sqr(b.r) + sqr(d) - sqr(a.r)) / 2 / d / b.r;
	ang = acos(ang);
	if (2 * ang < PI)
		ans += b.r * b.r * ang - fabs(cross(b, p1, p2)) / 2.0;
	else
		ans += b.r * b.r * ang + fabs(cross(b, p1, p2)) / 2.0;
	return ans;
}

POINT c[N];
int n;
int main() {
	int T, i, j;

	scanf("%d", &T);
	while (T--) {
		double ans = 1e50;
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			c[i].get();
		if (n == 1) {
			printf("%.4lf\n", c[0].r / sqrt(2.0));
			continue;
		}
		for (i = 0; i < n; i++) {
			double l, r, mid;
			POINT tc(c[i].x, c[i].y);
			l = 0, r = 1e20;
			while (r - l > 1e-9) {
				int ok = 1;
				mid = (l + r) / 2.0;
				tc.r = mid;
				for (j = 0; j < n && ok; j++) {
					if (i == j)
						continue;
					if (intersect(tc, c[j]) < c[j].a2)
						ok = 0;
				}
				if (ok)
					r = mid;
				else
					l = mid;
			}
			if (mid < ans)
				ans = mid;
		}
		printf("%.4lf\n", ans);
	}
	return 0;
}
