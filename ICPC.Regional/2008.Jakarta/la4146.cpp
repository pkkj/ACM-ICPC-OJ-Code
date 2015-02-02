// 2008 Jakarta: ICPC Team Strategy
// ACM-ICPC Live Archive 4146
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 13
#define INF 1000000
int tt[3][N];
int dp[1 << N][3], n;
 
void solve() {
	int i, j, k, v, tot, ans = 0;
	scanf("%d", &n);
	for (i = 0; i < 3; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &tt[i][j]);
	memset(dp, -1, sizeof(dp));
	dp[0][0] = dp[0][1] = dp[0][2] = 0;
	tot = 1 << n;
	for (i = 1; i < tot; i++)
		for (j = 0; j < 3; j++)
			dp[i][j] = INF;
	for (i = 0; i < tot; i++)
		for (j = 0; j < 3; j++) {
			for (k = 0; k < n; k++) {
				if ((i & (1 << k)) == 0) {
					for (v = 0; v < 3; v++) {
						if (v == j) continue;
						dp[i | (1 << k)][v] = min(dp[i | (1 << k)][v], dp[i][j] + tt[v][k]);
					}
				}
			}
		}
	for (i = 0; i < tot; i++) {
		int cnt = 0, j = i;
		while (j) {
			if (j & 1) cnt++;
			j >>= 1;
		}
		if (cnt <= ans) continue;
		for (j = 0; j < 3; j++)
			if (dp[i][j] <= 280) ans = cnt;
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}