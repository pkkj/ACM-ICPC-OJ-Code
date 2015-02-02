// 2008 Hangzhou: Fire-Control System
// ACM-ICPC Live Archive 4356
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int n, k;
#define N 10005
#define PI 3.14159265358
struct POINT {
	double a;
	int r;
	bool operator<(const POINT &p) const {
		if (a != p.a) return a < p.a;
		return r < p.r;
	}
};
POINT pl[N];
void solve() {
	int i, rr, l, r;
	double ans = 1e50;
	for (i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		pl[i].r = x * x + y * y;
		pl[i].a = atan2((double) y, (double) x);
		pl[i + n] = pl[i];
		pl[i + n].a += PI + PI;
	}
	if (k <= 1) {
		printf("0.00\n");
		return;
	}
	sort(pl, pl + n + n);
	for (i = 0; i < n && ans; i++) {
		int c = 1;
		rr = pl[i].r;
		for (l = 0; pl[l].r > rr; l++)
			;
		for(r = l + 1;r < n + n;r++){
			if (pl[r].r <= rr) c++;
			if (c == k) break;
		}
		if (c != k) continue;
		while (1) {
			double tt = (pl[r].a - pl[l].a) * rr;
			if (tt < ans && r - l + 1 <= n) ans = tt;
			for (l++; pl[l].r > rr; l++)
				;
			for (r++; r < n + n && pl[r].r > rr; r++)
				;
			if (pl[r].r > rr || r == n + n) break;
		}
	}
	printf("%.2lf\n", ans / 2.0);
}
int main() {
	int T = 0;
	while (scanf("%d%d", &n, &k) && n) {
		printf("Case #%d: ", ++T);
		solve();
	}
	return 0;
}