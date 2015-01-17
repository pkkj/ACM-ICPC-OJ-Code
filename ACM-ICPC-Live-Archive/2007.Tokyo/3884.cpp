// 2007 Tokyo: Minimal Backgammon
// ACM-ICPC Live Archive 3884
// POJ 3519
#include <cstdio>
#include <cstring>
#define N 105
int n, T, nl, nb;
double dp[N][N];
bool lose[N], back[N];
double solve() {
	int i, t, j, x;
	double ans = 0;
	memset(dp, 0, sizeof(dp));
	memset(lose, 0, sizeof(lose));
	memset(back, 0, sizeof(back));
	for (i = 0; i < nl; i++) {
		scanf("%d", &x);
		lose[x] = 1;
	}
	for (i = 0; i < nb; i++) {
		scanf("%d", &x);
		back[x] = 1;
	}
	dp[0][0] = 1.0;
	for (t = 0; t < T; t++) {
		for (i = 0; i < n; i++) {
			if (back[i]) continue;
			for (j = 1; j <= 6; j++) {
				int next = i + j;
				if (next > n) next = n - (j - (n - i));
				if (lose[i]) {
					if (back[next]) dp[t + 2][0] += dp[t][i] / 6.0;
					else dp[t + 2][next] += dp[t][i] / 6.0;
				} else {
					if (back[next]) dp[t + 1][0] += dp[t][i] / 6.0;
					else dp[t + 1][next] += dp[t][i] / 6.0;
				}
			}
		}
	}
	for(i = 1; i <= T;i++)
		ans += dp[i][n];
	return ans;
}
int main() {
	//freopen("in.txt", "r", stdin);
	while (scanf("%d%d%d%d", &n, &T, &nl, &nb) && n)
		printf("%.7lf\n", solve());
	return 0;
}