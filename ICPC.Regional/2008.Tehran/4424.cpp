// CII 4424
// 2008 Tehran: Painting
#include <cstdio>
#include <cstring>
#define N 102
short g[N][N], x[N], y[N];
bool v[N * N];
struct NODE {
	int d, sum, x, y;
};
NODE tt[N * N];
int n, m, num[N * N], ans[N * N];
void solve() {
	int k, i, j, len;
	memset(tt, 0, sizeof(tt));
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			scanf("%d", &k);
			g[i][j] = k;
			tt[k].sum++;
			if (tt[k].sum == 1) tt[k].x = i, tt[k].y = j, tt[k].d = 2;
			else if (tt[k].x == i) tt[k].d = 1;
			else tt[k].d = 0;
		}
	}
	len = 0;
	for (i = 1; i <= 10000; i++) {
		if (tt[i].sum) {
			tt[len] = tt[i];
			num[len++] = i;
		}
	}
	memset(v, 0, sizeof(v));
	memset(x, 0, sizeof(x));
	memset(y, 0, sizeof(y));
	for (i = 0; i < len; i++) {
		int next = -1, p, d;
		for (j = len - 1; j >= 0 && next == -1; j--) {
			if (v[j]) continue;
			if ((tt[j].d == 1 || tt[j].d == 2) && tt[j].sum + x[tt[j].x] == m) next = j, p = tt[j].x, d = 1;
			if ((tt[j].d == 0 || tt[j].d == 2) && tt[j].sum + y[tt[j].y] == n) next = j, p = tt[j].y, d = 0;
		}
		ans[len - i - 1] = num[next];
		v[next] = 1;
		if (d) {
			for (j = 0; j < m; j++)
				if (g[p][j] == num[next]) x[p]++, y[j]++, g[p][j] = 0;
		} else {
			for (j = 0; j < n; j++)
				if (g[j][p] == num[next]) x[j]++, y[p]++, g[j][p] = 0;
		}
	}
	int st = 1;
	for (i = 0; i < len; i++) {
		if (st) st = 0;
		else printf(" ");
		printf("%d", ans[i]);
	}
	printf("\n");
}
int main() {
	while (scanf("%d%d", &n, &m) && n)
		solve();
	return 0;
}
