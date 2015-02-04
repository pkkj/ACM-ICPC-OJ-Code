// 2008 Dhaka: Clicking Checkboxes
// ACM-ICPC Live Archive 4205
#include <cstdio>
#include <cstring>
#define N 65

long long dp[N][N][N][2];
// dp[n][x][c][top]: the way of layouts when:
// n: total number of checkboxes
// x: total number of boxes should be checked.
// c: changing time from checked to unchecked, and unchecked to checked.
// top: whether the first box is checked (top = 1) or not (top = 0).

void init(){
	int n = 64;
	memset(dp, 0, sizeof(dp));
	dp[1][1][1][1] = dp[1][0][0][0] = 1;
	for (int i = 2; i <= n; i++){
		for (int x = 0; x <= n; x++){
			for (int c = 0; c <= n; c++){
				if (c - 2 >= 0 && x - 1 >= 0)
					dp[i][x][c][1] += dp[i - 1][x - 1][c - 2][0];
				if (x - 1 >= 0)
					dp[i][x][c][1] += dp[i - 1][x - 1][c][1];
				dp[i][x][c][0] = dp[i - 1][x][c][0] + dp[i - 1][x][c][1];
			}
		}
	}
}

int main(){
	int n, m, T = 0;
	init();
	while (scanf("%d%d", &n, &m) && n){
		long long ans1 = 0, ans2 = 0;
		for (int i = m; i <= n; i++){
			for (int j = 0; j < i; j++)
				ans1 += dp[n][i][j][0] + dp[n][i][j][1];
			for (int j = i + 1; j <= n; j++)
				ans2 += dp[n][i][j][0] + dp[n][i][j][1];
		}
		printf("Case %d: %lld %lld\n", ++T, ans1, ans2);
	}
	return 0;
}