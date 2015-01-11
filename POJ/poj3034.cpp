// POJ 3034
// Nordic 2006: Whac-a-Mole
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define T 12
#define N 35
bool mo[T][N][N];
int dp[T][N][N];
int n, d, m;
int gcd(int m, int n) {
	int r;
	if (m < 0) m = -m;
	if (n < 0) n = -n;
	if (m == 0) return n;
	if (n == 0) return m;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
int main() {
	while (scanf("%d%d%d", &n, &d, &m) && n) {
		int i, j, t, i2, j2, k;
		n += 2 * d;
		memset(mo, 0, sizeof(mo));
		while (m--) {
			scanf("%d%d%d", &i, &j, &t);
			mo[t][i + d][j + d] = 1;
		}
		memset(dp[0], 0, sizeof(dp[0]));
		for (t = 1; t <= 10; t++) {
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++) {
					dp[t][i][j] = dp[t - 1][i][j] + mo[t][i][j];
					for (i2 = max(i - d, 0); i2 <= min(i + d, n - 1); i2++)
						for (j2 = max(j - d, 0); j2 <= min(j + d, n - 1); j2++) {
							int dx = i - i2, dy = j - j2, g, sx, sy, cnt = 0;
							if (dx * dx + dy * dy > d * d) continue;
							if (dx == 0 && dy == 0) continue;
							g = gcd(dx, dy);
							sx = dx / g, sy = dy / g;
							for (k = 0; k <= g; k++)
								if (mo[t][sx * k + i2][sy * k + j2]) cnt++;
							dp[t][i][j] = max(dp[t - 1][i2][j2] + cnt, dp[t][i][j]);
						}
				}
		}
		int ans = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				ans = max(dp[10][i][j], ans);
		printf("%d\n", ans);
	}
	return 0;
}
