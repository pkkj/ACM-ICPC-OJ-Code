// 2004 Shanghai: Islands and Bridges
// POJ 2288
// ACM-ICPC Live Archive 3267
#include <cstdio>
#include <cstring>
#define N 14
#define M (1<<13)+1
int dp[N][N][M], v[N];
long long cnt[N][N][M];
bool map[N][N];
 
void solve() {
	int n, m, i, j, k, l, cost = 0;
	memset(map, 0, sizeof(map));
	memset(dp, -1, sizeof(dp));
	memset(cnt, 0, sizeof(cnt));
	scanf("%d%d", &n, &m);
	for (i = 0; i < n; i++) {
		scanf("%d", &v[i]);
		cost += v[i];
	}
	while (m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--, b--;
		map[a][b] = map[b][a] = 1;
		dp[a][b][(1 << a) | (1 << b)] = dp[b][a][(1 << b) | (1 << a)] = v[a] * v[b];
		cnt[a][b][(1 << a) | (1 << b)] = cnt[b][a][(1 << b) | (1 << a)] = 1;
	}
	if (n == 1) {
		printf("%d 1\n", cost);
		return;
	}
	int tntst = (1 << n) - 1;
	for (k = 3; k <= tntst; k++) {
		for (i = 0; i < n; i++) {
			if (!((1 << i) & k)) continue;
			for (j = 0; j < n; j++) {
				if (!((1 << j) & k) || dp[i][j][k] == -1) continue;
				for (l = 0; l < n; l++) {
					if (((1<<l)&k) || !map[l][j]) continue;
					int st = k | (1 << l);
					int t = dp[i][j][k] + v[j] * v[l];
					if (map[i][l]) t += v[i] * v[j] * v[l];
					if (t > dp[j][l][st]) dp[j][l][st] = t, cnt[j][l][st] = cnt[i][j][k];
					else if (t == dp[j][l][st]) cnt[j][l][st] += cnt[i][j][k];
				}
			}
		}
	}
	int best = 0;
	long long road = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (map[i][j] && dp[i][j][tntst] > best) best = dp[i][j][tntst], road
					= cnt[i][j][tntst];
			else if (map[i][j] && dp[i][j][tntst] == best) road += cnt[i][j][tntst];
		}
	if (road == 0) printf("0 0\n");
	else printf("%d %lld\n", best + cost, road / 2);
 
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}