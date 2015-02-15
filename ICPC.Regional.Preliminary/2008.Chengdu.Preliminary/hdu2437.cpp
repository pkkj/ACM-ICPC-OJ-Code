// 2008 Chengdu Preliminary: Jerboas
// HDU 2437

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 1005
struct EDGE {
	int b, w;
	EDGE() { }
	EDGE(int b, int w) : b(b), w(w) { }
};
vector<EDGE> G[N];
int dp[N][N], n, m, s, k;
bool ok[N];

void dfs(int x, int v) {
	for (int i = 0; i < (int) G[x].size(); i++) {
		int d = (v + G[x][i].w) % k;
		int p = G[x][i].b;
		if (dp[p][d] == -1 || v + G[x][i].w < dp[p][d]) {
			dp[p][d] = v + G[x][i].w;
			dfs(p, v + G[x][i].w);
		}
	}
}

void solve() {
	int a, b, w, i, ans, best;
	scanf("%d%d%d%d\n", &n, &m, &s, &k);
	for (i = 1; i <= n; i++) {
		ok[i] = (getchar() == 'P');
		G[i].clear();
	}
	while (m--) {
		scanf("%d%d%d", &a, &b, &w);
		G[a].push_back(EDGE(b, w));
	}
	memset(dp, -1, sizeof(dp));
	dfs(s, 0);
	ans = best = -1;
	for (i = 1; i <= n; i++)
		if (ok[i] && dp[i][0] != -1 && (ans == -1 || dp[i][0] < ans))
			best = i, ans = dp[i][0];
	printf("%d %d\n", ans, best);
}

int main() {
	int T, ca = 1;
	scanf("%d\n", &T);
	while (T--) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
