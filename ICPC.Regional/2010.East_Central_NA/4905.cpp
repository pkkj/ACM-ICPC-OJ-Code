// CII 4905
// 2010 East Central NA: Pro-Test Voting
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
int money, n;
int pop[N], Ip[N], delta[N];
int dp[N][N], from[N][N];
int get(int idx, int mon) {
	double ans = pop[idx] * (Ip[idx] + mon / (mon + 10.1) * delta[idx]) / 100;
	return int(ans + 0.5);
}
void solve() {
	int i, j, k;
	for (i = n - 1; i >= 0; i--)
		scanf("%d%d%d", &pop[i], &Ip[i], &delta[i]);
	for (i = 0; i <= money; i++) {
		dp[0][i] = get(0, i);
		from[0][i] = i;
	}
	for (i = 1; i < n; i++)
		for (j = 0; j <= money; j++) {
			dp[i][j] = 0;
			for (k = 0; k <= j; k++) {
				int nans = dp[i - 1][j - k] + get(i, k); // make j-k as small as possible
				if (nans >= dp[i][j]) {
					dp[i][j] = nans;
					from[i][j] = k;
				}
			}
		}
 
	printf("%d\n", dp[n - 1][money]);
	for (i = n - 1; i >= 0; i--) {
		if (i != n - 1) printf(" ");
		printf("%d:%d", n - 1 - i, from[i][money]);
		money -= from[i][money];
	}
 
}
int main() {
	int T = 0;
	while (scanf("%d%d", &money, &n) && money) {
		printf("Case %d: ", ++T);
		solve();
		printf("\n");
	}
}
