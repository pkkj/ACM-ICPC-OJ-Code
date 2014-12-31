// CII 4613
// 2009 Northwestern Europe: Mountain Road
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct INFO {
	int t, d;
	INFO() {
	}
	INFO(int t, int d) :
		t(t), d(d) {
	}
};
#define N 205
#define INF 1<<30
INFO l1[N], l2[N];
int dp[N][N][2], pst[N][N][2];
void solve() {
	int n, i, n1, n2, j, k;
	char s[20];
	scanf("%d", &n);
	n1 = n2 = 0;
	for (i = 0; i < n; i++) {
		int t, d;
		scanf("%s%d%d", s, &t, &d);
		if (s[0] == 'A') l1[++n1] = INFO(t, d);
		else l2[++n2] = INFO(t, d);
	}
	for (i = 0; i <= n1; i++)
		for (j = 0; j <= n2; j++)
			for (k = 0; k <= 2; k++)
				dp[i][j][k] = INF;
	memset(pst, 0, sizeof(pst));
	dp[0][0][0] = dp[0][0][1] = 0;
	for (i = 0; i <= n1; i++)
		for (j = 0; j <= n2; j++) {
			int ti, re;
			re = max(dp[i][j][1] + l1[i + 1].d, l1[i + 1].t + l1[i + 1].d);
			dp[i + 1][j][0] = min(dp[i + 1][j][0], re);
			ti = l1[i + 1].d;
			for (k = i + 2; k <= n1; k++) {
				int st = max(re - ti + 10, l1[k].t);
				re = max(re + 10, st + l1[k].d);
				ti = re - st;
				dp[k][j][0] = min(re, dp[k][j][0]);
			}
			re = max(dp[i][j][0] + l2[j + 1].d, l2[j + 1].t + l2[j + 1].d);
			dp[i][j + 1][1] = min(dp[i][j + 1][1], re);
			ti = l2[j + 1].d;
			for (k = j + 2; k <= n2; k++) {
				int st = max(re - ti + 10, l2[k].t);
				re = max(re + 10, st + l2[k].d);
				ti = re - st;
				dp[i][k][1] = min(re, dp[i][k][1]);
			}
		}
	printf("%d\n", min(dp[n1][n2][0], dp[n1][n2][1]));
}
int main() {
	int T;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
