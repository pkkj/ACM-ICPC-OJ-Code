// 2007 Dhaka: Photographic Tour
// ACM-ICPC Live Archive 4061
#include <cstdio>
#include <cstring>
#define N 105
bool dp1[N][N], dp2[N][N];
 
struct EDGE {
	int b, next, w;
};
 
EDGE E[N * N * 2];
int G[N], tot, tic[N], n, m;
void addedge(int a, int b, int w) {
	EDGE e = { b, G[a], w };
	G[a] = tot;
	E[tot++] = e;
}
int solve() {
	int i, j, k, a, b, w, ans = 0;
	memset(G, -1, sizeof(G));
	memset(dp1, 0, sizeof(dp1));
	memset(dp2, 0, sizeof(dp2));
	tot = 0;
	while (m--) {
		scanf("%d%d%d", &a, &b, &w);
		addedge(a, b, w);
		addedge(b, a, w);
	}
	scanf("%d", &m);
	for (i = 0; i < m; i++)
		scanf("%d", &tic[i]);
	dp1[0][0] = 1;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (dp1[i][j]) {
				for (k = G[j]; ~k; k = E[k].next)
					if (E[k].w == tic[i]) dp1[i + 1][E[k].b] = 1;
			}
	dp2[m][n - 1] = 1;
	for (i = m; i >= 1; i--)
		for (j = 0; j < n; j++)
			if (dp2[i][j]) {
				for (k = G[j]; ~k; k = E[k].next)
					if (E[k].w == tic[i - 1]) dp2[i - 1][E[k].b] = 1;
			}
	for (j = 0; j < n; j++)
		for (i = 0; i <= m; i++)
			if (dp1[i][j] && dp2[i][j]) {
				ans++;
				break;
			}
	return ans;
}
int main() {
	int ca = 1;
	while (scanf("%d%d", &n, &m) && n)
		printf("Tour %d: %d\n", ca++, solve());
	return 0;
}