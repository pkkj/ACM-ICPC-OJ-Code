// 2008 Hefei Preliminary: Kindergarten
// POJ 3692
#include <cstdio>
#include <cstring>
#define N 500

int g[N][N], v[N], link[N], color[N], nl, nr;
int n, m;

// Maximum matching in bipartite graph
int dfs(int t) {
	int i;
	for (i = 1; i <= nr; i++) {
		if (!v[i] && g[t][i]) {
			v[i] = 1;
			if (link[i] == -1 || dfs(link[i])) {
				link[i] = t;
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	int i, j, a, b, ng, nb, m, T = 1;
	while (scanf("%d%d%d", &ng, &nb, &m) && ng + nb + m) {
		int ans = 0;
		memset(g, 0, sizeof(g));
		for (i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			g[a][ng + b] = g[ng + b][a] = 1;
		}
		for (i = 1; i <= ng; i++)
			for (j = 1; j <= ng; j++)
				g[i][j] = 1;
		for (i = 1; i <= nb; i++)
			for (j = 1; j <= nb; j++)
				g[ng + i][ng + j] = 1;
		nl = nr = ng + nb;
		for (i = 1; i <= nl; i++) {
			for (j = 1; j <= nl; j++)
				g[i][j] = !g[i][j];
			g[i][i] = 0;
		}
		memset(link, -1, sizeof(link));
		memset(v, 0, sizeof(v));
		for (i = 1; i <= nl; i++) {
			memset(v, 0, sizeof(v));
			ans += dfs(i);
		}
		printf("Case %d: %d\n", T++, nl - ans / 2);
	}
	return 0;
}
