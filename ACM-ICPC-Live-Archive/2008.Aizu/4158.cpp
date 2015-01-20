// 2008 Aizu: Expected Allowance
// ACM-ICPC Live Archive 4158
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000
int dp[50][N];
int main() {
	int n, m, k, i, j, u;
	while (scanf("%d%d%d", &n, &m, &k) && n) {
		memset(dp, 0, sizeof(dp));
		for (i = 1; i <= m; i++)
			dp[1][i] = 1;
		for (i = 2; i <= n; i++)
			for (j = i; j <= i * m; j++) {
				for (u = j - 1; u >= j - m; u--) {
					if (u == 0) break;
					dp[i][j] += dp[i - 1][u];
				}
			}
		double base = 1, ans = 0;
		for (i = 1; i <= n; i++)
			base *= m;
		for (i = n; i <= n * m; i++)
			if (i - k <= 0) ans += dp[n][i] / base;
			else ans += dp[n][i] / base * (i - k);
 
		printf("%.10lf\n", ans);
	}
	return 0;
}