// CII 4426
// 2008 Tehran: Blast the Enemy!
#include <cstdio>
#include <cmath>
#define EPS 1e-8
#define N 105
struct POINT {
	double x, y;
	POINT() {
		x = y = 0;
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("%.6lf %.6lf\n", x, y);
	}
	POINT operator+(const POINT &p) {
		return POINT(x + p.x, y + p.y);
	}
};
POINT pl[N];
int n;
double cross(POINT o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
void solve() {
	int i;
	double area = 0;
	POINT ct;
	for (i = 0; i < n; i++)
		pl[i].get();
	pl[i] = pl[0];
	for (i = 0; i < n; i++) {
		double s = cross(POINT(), pl[i], pl[i + 1]);
		POINT t;
		area += s;
		t = pl[i] + pl[i + 1];
		ct.x += s * t.x, ct.y += s * t.y;
	}
	ct.x = ct.x / area / 3.0, ct.y = ct.y / area / 3.0;
	ct.print();
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		printf("Stage #%d: ", T++);
		solve();
	}
	return 0;
}
