// 2006 Beijing: Guess
// ACM-ICPC Live Archive 3664
#include <cstdio>
#include <cstring>
#include <cmath>
#define N 20000
 
int n, rank[N];
double f[N][3];
#define EPS 1e-8
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
void solve() {
	int i, j, ok = 1;
	for (i = 1; i <= n; i++)
		for (j = 0; j < 3; j++)
			scanf("%lf", &f[i][j]);
	for (i = 1; i <= n; i++)
		scanf("%d", &rank[i]);
	double cur = f[rank[1]][0] + f[rank[1]][1] + f[rank[1]][2];
	for (i = 2; i <= n && ok; i++) {
		double a = f[rank[i]][0], b = f[rank[i]][1], c = f[rank[i]][2];
		if (rank[i] < rank[i - 1]) {
			double next = -1;
			if (sgn(a - cur) < 0 && a > next) next = a;
			if (sgn(b - cur) < 0 && b > next) next = b;
			if (sgn(c - cur) < 0 && c > next) next = c;
			if (sgn(a + b - cur) < 0 && a + b > next) next = a + b;
			if (sgn(b + c - cur) < 0 && b + c > next) next = b + c;
			if (sgn(a + c - cur) < 0 && a + c > next) next = a + c;
			if (sgn(a + b + c - cur) < 0 && a + b + c > next) next = a + b + c;
			if (sgn(cur) > 0 && sgn(next) < 0) next = 0;
			if (next == -1) ok = 0;
			cur = next;
		} else {
			double next = 0;
			if (sgn(a - cur) <= 0 && a > next) next = a;
			if (sgn(b - cur) <= 0 && b > next) next = b;
			if (sgn(c - cur) <= 0 && c > next) next = c;
			if (sgn(a + b - cur) <= 0 && a + b > next) next = a + b;
			if (sgn(b + c - cur) <= 0 && b + c > next) next = b + c;
			if (sgn(a + c - cur) <= 0 && a + c > next) next = a + c;
			if (sgn(a + b + c - cur) <= 0 && a + b + c > next) next = a + b + c;
			cur = next;
		}
	}
	if (ok) printf("%.2lf\n", cur);
	else printf("No solution\n");
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", T++);
		solve();
	}
	return 0;
}