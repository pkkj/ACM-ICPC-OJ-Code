// 2008 Amritapuri: Palindromic paths
// CII 4336
#include <cstdio>
#include <cstring>
#define N 55
char ch[N][N];
char dp[N][N][N];
void f(int a, int b) {
	if (a == b) return;
	if (dp[a][b][0] != 0) return;
	dp[a][b][0] = ch[a][b];
	for (int i = a + 1; i < b; i++) {
		for (int j = b - 1; j >= i; j--)
			if (ch[a][i] == ch[j][b]) {
				char s[N] = { 0 };
				f(i, j);
				int l1 = strlen(dp[i][j]) + 2;
				int l2 = strlen(dp[a][b]);
				if (l1 < l2) continue;
				strcpy(s + 1, dp[i][j]);
				s[0] = ch[a][i];
				s[strlen(s)] = ch[a][i];
				if (l1 > l2) strcpy(dp[a][b], s);
				else if (strcmp(s, dp[a][b]) < 0) strcpy(dp[a][b], s);
			}
	}
}
void solve() {
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%s", ch[i]);
	memset(dp, 0, sizeof(dp));
	f(0, n - 1);
	printf("%s\n", dp[0][n - 1]);
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}