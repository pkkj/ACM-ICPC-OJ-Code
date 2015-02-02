// 2007 Dhaka: ACM Puzzles
// ACM-ICPC Live Archive 4058
#include <cstdio>
#include <cstring>
#define M 1000000000000LL
#define N 26
long long dp[2005][27];
int from[22][3] = { { 2, 2, 2 }, { 1, 1, 1 }, { 1, 2, 1 }, { 2, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 2, 1, 2 }, { 2, 1, 0 }, { 0, 1, 2 }, {
		2, 1, 1 }, { 1, 1, 2 }, { 1, 1, 1 }, { 1, 1, 2 }, { 1, 1, 1 }, { 1, 2, 2 }, { 1, 0, 0 }, { 0, 0, 1 }, { 1, 1, 1 }, { 2, 2, 1 }, {
		0, 1, 1 }, { 1, 1, 0 }, { 1, 1, 1 } };
 
int to[22][3] = { { 2, 2, 2 }, { 1, 2, 1 }, { 2, 2, 2 }, { 2, 2, 2 }, { 1, 2, 1 }, { 2, 1, 2 }, { 2, 2, 2 }, { 2, 2, 1 }, { 1, 2, 2 }, { 2,
		2, 1 }, { 1, 2, 2 }, { 2, 2, 1 }, { 2, 2, 2 }, { 2, 1, 1 }, { 2, 2, 2 }, { 2, 1, 0 }, { 0, 1, 2 }, { 1, 1, 2 }, { 2, 2, 2 }, { 2,
		1, 1 }, { 1, 1, 2 }, { 1, 2, 2 } };
void calc() {
	int i, j, k, p, st;
	int v[3];
	memset(dp[0], 0, sizeof(dp[0]));
	dp[0][N] = 1;
	for (i = 0; i < 2000; i++) {
		for (j = 0; j <= N; j++) {
			if (!dp[i][j]) continue;
			v[0] = j / 9, v[1] = (j / 3) % 3, v[2] = j % 3;
			for (k = 0; k < 22; k++) {
				int ok = 1;
				for (p = 0; p < 3 && ok; p++)
					if (v[p] != from[k][p]) ok = 0;
				if (!ok) continue;
				st = to[k][0] * 9 + to[k][1] * 3 + to[k][2];
				dp[i + 1][st] += dp[i][j];
				dp[i + 1][st] %= M;
			}
			int ok = 1;
			for (p = 0; p < 3 && ok; p++) {
				v[p]--;
				if (v[p] < 0) ok = 0;
			}
			if (!ok) continue;
			st = v[0] * 9 + v[1] * 3 + v[2];
			dp[i + 1][st] += dp[i][j];
			dp[i + 1][st] %= M;
		}
	}
}
int main() {
	calc();
	int ca = 1, n;
	while (scanf("%d", &n) && n)
		printf("Case %d: %lld\n", ca++, dp[n][N]);
	return 0;
}