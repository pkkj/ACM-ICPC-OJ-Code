// 2008 Harbin Preliminary: Turn the corner
// HDU 2438

#include <cmath>
#include <cstdio>
#define PI 3.14159265358
#define EPS 0.0005
double X, Y, D, L;

double f(double x) {
	return -(cos(x) / sin(x) * X - L * cos(x) - D / sin(x));
}

double solve() {
	double l, r, m, mm;
	l = 0.00001, r = PI / 2;
	while (l + EPS < r) {
		m = (l + r) / 2;
		mm = (m + r) / 2;
		if (f(m) >= f(mm)) r = mm;
		else l = m;
	}
	return f(m);
}

int main() {
	while (~scanf("%lf%lf%lf%lf", &X, &Y, &L, &D)) {
		int ok = 1;
		if (D > X || D > Y) ok = 0;
		if (ok) if (solve() > Y) ok = 0;
		puts(ok ? "yes" : "no");
	}
	return 0;
}
