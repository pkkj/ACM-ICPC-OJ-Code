// 2008 Beijing: Minimal Ratio Tree
// ACM-ICPC Live Archive 4326
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 16
int g[N][N];
int cost[N], n, m, sol[N];
double best;
bool ok(int x) {
	int ans = 0;
	while (x) {
		ans += x & 1;
		x >>= 1;
	}
	return ans == m;
}
 
void prim(int x) {
	bool v[N] = { 0 };
	int dis[N], cursol[N], i, j, s;
	double se = 0, sp = 0, cur;
	for (s = 0; s < n; s++)
		if (x & (1 << s)) break;
	for (i = 0; i < n; i++)
		dis[i] = g[s][i];
	for (i = j = 0; i < n; i++)
		if (x & (1 << i)) sp += cost[i], cursol[j++] = i;
 
	v[s] = 1;
	while (1) {
		int mmin = 1 << 30, u = -1;
		for (i = 0; i < n; i++) {
			if ((x & (1 << i)) == 0) continue;
			if (!v[i] && dis[i] < mmin) u = i, mmin = dis[i];
		}
		if (u == -1) break;
		v[u] = 1, se += mmin;
		for (i = 0; i < n; i++)
			if (g[u][i] < dis[i] && !v[i]) dis[i] = g[u][i];
	}
	cur = se / sp;
	if (cur == best) {
		int ok = 0;
		for (i = 0; i < m && !ok; i++)
			if (sol[i] > cursol[i]) ok = 1;
		if (ok) for (i = 0; i < m; i++)
			sol[i] = cursol[i];
	} else if (cur < best) {
		best = cur;
		for (i = 0; i < m; i++)
			sol[i] = cursol[i];
	}
}
void solve() {
	int i, j, cnt;
	for (i = 0; i < n; i++)
		scanf("%d", cost + i);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &g[i][j]);
	cnt = 1 << n, best = 1e50, sol[0] = N;
	for (i = 0; i < cnt; i++)
		if (ok(i)) prim(i);
	for (i = 0; i < m - 1; i++)
		printf("%d ", sol[i] + 1);
	printf("%d\n", sol[i] + 1);
}
int main() {
	while (scanf("%d%d", &n, &m) && n)
		solve();
	return 0;
}