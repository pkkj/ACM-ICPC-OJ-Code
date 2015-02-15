// 2008 Harbin Preliminary: The Accomodation of Students
// HDU 2444

#include <stdio.h>
#include <string.h>
#define N 201

int g[N][N], v[N], link[N], color[N], nl, nr;
int n, m;

int dfs2(int t, int col) {
	int i;
	v[t] = 1;
	color[t] = col;
	for (i = 1; i <= n; i++) {
		if (g[i][t]) {
			if (!v[i]) {
				if (dfs2(i, !col))
					return 1;
			} else if (color[t] == color[i])
				return 1;
		}
	}
	return 0;
}
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

void solve() {
	int i, a, b, ans = 0;
	memset(g, 0, sizeof(g));
	for (i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}
	for (i = 0; i < N; i++)
		link[i] = -1;

	memset(v, 0, sizeof(v));
	memset(color, 0, sizeof(color));
	for (i = 1; i <= n; i++) {
		if (!v[i])
			if (dfs2(i, 0)) {
				printf("No\n");
				return;
			}
	}

	nl = nr = n;
	for (i = 1; i <= nl; i++) {
		memset(v, 0, sizeof(v));
		ans += dfs(i);
	}
	printf("%d\n", ans / 2);
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF)
		solve();
}
