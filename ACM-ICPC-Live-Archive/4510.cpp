// CII 4510 
// 2009 Southwestern Europe: Slalom
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 1005
#define INF 1e30
struct LINE {
	double y, x1, x2;
	void get() {
		scanf("%lf%lf%lf", &y, &x1, &x2);
	}
};
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
struct EDGE {
	int b, next;
	double w;
};
LINE li[N];
bool see[N * 2];
int G[N * 2], tot, n;
EDGE E[N * N * 2];
void addedge(int a, int b, double w) {
	EDGE e = { b, G[a], w };
	E[tot] = e;
	G[a] = tot++;
}
double sqr(double x) {
	return x * x;
}
double dis(POINT a, POINT b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
void getvis(POINT p, int id) {
	int i, st = 1;
	double k1, k2;
	for (id == 2 * n ? i = 0 : i = id / 2 + 1; i < n; i++) {
		if (st) {
			st = 0;
			k1 = (p.x - li[i].x1) / (p.y - li[i].y);
			k2 = (p.x - li[i].x2) / (p.y - li[i].y);
			addedge(id, i * 2, dis(p, POINT(li[i].x1, li[i].y)));
			addedge(id, i * 2 + 1, dis(p, POINT(li[i].x2, li[i].y)));
			if (i == n - 1 && p.x >= li[i].x1 && p.x <= li[i].x2) see[id] = 1;
		} else {
			double x1, x2, b;
			// Line 1
			b = p.x - k1 * p.y;
			x1 = k1 * li[i].y + b;
			// Line 2
			b = p.x - k2 * p.y;
			x2 = k2 * li[i].y + b;
			if (x2 <= li[i].x1 || x1 >= li[i].x2) break;
			if (li[i].x1 >= x1 && li[i].x1 <= x2) addedge(id, i * 2, dis(p, POINT(li[i].x1, li[i].y)));
			if (li[i].x2 >= x1 && li[i].x2 <= x2) addedge(id, i * 2 + 1, dis(p, POINT(li[i].x2, li[i].y)));
			x1 = max(x1, li[i].x1);
			x2 = min(x2, li[i].x2);
			k1 = (p.x - x1) / (p.y - li[i].y);
			k2 = (p.x - x2) / (p.y - li[i].y);
			if (i == n - 1 && p.x >= x1 && p.x <= x2) see[id] = 1;
		}
	}
}
double dp[N * 2];
double solve() {
	int i, j;
	double ans = INF;
	POINT st;
	st.get();
	for (i = 0; i < n; i++)
		li[i].get();
	memset(see, 0, sizeof(see));
	memset(G, -1, sizeof(G));
	tot = 0;
	getvis(st, n * 2);
	if (see[n * 2]) return st.y - li[n - 1].y;
	for (i = 0; i < n; i++) {
		getvis(POINT(li[i].x1, li[i].y), i * 2);
		getvis(POINT(li[i].x2, li[i].y), i * 2 + 1);
	}
	for (i = 0; i < 2 * n; i++)
		dp[i] = INF;
	for (i = G[2 * n]; ~i; i = E[i].next)
		dp[E[i].b] = min(dp[E[i].b], E[i].w);
 
	for (i = 0; i < 2 * n; i++) {
		if (see[i]) ans = min(ans, dp[i] + li[i / 2].y - li[n - 1].y);
		for (j = G[i]; ~j; j = E[j].next)
			dp[E[j].b] = min(dp[E[j].b], dp[i] + E[j].w);
	}
	ans = min(ans, dp[(n - 1) * 2]);
	ans = min(ans, dp[(n - 1) * 2 + 1]);
	return ans;
}
int main() {
	while (scanf("%d", &n) && n)
		printf("%.9lf\n", solve());
	return 0;
}
