// 2009 Phuket: In-circles Again
// ACM-ICPC Live Archive 4714
#include <cstdio>
#include <cmath>
double sqr(double x) {
	return x * x;
}
double get(double R, double r) {
	double x, y;
	x = sqrt(sqr((R + r) / 2.0) - sqr((R - r) / 2.0));
	x *= 2;
	y = x * r / (R - r);
	return x + y;
}
int main() {
	double r1, r2, r3, R;
	int ca = 1;
	while (scanf("%lf%lf%lf%lf", &R, &r1, &r2, &r3) && R > 0) {
		double a = get(R, r1);
		double b = get(R, r2);
		double c = get(R, r3);
		double A = a + b, B = a + c, C = b + c;
		double p = a+b+c;
		double S = sqrt(p * (p - A) * (p - B) * (p - C));
		printf("Case %d: %.2lf\n", ca++, S);
	}
	return 0;
}