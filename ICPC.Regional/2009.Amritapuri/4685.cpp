// CII 4685
// 2009 Amritapuri: Succession
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define INF (1 << 30)
#define MOD 1000000007LL
struct EDGE {
	int y, next;
};
int dp[N][N], v[N], G[N], K, n, tot;
long long cnt[N][N];
EDGE E[N * 2];
void addedge(int x, int y) {
	EDGE e = { y, G[x] };
	E[tot] = e;
	G[x] = tot++;
}
void dfs(int x, int fa) {
	int i, j, k, l;
	for(i =0;i <= K;i++)
		dp[x][i] = -INF;
	dp[x][1] = v[x];
	cnt[x][1] = 1;
	for (j = G[x]; ~j; j = E[j].next) {
		i = E[j].y;
		if (i == fa) continue;
		dfs(i, x);
		for (k = K; k >= 2; k--) {
			for (l = 0; l < k; l++) {
				if (dp[i][l] == -INF || dp[x][k - l] == -INF) continue;
				if(dp[i][l] + dp[x][k - l] > dp[x][k])
				{
					dp[x][k] = dp[i][l] + dp[x][k - l];
					cnt[x][k] = cnt[i][l] * cnt[x][k-l]% MOD;
				}
				else if(dp[i][l] + dp[x][k-l] == dp[x][k])
					cnt[x][k] = (cnt[x][k] + cnt[i][l] * cnt[x][k-l]) % MOD;
			}
		}
	}
}
 
void solve() {
	int i, x, y, ans = -INF;
	long long anscnt = 0;
	tot = 0;
	scanf("%d%d%d", &n, &K, &x);
	memset(G, -1, sizeof(G));
	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < n; i++)
		scanf("%d", v + i);
	for (i = 0; i < n - 1; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	dfs(0, -1);
	for (i = 0; i < n; i++)
	{
		if(dp[i][K] > ans)
			ans = dp[i][K], anscnt = cnt[i][K];
		else if(dp[i][K] == ans)
			anscnt = (anscnt + cnt[i][K]) % MOD;
	}
	printf("%d %lld\n", ans, anscnt);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
