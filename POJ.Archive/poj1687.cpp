// 2000 Tehran: Buggy Sat
// ACM-ICPC Live Archive 2057
// POJ 1687
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define N 100

struct POINT {
	double x, y;
	POINT(double x, double y) :
			x(x), y(y) {
	}

	POINT() :
			x(0), y(0) {
	}
};

struct POLY {
	int n;
	double area;
	POINT data[2000];
};

double poly_area(POLY &p) {
	double s = p.data[0].y * (p.data[p.n - 1].x - p.data[1].x);
	for (int i = 1; i < p.n; i++)
		s += p.data[i].y * (p.data[i - 1].x - p.data[(i + 1) % p.n].x);
	p.area = s / 2;
	return s / 2;
}

POINT plist[N];

int main() {
	int T, n, i, j;
	scanf("%d", &T);
	while (T--) {
		POLY polygon;
		double maxarea = -1;
		int maxid;
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%lf%lf", &plist[i].x, &plist[i].y);
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d", &polygon.n);
			for (j = 0; j < polygon.n; j++) {
				int id;
				scanf("%d", &id);
				polygon.data[j] = plist[id - 1];
			}
			double ta = fabs(poly_area(polygon));

			if (ta > maxarea) {
				maxarea = ta;
				maxid = i;
			}
		}
		printf("%d\n", maxid + 1);
	}
	return 0;
}
