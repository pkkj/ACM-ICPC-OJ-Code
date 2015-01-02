// CII 4299
// 2008 Southwestern Europe: Randomly-priced Tickets 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
#define R 3005
#define INF 100000
int g[N][N];
 
void floyd(int n) {
	int i, j, k;
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			if (g[i][k] > 0) for (j = 1; j <= n; j++)
				if (g[k][j] > 0) {
					int d = g[i][k] + g[k][j];
					if (d < g[i][j]) g[i][j] = d;
				}
		}
	}
}
 
double f[N][R];
void dp(int n, int mr) {
	memset(f, 0, sizeof f);
	for (int i = 1; i <= mr; i++)
		f[1][i] = 1.0 / mr;
	for (int i = 2; i <= n; ++i) {
		for (int j = i; j <= n * mr; ++j) {
			for (int k = j - 1; k >= 0 && j - k <= mr; --k) {
				f[i][j] += f[i - 1][k] / mr;
			}
		}
	}
}
void solve() {
	int n, mr, i, j;
	char cmd[300];
	scanf("%d%d\n", &n, &mr);
	for (i = 1; i <= n; i++) {
		scanf("%s", cmd);
		for (j = 0; j < n; j++)
			if (cmd[j] == 'Y') g[i][j + 1] = 1;
			else g[i][j + 1] = INF;
		g[i][i] = 0;
	}
	floyd(n);
	dp(n, mr);
	int Q;
	scanf("%d", &Q);
	while (Q--) {
		int s, t, r, d;
		scanf("%d%d%d", &s, &t, &r);
		d = g[s][t];
		r = min(r, d * mr);
		double ans = 0;
		for (i = 0; i <= r; i++)
			ans += f[d][i];
		printf("%.8lf\n", ans);
	}
}
 
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d\n", ca++);
		solve();
		printf("\n");
	}
	return 0;
}
