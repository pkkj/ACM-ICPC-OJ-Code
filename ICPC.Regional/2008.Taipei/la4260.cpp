// 2008 Taipei: Fortune Card Game
// ACM-ICPC Live Archive 4260
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 805
#define L 155
struct CARD {
	int id, next;
	char ch;
};
char cmd[2], s[L];
int dp[L][N];
struct EDGE {
	int b, next;
};
int G[N], tot;
EDGE E[N * N];
CARD cl[N];
void addedge(int x, int y) {
	EDGE e = { y, G[x] };
	G[x] = tot;
	E[tot++] = e;
}
void solve() {
	int n, i, j, k, len;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d%s%d", &cl[i].id, cmd, &cl[i].next);
		cl[i].ch = cmd[0];
	}
	scanf("%s", s);
	// Build Graph
	tot = 0;
	memset(G, -1, sizeof(G));
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			if (cl[i].id == cl[j].next) addedge(i, j);
	}
	// Solve it by DP
	memset(dp, 0, sizeof(dp));
	for (i = 0; i < n; i++) {
		if (cl[i].ch == s[0] && cl[i].id == 1) dp[0][i] = cl[i].next;
	}
	len = strlen(s);
	for (i = 1; i < len; i++) {
		for (j = 0; j < n; j++) {
			if (s[i] == cl[j].ch) {
				for (k = G[j]; ~k; k = E[k].next)
					dp[i][j] = max(dp[i][j], dp[i - 1][E[k].b]);
				if (dp[i][j]) dp[i][j] += cl[j].next;
			}
		}
	}
	int ans = 0;
	for (i = 0; i < n; i++)
		ans = max(dp[len - 1][i], ans);
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}