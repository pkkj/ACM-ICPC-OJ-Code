// 2007 Dhaka: You are around me ...
// ACM-ICPC Live Archive 4062
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 15010
#define PI 3.14159265358979323846
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	bool operator <(const POINT &p) const {
		return x < p.x;
	}
 
};
double sqr(double x) {
	return x * x;
}
double dist(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
POINT rotate(const POINT &p, double a) {
	POINT ret;
	ret.x = p.x * cos(a) - p.y * sin(a);
	ret.y = p.x * sin(a) + p.y * cos(a);
	return ret;
}
int n;
double e, w;
POINT pl[N];
int idx[N];
bool cmpy(int x, int y) {
	return pl[x].y < pl[y].y;
}
double divide(int a, int b) {
	if (b - a == 1) return dist(pl[a], pl[b]);
	else if (b - a == 2) return min(dist(pl[a], pl[a + 2]), min(dist(pl[a], pl[a + 1]), dist(pl[a + 1], pl[a + 2])));
	int mid = (a + b) >> 1, ysz = 0, i, j;
	double ret = min(divide(a, mid), divide(mid + 1, b));
	for (i = mid; pl[mid].x - pl[i].x < ret && i >= a; i--)
		idx[ysz++] = i;
	for (i = mid + 1; pl[i].x - pl[mid + 1].x < ret && i <= b; i++)
		idx[ysz++] = i;
	sort(idx, idx + ysz, cmpy);
	for (i = 0; i < ysz; i++)
		for (j = i + 1; j < ysz && j < i + 7; j++)
			ret = min(ret, dist(pl[idx[j]], pl[idx[i]]));
	return ret;
}
 
double solve() {
	int i;
	double d ,EE = sqrt(1 - e * e);
	for (i = 1; i <= n; i++) {
		pl[i].get();
		pl[i] = rotate(pl[i], -w / 180.0 * PI);
		pl[i].x *= EE;
	}
	sort(pl + 1, pl + n + 1);
	d = divide(1, n) / 2.0;
	return d * (d / EE) * PI;
}
int main() {
	int ca = 1;
	while (scanf("%d%lf%lf", &n, &e, &w) && n)
		printf("Case %d:\n%lf\n", ca++, solve());
	return 0;
}