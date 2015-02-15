// 2008 Harbin: Mining Station on the Sea
// ACM-ICPC Live Archive 4314

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 205
#define M 105
int nx, ny, w[M][M], lx[M], ly[M];
int fx[M], fy[M];
int matx[N], maty[N];
int path(int u) {
	int v;
	fx[u] = 1;
	for (v = 1; v <= ny; v++) {
		if (lx[u] + ly[v] == w[u][v] && fy[v] < 0) {
			fy[v] = 1;
			if (maty[v] < 0 || path(maty[v])) {
				matx[u] = v, maty[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
int KM() {
	int ans = 0, p, i, j, k;
	memset(ly, 0, sizeof(ly));
	for (i = 1; i <= nx; i++) {
		lx[i] = 0x7fffffff + 1;
		for (j = 1; j <= ny; j++)
			if (w[i][j] > lx[i]) lx[i] = w[i][j];
	}
	memset(matx, -1, sizeof(matx));
	memset(maty, -1, sizeof(maty));
	for (i = 1; i <= nx; i++) {
		memset(fx, -1, sizeof(fx));
		memset(fy, -1, sizeof(fy));
		if (!path(i)) {
			i--;
			p = 0x7fffffff;
			for (k = 1; k <= nx; k++) {
				if (fx[k] > 0) {
					for (j = 1; j <= ny; j++) {
						if (fy[j] < 0 && lx[k] + ly[j] - w[k][j] < p) p = lx[k] + ly[j] - w[k][j];
					}
				}
			}
			for (j = 1; j <= ny; j++)
				ly[j] += (fy[j] < 0 ? 0 : p);
			for (j = 1; j <= nx; j++)
				lx[j] -= (fx[j] < 0 ? 0 : p);
		}
	}
	for (i = 1; i <= ny; i++) {
		if (maty[i] == -1) continue;
		ans += w[maty[i]][i];
	}
	return ans;
}
int n, m, k, p;
int g[M][N], mine[N][N], ves[M];
 
void floyd() {
	int i, j, k;
	for (k = 1; k <= m; k++) {
		for (i = 1; i <= m; i++) {
			for (j = i + 1; j <= m; j++) {
				int d = mine[i][k] + mine[k][j];
				if (d < mine[i][j]) mine[i][j] = mine[j][i] = d;
			}
		}
	}
}
void solve() {
	int i, j, u, a, b, l;
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= m; j++)
			mine[i][j] = 0xfffffff;
		mine[i][i] = 0;
	}
	for (i = 1; i <= n; i++)
		scanf("%d", ves + i);
	while (k--) {
		scanf("%d%d%d", &a, &b, &l);
		mine[a][b] = mine[b][a] = l;
	}
	memset(g, -1, sizeof(g));
	while (p--) {
		scanf("%d%d%d", &a, &b, &l);
		g[a][b] = l;
	}
	floyd();
	for (i = 1; i <= n; i++) {
		int x = ves[i];
		for (j = 1; j <= n; j++) {
			w[i][j] = 0xfffffff;
			for (u = 1; u <= m; u++)
				if (g[j][u] != -1) w[i][j] = min(w[i][j], g[j][u] + mine[u][x]);
			w[i][j] = -w[i][j];
		}
	}
	nx = ny = n;
	printf("%d\n", -KM());
}
 
int main() {
	while (~scanf("%d%d%d%d", &n, &m, &k, &p))
		solve();
	return 0;
}