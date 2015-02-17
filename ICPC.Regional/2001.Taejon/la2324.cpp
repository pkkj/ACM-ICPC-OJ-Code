// 2001 Taejon: Human Gene Functions
// ACM-ICPC Live Archive 2324
// POJ 1080

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define INF 10000000
int dp[N][N], d1[N], d2[N], map[100];
char s1[N], s2[N];

int table[4][4] = { { 5, -1, -2, -1 }, { -1, 5, -3, -2 }, { -2, -3, 5, -2 }, { -1, -2, -2, 5 } };
int gap[4] = { -3, -4, -2, -1 };
void solve() {
	int l1, l2, i, j;
	scanf("%d%s", &l1, s1 + 1);
	scanf("%d%s", &l2, s2 + 1);
	for (i = 1; i <= l1; i++)
		d1[i] = map[(int) s1[i]];
	for (i = 1; i <= l2; i++)
		d2[i] = map[(int) s2[i]];
	for (i = 0; i <= l1; i++)
		for (j = 0; j <= l2; j++)
			dp[i][j] = -INF;
	dp[0][0] = 0;
	for (i = 1; i <= l1; i++)
		dp[i][0] = dp[i - 1][0] + gap[d1[i]];
	for (i = 1; i <= l2; i++)
		dp[0][i] = dp[0][i - 1] + gap[d2[i]];
	for (i = 1; i <= l1; i++) {
		for (j = 1; j <= l2; j++) {
			dp[i][j] = max(dp[i][j], dp[i - 1][j] + gap[d1[i]]);
			dp[i][j] = max(dp[i][j], dp[i][j - 1] + gap[d2[j]]);
			dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + table[d1[i]][d2[j]]);
		}
	}
	printf("%d\n", dp[l1][l2]);
}
int main() {
	int T;
	map['A'] = 0, map['C'] = 1, map['G'] = 2, map['T'] = 3;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
