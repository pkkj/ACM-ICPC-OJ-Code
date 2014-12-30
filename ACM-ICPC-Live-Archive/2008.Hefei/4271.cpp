// CII 4271
// 2008 Hefei: Necklace
#include <cstdio>
#include <cstring>
#define N 10001
#define M 200005
using namespace std;
int V[N], D[N], low[N], ftr[N];
struct EDGE {
	int a, b, next, vis, brg;
};
EDGE ET[M];
int G[N], tot;
void addedge(int a, int b) {
	EDGE x = { a, b, G[a], 0, 0 };
	ET[tot] = x;
	G[a] = tot++;
}
int root;
void dfs(int x, int d) {
	int i, j, son = 0;
	V[x] = 1, low[x] = D[x] = d;
	for (i = G[x]; i != -1; i = ET[i].next) {
		if (!ET[i].vis) {
			j = ET[i].b;
			if (V[j]) {
				if (i != (ftr[x] ^ 1) && D[j] < low[x]) low[x] = D[j];
			} else {
				ftr[j] = i, son++;
				dfs(j, d + 1);
				ET[i].vis = ET[i ^ 1].vis = 1;
				if (low[j] > D[x]) ET[i].brg = ET[i ^ 1].brg = 1;
				if (low[j] < low[x]) low[x] = low[j];
			}
		}
	}
}
int s, t;
int dfs(int x) {
	int i;
	if (x == t) return 1;
	V[x] = 1;
	for (i = G[x]; i != -1; i = ET[i].next) {
		if (!ET[i].brg && !V[ET[i].b]) {
			if (dfs(ET[i].b)) return 1;
		}
	}
	return 0;
}
int main() {
	int m, i, n, a, b, T = 0;
	while (scanf("%d%d", &n, &m) && n) {
		printf("Case %d: ", ++T);
		memset(G, -1, sizeof(G));
		memset(V, 0, sizeof(V));
		tot = 0;
		for (i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			addedge(a, b), addedge(b, a);
		}
		scanf("%d%d", &s, &t);
		for (i = 1; i <= n; i++)
			if (!V[i]) root = i, dfs(i, 1);
		memset(V, 0, sizeof(V));
		if (dfs(s)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
