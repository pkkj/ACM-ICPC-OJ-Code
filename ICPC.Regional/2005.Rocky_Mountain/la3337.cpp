// Rocky Mountain 2005: Random Walk
// ACM-ICPC Live Archive 3337
// POJ 2714

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 205
int n;
 
struct POINT {
	double x, y, a;
	double len2() {
		return x * x + y * y;
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	bool operator<(const POINT &p) const {
		return a < p.a;
	}
	POINT operator +(const POINT &p) {
		POINT ret;
		ret.x = x + p.x, ret.y = y + p.y;
		return ret;
	}
};
 
POINT pl[N];
double solve() {
	double ans = 0, t;
	int i, j;
	for (i = 0; i < 2 * n;) {
		pl[i].get();
		pl[i].a = atan2(pl[i].y, pl[i].x);
		i++;
		pl[i].x = -pl[i - 1].x, pl[i].y = -pl[i - 1].y;
		pl[i].a = atan2(pl[i].y, pl[i].x);
		i++;
	}
	sort(pl, pl + 2 * n);
	for (i = 0; i < 2 * n; i++) {
		POINT v;
		v.x = v.y = 0;
		for (j = 0; j < n; j++) {
			v = v + pl[(i + j) % (2 * n)];
		}
		t = v.len2();
		ans = t > ans ? t : ans;
	}
	return sqrt(ans);
}
int main() {
	while (scanf("%d", &n) && n)
		printf("Maximum distance = %.3lf meters.\n", solve());
}