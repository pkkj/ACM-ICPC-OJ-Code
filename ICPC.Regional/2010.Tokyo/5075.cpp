// CII 5075
// 2010 Tokyo: Intersection of Two Prisms
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 300
#define INF 1e10
struct POINT {
	int a, b;
};
 
int n1, n2;
POINT p1[N], p2[N];
 
double find(POINT p[], int sz, int x) {
	double mmin = INF, mmax = -INF;
	for (int i = 0; i < sz; i++) {
		POINT p1 = p[i], p2 = p[i + 1];
		if (p1.a > p2.a) swap(p1, p2);
		if (x < p1.a || x > p2.a) continue;
		if (p1.a == p2.a) return fabs((double)p1.b - p2.b);
		if (p1.a <= x && x <= p2.a && p1.a != p2.a) {
			double f = ((double) x - p1.a) / ((double) p2.a - p1.a);
			double y = p1.b + f * (p2.b - p1.b);
			mmin = min(mmin, y);
			mmax = max(mmax, y);
		}
	}
	return mmax - mmin;
}
 
double solve() {
	int i, min1 = N, max1 = -N, min2 = N, max2 = -N;
	for (i = 0; i < n1; i++) {
		scanf("%d%d", &p1[i].a, &p1[i].b);
		min1 = min(p1[i].a, min1);
		max1 = max(p1[i].a, max1);
	}
 
	for (i = 0; i < n2; i++) {
		scanf("%d%d", &p2[i].a, &p2[i].b);
		min2 = min(p2[i].a, min2);
		max2 = max(p2[i].a, max2);
	}
	p1[n1] = p1[0], p2[n2] = p2[0];
 
	double ans = 0;
	double py = find(p1, n1, max(min1, min2)), pz = find(p2, n2, max(min1, min2));
	for (i = max(min1, min2) + 1; i <= min(max1, max2); i++) {
		double cy = find(p1, n1, i), cz = find(p2, n2, i);
		ans += cy * cz + (cy + py) * (cz + pz) + py * pz;
		py = cy, pz = cz;
	}
	return ans / 6.0;
}
 
int main() {
	while (scanf("%d%d", &n1, &n2) && n1)
		printf("%.6lf\n", solve());
	return 0;
}
