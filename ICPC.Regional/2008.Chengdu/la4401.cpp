// 2008 Chengdu: String painter
// ACM-ICPC Live Archive 4394
#include <cstdio>
#include <cstring>
#define N 105
#define M 27
int dp[N][N][M];
char A[N], B[N];
int dfs(int l, int r, int ch) {
	int c, t, i;
	if (dp[l][r][ch] == -1) {
		if (ch) c = ch;
		else c = A[l];
		if (c == B[l]) dp[l][r][ch] = dfs(l+1, r, ch);
		else {
			dp[l][r][ch] = dfs(l + 1, r, ch) + 1;
			for (i = l + 1; i <= r; i++) {
				if (B[l] != B[i]) continue;
				t = dfs(l + 1, i - 1, B[l]) + dfs(i + 1, r, ch) + 1;
				dp[l][r][ch] = dp[l][r][ch] < t ? dp[l][r][ch] : t;
			}
		}
	}
	return dp[l][r][ch];
}
int main() {
	while (~scanf("%s", A)) {
		scanf("%s", B);
		int n = strlen(A), i, j, k;
		for (i = 0; i < n; i++)
			A[i] = A[i] - 'a' + 1, B[i] = B[i] - 'a' + 1;
		for (i = 0; i < n; i++)
			for (j = i; j < n; j++)
				for (k = 0; k < M; k++) {
					if (i == j) {
						if (!k) dp[i][j][k] = A[i] != B[i];
						else dp[i][j][k] = k != B[i];
					} else dp[i][j][k] = -1;
				}
		printf("%d\n", dfs(0, n - 1, 0));
	}
	return 0;
}