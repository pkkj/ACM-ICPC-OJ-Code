// 2008 Kuala Lumpur: Gun Fight
// ACM-ICPC Live Archive 4407
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 305
struct POINT {
	int x, y, h;
	void get() {
		scanf("%d%d%d", &x, &y, &h);
	}
	void print() {
		printf("[%d %d %d] ", x, y, h);
	}
};
int cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int n;
POINT pl[N], p1[N], p2[N];
bool g[N][N], v[N];
int link[N], nl, nr;
int dis(POINT &a, POINT &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
int dfs(int t) {
	int i;
	for (i = 1; i <= nr; i++) {
		if (!v[i] && g[t][i]) {
			v[i] = 1;
			if (link[i] == -1 || dfs(link[i])) {
				link[i] = t;
				return 1;
			}
		}
	}
	return 0;
}
int solve() {
	int i, j, c1, c2, a, b, R, ans = 0;
	POINT *g1, *g2;
	c1 = 0, c2 = 0;
	for (i = 1; i <= n; i++)
		pl[i].get();
	scanf("%d%d%d", &a, &b, &R);
	R *= R;
	for (i = 1; i <= n; i++) {
		if (!pl[i].h) continue;
		if (cross(pl[a], pl[i], pl[b]) > 0) p1[++c1] = pl[i];
		else p2[++c2] = pl[i];
	}
 
	g1 = p1, g2 = p2;
	if (c1 > c2) swap(c1, c2), swap(g1, g2);
	memset(g, 0, sizeof(g));
	memset(link, -1, sizeof(link));
	for (i = 1; i <= c1; i++) {
		for (j = 1; j <= c2; j++) {
			if (g1[i].h <= g2[j].h) continue;
			if (dis(g1[i], g2[j]) <= R) {
				g[i][j] = 1;
			}
		}
	}
	nl = c1, nr = c2;
	for (i = 1; i <= nl; i++) {
		memset(v, 0, sizeof(v));
		ans += dfs(i);
	}
	return ans;
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n)
		printf("Case %d: %d\n", ca++, solve());
}