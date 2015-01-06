// POJ 3713
// POJ Monthly Contest - 2008.12.28: Transferring Sylla
#include <cstdio>
#include <cstring>
#define N 505
#define M 40005
struct EDGE {
	int b, next;
};
EDGE E[M];
int G[N], tot, vp;
short D[N], low[N], C[N];
int n, m, root;
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	G[a] = tot;
	E[tot++] = e;
}
 
int dfs(int x, int fa, int d) {
	int i, j, son = 0;
	C[x] = -1, D[x] = low[x] = d;
	vp++;
	for (i = G[x]; ~i; i = E[i].next) {
		j = E[i].b;
		if (C[j] == 2 || j == fa) continue;
		if (C[j] == -1) low[x] = low[x] < D[j] ? low[x] : D[j];
		else if (C[j] == 0) {
			if (dfs(j, x, d + 1)) return 1;
			son++;
			low[x] = low[x] < low[j] ? low[x] : low[j];
			if (x == root && son > 1 || x != root && low[j] >= D[x]) return 1;
		}
	}
	C[x] = 1;
	return 0;
}
 
int solve() {
	int a, b, i;
	memset(G, -1, sizeof(G));
	tot = 0;
	while (m--) {
		scanf("%d%d", &a, &b);
		addedge(a, b);
		addedge(b, a);
	}
	for (i = 0; i < n; i++) {
		root = i;
		vp = 0;
		memset(C, 0, sizeof(C));
		C[i] = 2;
		if (i == 0) root = 1;
		else root = 0;
		if (dfs(root, -1, 1) || vp < n - 1) return 0;
	}
	return 1;
}
int main() {
	while (scanf("%d%d", &n, &m) && n)
		printf(solve() ? "YES\n" : "NO\n");
	return 0;
}
