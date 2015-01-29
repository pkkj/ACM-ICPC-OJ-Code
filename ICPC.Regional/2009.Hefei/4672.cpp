// CII 4672
// 2009 Hefei: New Game
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define M 10005
#define MOD 1000000007
struct EDGE {
	int y, next;
};
int tot, G[N], sg[N], dp[N][N][N], c[M / 2 + N][N];
EDGE E[M];
void addedge(int x, int y) {
	EDGE e = { y, G[x] };
	E[tot] = e;
	G[x] = tot++;
}
 
void init() {
	c[0][0] = 1;
	for (int i = 1; i < M / 2 + N; i++) {
		c[i][0] = 1;
		for (int j = 1; j < N && j <= i; j++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
	}
}
void dfs(int x) {
	if (sg[x] != -1) return;
	int has[N] = { 0 };
	for (int j = G[x]; ~j; j = E[j].next) {
		dfs(E[j].y);
		has[sg[E[j].y]] = 1;
	}
	for (int i = 0; i < N; i++)
		if (!has[i]) {
			sg[x] = i;
			return;
		}
}
 
void solve() {
	int n, m, s, i, j, k;
	tot = 0;
	memset(G, -1, sizeof(G));
	scanf("%d%d%d", &n, &m, &s);
	while (m--) {
		scanf("%d%d", &i, &j);
		addedge(++i, ++j);
	}
	memset(sg, -1, sizeof(sg));
	for (int i = 1; i <= n; i++)
		dfs(i);
	memset(dp, 0, sizeof(dp));
	dp[1][0][0] = dp[1][1][sg[1]] = 1;
	for (i = 1; i < n; i++)
		for (j = 0; j <= i; j++)
			for (k = 0; k <= n; k++) {
				dp[i][j][k] %= MOD;
				dp[i + 1][j][k] += dp[i][j][k];
				dp[i + 1][j + 1][k ^ sg[i + 1]] += dp[i][j][k];
			}
	long long ans = 0;
	for (int i = 0; i <= s && i <= n; i++)
		if ((s - i) % 2 == 0) ans = (ans + (long long) dp[n][i][0] * c[n + (s - i) / 2 - 1][n - 1]) % MOD;
 
	printf("%lld\n", ans);
}
int main() {
	int T;
	init();
	scanf("%d", &T);
	while (T--)
		solve();
}
