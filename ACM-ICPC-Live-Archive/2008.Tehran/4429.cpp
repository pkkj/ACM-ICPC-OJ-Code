// CII 4429
// 2008 Tehran: Hurry Plotter
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1005
 
int n, t;
struct SEG {
	int y, x1, x2;
	bool operator <(const SEG &s) const {
		if (y != s.y) return y < s.y;
		return x1 < s.x1;
	}
	void get() {
		scanf("%d%d%d", &y, &x1, &x2);
	}
};
SEG sl[N];
int dp[N][N];
int dis(SEG &a, SEG &b) {
	if (a.y == b.y) return b.x1 - a.x2;
	return a.x2 + b.x1;
}
 
void solve() {
	int i, j, k, best = 0;
	for (i = 1; i <= n; i++)
		sl[i].get();
	sort(sl + 1, sl + n + 1);
	for (i = 1; i <= n; i++)
		dp[i][1] = sl[i].x2 - sl[i].x1 + sl[i].x2;
	for (i = 1; i <= n; i++)
		for (j = 2; j <= i; j++) {
			dp[i][j] = 1 << 30;
			for (k = j - 1; k < i; k++)
				dp[i][j] = min(dp[i][j], dp[k][j - 1] + dis(sl[k], sl[i]));
			dp[i][j] += (sl[i].x2 - sl[i].x1) * 2;
		}
 
	for (i = 1; i <= n; i++)
		for (j = 1; j <= i; j++)
			if (dp[i][j] <= t) best = max(j, best);
	printf("%d\n", best);
}
int main() {
	while (scanf("%d%d", &n, &t) && n + t)
		solve();
	return 0;
}
