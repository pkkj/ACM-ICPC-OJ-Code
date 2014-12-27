// CII 5138
// 2011 World Finals: Trash Removal
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 105
#define PRECISION  1e-10

struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};

POINT pl[N], ch[N];
int n;

double sqr(double x) {
	return x * x;
}
int cmpzero(double d) {
	return (fabs(d) < PRECISION) ? 0 : (d > 0 ? 1 : -1);
}

double dis(const POINT &a, const POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
bool cmp_angle(const POINT &p1, const POINT &p2) {
	return cross(pl[0], p1, p2) > 0;
}
inline bool farer(const POINT &p1, const POINT &p2) {
	return dis(p1, pl[0]) > dis(p2, pl[0]);
}
int remove_point() {
	int idx = 1;
	for (int i = 2; i < n; ++i) {
		if (cmpzero(cross(pl[0], pl[i], pl[idx])))
			pl[++idx] = pl[i];
		else if (farer(pl[i], pl[idx]))
			pl[idx] = pl[i];
	}
	return idx + 1;
}
double point_to_line(POINT &p, POINT &a, POINT &b) {
	return fabs((double) cross(a, b, p)) / dis(a, b);
}
int graham_scan() {
	int top;
	for (int i = 1; i < n; i++)
		if (pl[i].y < pl[0].y || (pl[i].y == pl[0].y && pl[i].x < pl[0].x))
			swap(pl[i], pl[0]);
	sort(pl + 1, pl + n, cmp_angle);
	n = remove_point();

	ch[0] = pl[0];
	ch[1] = pl[1];
	ch[2] = pl[2];
	top = 2;
	for (int i = 3; i < n; ++i) {
		while (!(cross(ch[top - 1], pl[i], ch[top]) < 0))
			--top;
		ch[++top] = pl[i];
	}
	return ++top;
}

double solve() {
	int i, j, top;
	double ans = 1e50;
	for (i = 0; i < n; i++)
		pl[i].get();
	top = graham_scan();
	ch[top] = ch[0];
	for (i = 0; i < top; i++) {
		double maxdis = 0.0;
		for (j = 0; j < top; j++) {
			maxdis = max(maxdis, point_to_line(ch[j], ch[i], ch[i+1]));
		}
		ans = min(ans, maxdis);
	}
	ans += 0.005;
	return ans;

}

int main() {
	int ca = 1;
	while (scanf("%d", &n) && n)
		printf("Case %d: %.2lf\n", ca++, solve());
	return 0;
}

