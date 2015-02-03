// 2007 Beijing: Bricks
// ACM-ICPC Live Archive 4024
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 20
struct POINT {
	int x, y;
	void print() {
		printf("%d %d ", x, y);
	}
	POINT() {
	}
	POINT(int x, int y) :
		x(x), y(y) {
	}
};
struct REC {
	POINT a, b;
	REC() {
	}
	REC(int x1, int y1, int x2, int y2) :
		a(x1, y1), b(x2, y2) {
	}
 
};
int reccross(REC &r1, REC &r2) {
	if (r1.a.x >= r2.b.x || r1.b.x <= r2.a.x) return 0;
	if (r1.a.y >= r2.b.y || r1.b.y <= r2.a.y) return 0;
	int x[4], y[4];
	x[0] = r1.a.x, x[1] = r1.b.x, x[2] = r2.a.x, x[3] = r2.b.x;
	y[0] = r1.a.y, y[1] = r1.b.y, y[2] = r2.a.y, y[3] = r2.b.y;
	sort(x, x + 4);
	sort(y, y + 4);
	return (x[2] - x[1]) * (y[2] - y[1]);
}
REC low[N], top[N][4];
int m, n;
bool nofall(int st) {
	int support, i, j, k;
	for (i = 0; i < m; i++) {
		for (j = 0; j < 4; j++) {
			support = 0;
			for (k = 0; k < n; k++) {
				if ((1 << k) & st) continue;
				support += reccross(top[i][j], low[k]);
			}
			if (!support) return 0;
		}
	}
	return 1;
}
bool G[N][4][N];
bool findorder(int st, int cnt) {
	bool remove[N] = { 0 };
	int i, j, k, so = 0;
	while (so < cnt) {
		int found = 0;
		for (i = 0; i < n; i++) {
			if ((1 << i) & st) {
				if (remove[i]) continue;
				for (j = 0; j < 4; j++) {
					int ok = 1;
					for (k = 0; k < n && ok; k++) {
						if (G[i][j][k] && !remove[k]) ok = 0;
					}
					if (ok) {
						found = 1;
						remove[i] = 1;
						break;
					}
				}
				if (remove[i]) so++;
			}
		}
		if (!found) break;
	}
	return so == cnt;
}
void getG() {
	int i, j;
	memset(G, 0, sizeof(G));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) continue;
			if (!(low[i].b.x <= low[j].a.x || low[i].a.x >= low[j].b.x)) {
				if (low[i].b.y <= low[j].a.y) G[i][0][j] = 1;
				if (low[i].a.y >= low[j].b.y) G[i][1][j] = 1;
			}
			if (!(low[i].b.y <= low[j].a.y || low[i].a.y >= low[j].b.y)) {
				if (low[i].b.x <= low[j].a.x) G[i][2][j] = 1;
				if (low[i].a.x >= low[j].b.x) G[i][3][j] = 1;
			}
		}
	}
}
void solve() {
	int i, j, st, tot, ans = 0;
	scanf("%d\n", &m);
	for (i = 0; i < n; i++)
		scanf("(%d,%d)-(%d,%d) ", &low[i].a.x, &low[i].a.y, &low[i].b.x, &low[i].b.y);
	for (i = 0; i < m; i++) {
		int x1, y1, x2, y2;
		scanf("(%d,%d)-(%d,%d) ", &x1, &y1, &x2, &y2);
		int mx1, mx2, my1, my2;
		double mx = (double) (x1 + x2) / 2.0;
		double my = (double) (y1 + y2) / 2.0;
		mx1 = mx2 = (int) floor(mx);
		my1 = my2 = (int) floor(my);
		if ((x2 - x1) % 2) mx1++;
		if ((y2 - y1) % 2) my1++;
		top[i][0] = REC(x1, y1, x2, my1);
		top[i][1] = REC(x1, my2, x2, y2);
		top[i][2] = REC(x1, y1, mx1, y2);
		top[i][3] = REC(mx2, y1, x2, y2);
	}
	getG();
	tot = (1 << n);
	for (st = 1; st < tot; st++) {
		int cnt = 0;
		j = st;
		while (j) {
			if (j & 1) cnt++;
			j >>= 1;
		}
		if (cnt <= ans) continue;
		if (!nofall(st)) continue;
		if (!findorder(st, cnt)) continue;
		ans = cnt;
	}
	printf("%d\n", ans);
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", T++);
		solve();
	}
	return 0;
}