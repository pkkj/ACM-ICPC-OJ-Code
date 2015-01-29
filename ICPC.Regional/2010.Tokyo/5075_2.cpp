// CII 5075: solution 2
// 2010 Tokyo: Intersection of Two Prisms
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 300
#define PLUS 100
#define INF 1e10
struct POINT {
	int a, b;
};
 
int n1, n2;
double xmin1[N], xmax1[N], xmin2[N], xmax2[N], gapy[N], gapz[N];
POINT p1[N], p2[N];
void calcx(int n, POINT *p, double *xmin, double *xmax) {
	for (int i = 0; i < n; i++) {
		POINT u1 = p[i], u2 = p[i + 1];
		if (u1.a > u2.a) swap(u1, u2);
		xmin[u1.a] = min(xmin[u1.a], (double) u1.b);
		xmax[u1.a] = max(xmax[u1.a], (double) u1.b);
 
		if (u1.a == u2.a) continue;
		double d = ((double) u1.b - u2.b) / ((double) u1.a - u2.a);
		double base = u1.b;
		for (int j = u1.a + 1; j <= u2.a; j++) {
			base += d;
			xmin[j] = min(xmin[j], base);
			xmax[j] = max(xmax[j], base);
		}
	}
}
double solve() {
	int i, min1 = N, max1 = -N, min2 = N, max2 = -N;
	for (i = 0; i < n1; i++) {
		scanf("%d%d", &p1[i].a, &p1[i].b);
		p1[i].a += PLUS;
		min1 = min(p1[i].a, min1);
		max1 = max(p1[i].a, max1);
	}
 
	for (i = 0; i < n2; i++) {
		scanf("%d%d", &p2[i].a, &p2[i].b);
		p2[i].a += PLUS;
		min2 = min(p2[i].a, min2);
		max2 = max(p2[i].a, max2);
	}
	for (i = 0; i < N; i++)
		xmin1[i] = xmin2[i] = INF, xmax1[i] = xmax2[i] = -INF;
 
	p1[n1] = p1[0], p2[n2] = p2[0];
 
	calcx(n1, p1, xmin1, xmax1);
	calcx(n2, p2, xmin2, xmax2);
 
	int beg = max(min1, min2), end = min(max1, max2);
	for (i = beg; i <= end; i++) {
		gapy[i] = xmax1[i] - xmin1[i];
		gapz[i] = xmax2[i] - xmin2[i];
	}
	double ans = 0;
 
	for (i = beg + 1; i <= end; i++)
		ans += gapy[i - 1] * gapz[i - 1] + (gapy[i - 1] + gapy[i]) * (gapz[i - 1] + gapz[i]) + gapy[i] * gapz[i];
	return ans / 6.0;
}
 
int main() {
	while (scanf("%d%d", &n1, &n2) && n1)
		printf("%.6lf\n", solve());
	return 0;
}
