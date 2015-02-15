// 2003 Guangzhou: Vivian's Problem
// ACM-ICPC Live Archive 2955
// POJ 1777

#include <cstdio>
#include <cstring>
 
long long mp[] = { (1 << 2) - 1, (1 << 3) - 1, (1 << 5) - 1, (1 << 7) - 1, (1 << 13) - 1, (1 << 17)
		- 1, (1 << 19) - 1, (1LL << 31LL) - 1 };
int mask[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
int we[] = { 2, 3, 5, 7, 13, 17, 19, 31 };
int vi[256];
 
void init() {
	memset(vi, 0, sizeof(vi));
	int i, j;
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 8; j++)
			if (i & mask[j]) vi[i] += we[j];
	}
}
 
void solve(int n) {
	int i, p1 = 0, p2 = 1, x, j;
	int dp[2][256];
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (i = 0; i < n; i++) {
		int bin = 0, ok = 1;
		scanf("%d", &x);
		for (j = 0; j < 8 && ok && x > 1; j++) {
			if (x % mp[j] == 0) {
				int t = x / mp[j];
				bin = bin | mask[j];
				if (t % mp[j] == 0) ok = 0;
				x /= mp[j];
			}
		}
		if (bin && ok && x == 1) {
			for (j = 0; j < 256; j++)
				dp[p2][j] = dp[p1][j];
			for (j = 0; j < 256; j++) {
				if ((j & bin) == 0 && dp[p1][j])
					dp[p2][j != 0 ? (j | bin) : bin] = 1;
			}
			p1 = !p1, p2 = !p2;
		}
	}
	int ans = 0;
	for (i = 0; i < 256; i++)
		if (dp[p1][i] && vi[i] > ans) ans = vi[i];
	if (ans) printf("%d\n", ans);
	else printf("NO\n");
}
int main() {
	init();
	int n;
	while (scanf("%d", &n) != EOF)
		solve(n);
	return 0;
}