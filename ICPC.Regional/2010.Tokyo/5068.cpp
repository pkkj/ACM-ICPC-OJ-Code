// CII 5068
// 2010 Tokyo: Balloon Collecting
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 50
#define INF 1<<25
int pos[N], tim[N], dp[N][4], n;
 
void solve() {
	int i, j;
	for (i = 1; i <= n; i++)
		scanf("%d%d", &pos[i], &tim[i]);
	tim[0] = pos[0] = pos[n + 1] = 0;
	tim[n + 1] = INF;
	dp[0][1] = dp[0][2] = dp[0][3] = INF;
	if (tim[1] < pos[1]) dp[0][0] = INF;
	else dp[0][0] = 0;
	for (i = 1; i <= n; i++) {
		int t, ok = 0;
		// 1 ball
		if (dp[i - 1][0] != INF) dp[i][1] = dp[i - 1][0] + pos[i], ok = 1;
		else dp[i][1] = INF;
 
		// 2 ball
		t = abs(pos[i] - pos[i - 1]) * 2;
		if (t <= tim[i] - tim[i - 1] && dp[i - 1][1] != INF) dp[i][2] = dp[i - 1][1] + abs(pos[i] - pos[i - 1]), ok = 1;
		else dp[i][2] = INF;
 
		// 3 ball
		t = abs(pos[i] - pos[i - 1]) * 3;
		if (t <= tim[i] - tim[i - 1] && dp[i - 1][2] != INF) dp[i][3] = dp[i - 1][2] + abs(pos[i] - pos[i - 1]), ok = 1;
		else dp[i][3] = INF;
 
		if (!ok) {
			printf("NG %d\n", i);
			return;
		}
 
		// 0 ball
		dp[i][0] = INF;
		for (j = 1; j <= 3; j++)
			if (pos[i] * (j + 1) + pos[i + 1] <= tim[i + 1] - tim[i]) dp[i][0] = min(dp[i][0], dp[i][j] + pos[i]);
	}
	printf("OK %d\n", dp[n][0]);
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
