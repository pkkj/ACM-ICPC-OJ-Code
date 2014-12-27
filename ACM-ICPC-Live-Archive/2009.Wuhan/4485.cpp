// CII 4485
// 2009 Wuhan: Crossing Rivers
#include <cstdio>
 
int main() {
	double d, len, l, v, p, ans = 0;
	int n, i, ca = 1;
	while (scanf("%d%lf", &n, &d) && d) {
		ans = 0, len = d;
		for (i = 0; i < n; i++) {
			scanf("%lf%lf%lf", &p, &l, &v);
			ans += l * 2 / v;
			len -= l;
		}
		ans += len;
		printf("Case %d: %.3lf\n\n", ca++, ans);
	}
	return 0;
}
