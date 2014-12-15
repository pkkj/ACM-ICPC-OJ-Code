// SGU 110 Dungeon
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 60
#define EPS 1e-11
#define INF 1e50
int sgn(double x) {
	return x < -EPS ? -1 : (x > EPS);
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
double sqr(double x) {
	return x * x;
}
struct VECTOR {
	double x, y, z;
	VECTOR() {
	}
	VECTOR(double x, double y, double z) :
		x(x), y(y), z(z) {
	}
	VECTOR operator +(VECTOR v) {
		return VECTOR(x + v.x, y + v.y, z + v.z);
	}
	VECTOR operator -(VECTOR v) {
		return VECTOR(x - v.x, y - v.y, z - v.z);
	}
	VECTOR operator *(double v) {
		return VECTOR(x * v, y * v, z * v);
	}
	VECTOR operator /(double v) {
		return VECTOR(x / v, y / v, z / v);
	}
	double operator *(VECTOR v) {
		return x * v.x + y * v.y + z * v.z;
	}
	double abs2() {
		return (x * x + y * y + z * z);
	}
	double abs() {
		return sqrt(abs2());
	}
	void get() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void show() {
		printf("(%lf %lf %lf)\n", x, y, z);
	}
	void single() {
		double mo = abs();
		x /= mo, y /= mo, z /= mo;
	}
};
 
typedef VECTOR POINT;
struct LINE {
	POINT p, v;
};
struct BALL {
	POINT p;
	double r;
};
BALL bl[N];
 
double intersect(LINE &l, BALL &ba) {
	VECTOR aa = l.p - ba.p;
	double a, b, c, x1, x2;
	int ret;
	a = l.v.abs2();
	b = aa * l.v * 2;
	c = aa.abs2() - sqr(ba.r);
	ret = solve_two_eq(a, b, c, x1, x2);
	if (ret < 0) return INF;
	return min(x1, x2);
}
int n;
int once(LINE &ll) {
	double best = INF;
	VECTOR v1, nn;
	POINT itp;
	int bid = -1, i;
	for (i = 0; i < n; i++) {
		double t = intersect(ll, bl[i]);
		if (sgn(t) <= 0) continue;
		if (t < best) best = t, bid = i;
	}
	if (bid == -1) return -1;
	itp = ll.v * best + ll.p;
	ll.p = itp;
	ll.v = ll.v * (-1);
	v1 = ll.v;
	v1.single();
	nn = itp - bl[bid].p;
	nn.single();
	ll.v = nn * (2.0 * (v1 * nn)) - v1;
	return bid;
}
int main() {
	LINE st;
	POINT sp, sv;
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%lf%lf%lf%lf", &bl[i].p.x, &bl[i].p.y, &bl[i].p.z, &bl[i].r);
	sp.get();
	sv.get();
	st.p = sp;
	st.v = VECTOR(sv.x - sp.x, sv.y - sp.y, sv.z - sp.z);
	for (i = 0; i < 10; i++) {
		int ret = once(st);
		if (ret == -1) return 0;
		else printf("%d ", ret + 1);
	}
	if(once(st) != -1)printf("etc.\n");
	return 0;
}
