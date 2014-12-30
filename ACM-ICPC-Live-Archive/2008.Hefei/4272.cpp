// CII 4272
// 2008 Hefei: Polynomial-time Reductions
#include <cstdio>
#include <cstring>
 
#define N 105
struct EDGE {
	int b, next;
};
EDGE E[N * N * 4];
int GA[N], GD[N], tot, G[N][N];
;
void addedge(int *G, int a, int b) {
	EDGE e = { b, G[a] };
	G[a] = tot;
	E[tot++] = e;
}
bool v[N];
int block[N], pp, pos[N], n, m, bsize[N], id[N];
 
void dfs1(int x) {
	v[x] = 1;
	for (int i = GA[x]; ~i; i = E[i].next)
		if (!v[E[i].b]) dfs1(E[i].b);
	pos[pp++] = x;
}
void dfs2(int x, int id) {
	v[x] = 0, block[x] = id;
	for (int i = GD[x]; ~i; i = E[i].next)
		if (v[E[i].b]) dfs2(E[i].b, id);
}
void solve() {
	int i, j, k, nblock = 0, ans = 0, tn = 0;
	tot = 0;
	memset(GA, -1, sizeof(GA));
	memset(GD, -1, sizeof(GD));
	while (m--) {
		scanf("%d%d", &i, &j);
		addedge(GA, i, j), addedge(GD, j, i);
	}
	//
	pp = 1;
	memset(v, 0, sizeof(v));
	for (i = 1; i <= n; i++)
		if (!v[i]) dfs1(i);
	for (i = n; i >= 1; i--)
		if (v[pos[i]]) dfs2(pos[i], pos[i]), nblock++;
	for (i = 1; i <= n; i++)
		if (block[i] == i) id[i] = ++tn;
	// Floyd Algorithm
	memset(G, 0, sizeof(G));
	for (i = 1; i <= n; i++) {
		G[id[i]][id[i]] = 1;
		for (j = GA[i]; ~j; j = E[j].next)
			G[id[block[i]]][id[block[E[j].b]]] = 1;
	}
	for (k = 1; k <= tn; k++)
		for (i = 1; i <= tn; i++)
			for (j = 1; j <= tn; j++) {
				if (i == j) continue;
				if (G[i][k] && G[k][j] && i != k && j != k) if (G[i][k] + G[k][j] > G[i][j]) G[i][j] = G[i][k] + G[k][j];
			}
	// Calculate answer
	memset(bsize, 0, sizeof(bsize));
	for (i = 1; i <= n; i++)
		bsize[block[i]]++;
	for (i = 1; i <= n; i++)
		if (bsize[i] > 1) ans += bsize[i];
	for (i = 1; i <= tn; i++)
		for (j = 1; j <= tn; j++) {
			if (i == j) continue;
			if (G[i][j] == 1) ans++;
		}
	printf("%d\n", ans);
}
int main() {
	int T = 1;
	//freopen("in.txt", "r", stdin);
	while (scanf("%d%d", &n, &m) && n) {
		printf("Case %d: ", T++);
		solve();
	}
	return 0;
}
