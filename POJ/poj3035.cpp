// POJ 3035
// Nordic 2006: Random Walk
#include <cstdio>
#include <cstring>
#define N 1<<11
 
struct EDGE {
	int b, next;
};
EDGE E[5000];
double dp[105][N];
int G[N], tot, deg[N];
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
int main() {
	int K, n, m;
	while (scanf("%d%d%d", &K, &n, &m) && K) {
		int i, j, k, cnt;
		bool ok = 1;
		cnt = (1 << n);
		memset(deg, 0, sizeof(deg));
		memset(G, -1, sizeof(G));
		tot = 0;
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			addedge(a, b);
			addedge(b, a);
			deg[a]++, deg[b]++;
		}
		memset(dp, 0, sizeof(dp));
		for (i = 0; i < cnt; i++) {
			dp[0][i] = 100.0 / cnt;
		}
		for (k = 1; k < K && ok; k++) {
			for (i = 0; i < cnt; i++) {
				dp[k][i] = 0;
				for (j = G[i]; ~j; j = E[j].next) {
					dp[k][i] += dp[k - 1][E[j].b] / deg[E[j].b];
				}
			}
			for (i = 0; i < n; i++) {
				double p = 0;
				for (j = 0; j < cnt; j++)
					if ((1 << i) & j) p += dp[k][j];
				if (p <= 25 || p >= 75) ok = 0;
			}
		}
		puts(ok ? "Yes" : "No");
	}
	return 0;
}
