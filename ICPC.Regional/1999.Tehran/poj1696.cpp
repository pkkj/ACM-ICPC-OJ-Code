// 1999 Tehran: Space Ant
// POJ 1696

#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#define PRECISION  1e-8
#define NP 100

struct POINT {
	double x, y;
	int id;
};

int cmpzero(double d) {
	return (fabs(d) < PRECISION) ? 0 : (d > 0 ? 1 : -1);
}

double sqr(double x) {
	return x * x;
}

double dotdet(double x1, double y1, double x2, double y2) {
	return x1 * x2 + y1 * y2;
}

double cross_det(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

double dotdet(const POINT &a1, const POINT &a2, const POINT &b1, const POINT &b2) {
	return dotdet(a2.x - a1.x, a2.y - a1.y, b2.x - b1.x, b2.y - b1.y);
}

double cross_det(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

POINT plist[NP], start_point;

double pt_distance(const POINT &p1, const POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

int cmp(const POINT &a, const POINT &b) {
	int t = cross_det(plist[0], a, b);
	if (t)
		return t > 0;
	return pt_distance(a, plist[0]) > pt_distance(b, plist[0]);
}

void scan(int n) {
	int i, j, used[NP] = { 1, 1, 0 }, next;
	POINT p0, p1;
	for (i = 1; i < n; i++)
		if (plist[i].y < plist[0].y || (plist[i].y == plist[0].y && plist[i].x < plist[0].x))
			swap(plist[i], plist[0]);
	for (i = 2; i < n; i++) {
		if (!cmp(plist[1], plist[i]))
			swap(plist[1], plist[i]);
	}
	printf("%d ", n);
	printf("%d %d ", plist[0].id, plist[1].id);
	p0 = plist[0], p1 = plist[1];
	for (i = 2; i < n; i++) {
		double tmp = 181, alpha;
		for (j = 2; j < n; j++) {
			if (!used[j] && (alpha = acos(dotdet(p0, p1, p1, plist[j]) / pt_distance(p0, p1) / pt_distance(p1, plist[j]))) <= tmp) {
				tmp = alpha;
				next = j;
			}
		}
		used[next] = 1;
		printf("%d ", plist[next].id);
		p0 = p1;
		p1 = plist[next];
	}
	printf("\n");
}

int main() {
	int i, n, T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d%lf%lf", &plist[i].id, &plist[i].x, &plist[i].y);
		scan(n);
	}
	return 0;
}
