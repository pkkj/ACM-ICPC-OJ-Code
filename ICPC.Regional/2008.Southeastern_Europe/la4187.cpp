// 2008 Southeastern Europe: Build Your Home
// ACM-ICPC Live Archive 4187

#include <cstdio>
#include <cstring>
#include <cmath>
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
#define NP 20
struct POLY {
	int n;
	POINT data[NP];
};
POLY pl;
double poly_area(POLY &p) {
	double s = p.data[0].y * (p.data[p.n - 1].x - p.data[1].x);
	for (int i = 1; i < p.n; i++)
		s += p.data[i].y * (p.data[i - 1].x - p.data[(i + 1) % p.n].x);
	return s / 2;
}
int main() {
	int n, i, ans;
	while (scanf("%d", &n) && n) {
		pl.n = n;
		for (i = 0; i < n; i++)
			pl.data[i].get();
		if (n <= 2) {
			printf("0\n");
			continue;
		}
		double a = fabs(poly_area(pl));
		ans = (int) (a + 0.5);
		printf("%d\n", ans);
	}
	return 0;
}