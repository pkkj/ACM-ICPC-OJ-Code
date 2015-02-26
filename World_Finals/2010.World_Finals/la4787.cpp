// 2010 World Finals: Tracking Bio-bots
// ACM-ICPC Live Archive 4787 

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 2005
struct WALL {
	int x1, x2, y;
};
WALL wall[N];
int n, m, w;
int X[N], Y[N];
bool map[N][N], vis[N][N];
 
long long solve() {
	int i, j, xcnt = 0, ycnt = 0;
	long long ans = 0;
	for (i = 0; i < w; i++) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		X[xcnt++] = a, X[xcnt++] = c + 1, Y[ycnt++] = b, Y[ycnt++] = b + 1;
		wall[i].x1 = a, wall[i].x2 = c + 1, wall[i].y = b;
	}
	X[xcnt++] = m, Y[ycnt++] = n;
	X[xcnt++] = 0, Y[ycnt++] = 0;
	sort(X, X + xcnt);
	sort(Y, Y + ycnt);
	xcnt = unique(X, X + xcnt) - X;
	ycnt = unique(Y, Y + ycnt) - Y;
	memset(map, 0, sizeof(map));
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < w; i++) {
		int x1, x2, y;
		x1 = lower_bound(X, X + xcnt, wall[i].x1) - X;
		x2 = lower_bound(X, X + xcnt, wall[i].x2) - X;
		y = lower_bound(Y, Y + ycnt, wall[i].y) - Y;
		for (j = x1; j < x2; j++)
			map[y][j] = 1;
	}
	n = ycnt - 1, m = xcnt - 1;
	if (!map[n - 1][m - 1])
		vis[n - 1][m - 1] = 1;
	for (i = n - 1; i >= 0; i--) {
		for (j = m - 1; j >= 0; j--) {
			if ((i == n - 1 && j == m - 1) || map[i][j])
				continue;
			if (vis[i + 1][j] || vis[i][j + 1])
				vis[i][j] = 1;
		}
	}
	for (i = n - 1; i >= 0; i--)
		for (j = 0; j < m; j++)
			if (vis[i][j] == 0 && map[i][j] == 0)
				ans += (long long)(Y[i + 1] - Y[i]) * (X[j + 1] - X[j]);
	return ans;
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d", &n, &m, &w) && n)
		printf("Case %d: %lld\n", ca++, solve());
	return 0;
}
