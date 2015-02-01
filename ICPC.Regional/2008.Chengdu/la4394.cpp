// 2008 Chengdu: Counting square
// ACM-ICPC Live Archive 4401
#include <cstdio>
#include <cstring>
#define N 301
 
int cnt[N][N], linev[N][N], lineh[N][N];
int iabs(int x) {
	return x < 0 ? -x : x;
}
void solve() {
	int n, m, i, j, k, ans = 0;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			scanf("%d", &cnt[i][j]);
	memset(linev, 0, sizeof(linev));
	memset(lineh, 0, sizeof(lineh));
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++) {
			linev[i][j] = linev[i - 1][j] + cnt[i][j];
			lineh[i][j] = lineh[i][j - 1] + cnt[i][j];
		}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			cnt[i][j] += (cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1]);
 
	for (i = 1; i <= n - 1; i++)
		for (j = 1; j <= m - 1; j++)
			for (k = 1; i + k <= n && j + k <= m; k++) {
				if (lineh[i + k][j + k] - lineh[i + k][j - 1] != k + 1) continue;
				if (lineh[i][j + k] - lineh[i][j - 1] != k + 1) continue;
				if (linev[i + k][j + k] - linev[i - 1][j + k] != k + 1) continue;
				if (linev[i + k][j] - linev[i - 1][j] != k + 1) continue;
				if (k == 1) ans++;
				else {
					int a = (k - 1) * (k - 1);
					int sum = cnt[i + k - 1][j + k - 1] - cnt[i][j + k - 1] - cnt[i + k - 1][j] + cnt[i][j];
					int c0 = a - sum, c1 = sum;
					if (iabs(c1 - c0) <= 1) ans++;
				}
			}
	printf("%d\n", ans);
}
 
int main() {
	int T;
	memset(cnt, 0, sizeof(cnt));
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}