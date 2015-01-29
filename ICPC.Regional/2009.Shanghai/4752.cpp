// CII 4752
// 2009 Shanghai: Jinyuetuan Puzzle
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1005
#define M 7
#define BEGIN 1
#define MID 2
#define END 3
#define SINGLE 4
#define INF (1<<29)
#define CNT (1<<7)
int dp[N * 2][1 << M];
short plan[N * 2][M];
bool forb[1 << M];
bool period(char *s) {
	int i, len = strlen(s);
	for (i = 0; i < len; i++)
		if (s[i] == '-') return 1;
	return 0;
}
 
int solve() {
	int t, i, j, k, m, a, b, nf;
	char s[100];
	scanf("%d", &t);
	memset(plan, 0, sizeof(plan));
	memset(forb, 0, sizeof(forb));
	for (i = 0; i < 7; i++) {
		scanf("%d", &m);
		for (j = 0; j < m; j++) {
			scanf("%s", s);
			if (period(s)) {
				sscanf(s, "%d-%d", &a, &b);
				a = a * 2, b = b * 2 - 1;
				plan[a][i] = BEGIN, plan[b][i] = END;
				for (k = a + 1; k < b; k++)
					plan[k][i] = MID;
			} else {
				sscanf(s, "%d", &a);
				plan[a * 2][i] = SINGLE;
			}
		}
	}
 
	scanf("%d", &nf);
	for (i = 0; i < nf; i++) {
		a = 0;
		scanf("%s", s);
		for (j = 0; j < 7; j++)
			if (s[j] == '1') a |= (1 << j);
		forb[a] = 1;
		for (j = 0; j < CNT; j++)
			if ((a & j) == a) forb[j] = 1;
	}
	t = t * 2 + 1;
	for (i = 0; i <= t; i++)
		for (j = 0; j < CNT; j++)
			dp[i][j] = dp[i][j] = -INF;
	dp[0][0] = 0;
	for (i = 0; i <= t; i++) {
		int hasnot;
		for (j = 0; j < CNT; j++) {
			if (dp[i][j] == -INF) continue;
			//单个音节的按下，长时间按下音节的起始与结尾均得分。
			for (k = 0; k < 7; k++) {
				if ((1 << k) & j) if (plan[i][k] == END || plan[i][k] == BEGIN || plan[i][k] == SINGLE) dp[i][j]++;
			}
			hasnot = 0;
			//检查下一个可能达到的状态。
			for (k = 0; k < 7; k++) {
				if (plan[i + 1][k] == BEGIN || plan[i + 1][k] == SINGLE || ((plan[i + 1][k] == MID || plan[i + 1][k]
						== END) && ((1 << k) & j))) hasnot |= (1 << k);
			}
			for (k = 0; k < CNT; k++) {
				if (forb[k]) continue;
				if ((hasnot | k) != hasnot) continue;
				//如果可以由当前状态到达，那么则更新答案。
				dp[i + 1][k] = max(dp[i + 1][k], dp[i][j]);
			}
		}
	}
 
	int ans = 0;
	for (i = 0; i < CNT; i++)
		ans = ans > dp[t][i] ? ans : dp[t][i];
	return ans;
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--)
		printf("Case #%d: %d\n", ca++, solve());
	return 0;
}
