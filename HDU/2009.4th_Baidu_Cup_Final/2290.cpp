// HDU 2290
// The 4th Baidu Cup Final: Find the Path
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 205
#define INF 1<<30
 
int G[N][N], dp[N][N][N];
int po[N], idx[N];
bool cmp(int a, int b) {
	return po[a] < po[b];
}
void solve() {
	int n, m, i, j, k, a, b, Q, w;
	scanf("%d%d", &n, &m);
	for (i = 0; i < n; i++)
		scanf("%d", &po[i]);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			G[i][j] = INF;
	while (m--) {
		scanf("%d%d%d", &a, &b, &w);
		G[a][b] = G[b][a] = w;
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			dp[0][i][j] = G[i][j];
	for (i = 0; i < n; i++)
		idx[i] = i;
	sort(idx, idx + n, cmp);
	for (k = 0; k < n; k++) {
		int v = idx[k];
		memcpy(dp[k + 1], dp[k], sizeof(dp[k]));
		for (i = 0; i < n; i++)
			if (dp[k][i][v] != INF) for (j = 0; j < n; j++)
				if (dp[k][v][j] != INF) {
					dp[k + 1][i][j] = min(dp[k][i][v] + dp[k][v][j], dp[k + 1][i][j]);
				}
	}
	sort(po, po + n);
	scanf("%d", &Q);
	while (Q--) {
		scanf("%d%d%d", &a, &b, &w);
		k = upper_bound(po, po + n, w) - po;
		int ans = min(G[a][b], dp[k][a][b]);
		if (ans == INF) ans = -1;
		printf("%d\n", ans);
	}
	printf("\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
