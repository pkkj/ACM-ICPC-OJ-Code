// CII 4486
// 2009 Wuhan: Download Manager
#include <cstdio>
int main() {
	int n, T, ca = 1;
	double B, sum;
	while (scanf("%d%d%lf", &T, &n, &B) && T) {
		sum = 0;
		while (T--) {
			double a, p;
			scanf("%lf%lf", &a, &p);
			sum += a * (100 - p) / 100.0;
		}
		printf("Case %d: %.2lf\n\n", ca++, sum / B);
	}
}
