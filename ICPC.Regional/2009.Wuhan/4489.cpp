// CII 4489 
// 2009 Wuhan: Gift Hunting
#include <cstdio>
#include <cstring>
#define N 505
#define M 55
int V1, V2, n;
 
int dp[N][M][2], num[N][M][2];
int solve() {
	int it, p, h, s, i, j, k, sp = 0;
	memset(dp, -1, sizeof(dp));
	memset(num, 0, sizeof(num));
	dp[0][0][0] = 0;
	for (it = 0; it < n; it++) {
		scanf("%d%d%d", &p, &h, &s);
		sp += s;
		for (i = V1; i >= 0; i--)
			for (j = V2; j >= 0; j--) {
				for (k = 1; k >= 0; k--) {
					// Using coupon X
					if (i >= p && dp[i - p][j][k] != -1) {
						if (num[i - p][j][k] + s > num[i][j][k]) {
							num[i][j][k] = num[i - p][j][k] + s;
							dp[i][j][k] = dp[i - p][j][k] + h;
						} else if (num[i - p][j][k] + s == num[i][j][k]) {
							if (dp[i - p][j][k] + h > dp[i][j][k]) dp[i][j][k] = dp[i - p][j][k] + h;
						}
					}
 
					// Using coupon Y
					if (j >= p && dp[i][j - p][k] != -1) {
						if (num[i][j - p][k] + s > num[i][j][k]) {
							num[i][j][k] = num[i][j - p][k] + s;
							dp[i][j][k] = dp[i][j - p][k] + h;
						} else if (num[i][j - p][k] + s == num[i][j][k]) {
							if (dp[i][j - p][k] + h > dp[i][j][k]) dp[i][j][k] = dp[i][j - p][k] + h;
						}
					}
 
					// Using bonus
					if (k >= 1 && dp[i][j][k - 1] != -1) {
						if (num[i][j][k - 1] + s > num[i][j][k]) {
							num[i][j][k] = num[i][j][k - 1] + s;
							dp[i][j][k] = dp[i][j][k - 1] + h;
						} else if (num[i][j][k - 1] + s == num[i][j][k]) {
							if (dp[i][j][k - 1] + h > dp[i][j][k]) dp[i][j][k] = dp[i][j][k - 1] + h;
						}
					}
				}
			}
	}
	int best = -1;
	for (i = 0; i <= V1; i++)
		for (j = 0; j <= V2; j++)
			for (k = 0; k < 2; k++)
				if (num[i][j][k] == sp && dp[i][j][k] > best) best = dp[i][j][k];
	return best;
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d", &V1, &V2, &n) && n)
		printf("Case %d: %d\n\n", ca++, solve());
	return 0;
}
