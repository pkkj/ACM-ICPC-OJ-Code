// 2008 Taipei: Early-Morning Pickup
// ACM-ICPC Live Archive 4263
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
#define MAXM 300000
#define MAXN 1500
#define INF 0x0FFFFFFF
#define N 530
struct EDGE {
	short a, b;
	int cost, c, f, next;
};
EDGE E[MAXM];
int GG[MAXN], tot;
int dist[MAXN], low[MAXN], pre[MAXN];
int S, T, ans, anscost;
 
bool spfa() {
	queue<int> Q;
	bool inQ[MAXN] = { 0 };
	fill(dist, dist + MAXN, INF);
	memset(pre, -1, sizeof pre);
	dist[S] = 0, inQ[S] = 1, low[S] = INF;
	Q.push(S);
	while (!Q.empty()) {
		int k = Q.front();
		Q.pop();
		inQ[k] = 0;
		for (int p = GG[k]; p != -1; p = E[p].next) {
			int T = E[p].b, w = E[p].cost, c = E[p].c, f = E[p].f;
			if (f < c && dist[k] + w < dist[T]) {
				dist[T] = dist[k] + w;
				pre[T] = p;
				low[T] = min(low[k], c - f);
				if (!inQ[T]) {
					inQ[T] = 1;
					Q.push(T);
				}
			}
		}
	}
	return dist[T] != INF;
}
void costflow() {
	ans = 0, anscost = 0;
	while (spfa()) {
		int p = pre[T];
		ans += low[T];
		anscost += low[T] * dist[T];
		while (p != -1) {
			E[p].f += low[T];
			E[p ^ 1].f -= low[T];
			E[p ^ 1].cost = -E[p].cost;
			p = pre[E[p].a];
		}
	}
}
void add(int a, int b, int cost, int c, int f = 0) {
	EDGE e = { a, b, cost, c, f, GG[a] };
	E[tot] = e;
	GG[a] = tot++;
}
void addedge(int a, int b, int cost, int c) {
	add(a, b, cost, c, 0), add(b, a, INF, 0, 0);
}
 
void init() {
	memset(GG, -1, sizeof GG);
	tot = 0;
}
int G[N][N];
int rep[N][2], nr;
int station[N], custom[N], ns, nc;
 
int getmin(int r, int c) {
	int ret = INF, i;
	for (i = 0; i < ns; i++)
		if (G[custom[c]][station[i]] + G[station[i]][rep[r][1]] < ret) ret = G[custom[c]][station[i]] + G[station[i]][rep[r][1]];
	return ret + G[rep[r][0]][custom[c]];
}
void floyd(int n) {
	int i, j, k;
	for (k = 1; k <= n; k++) {
		for (i = 1; i <= n; i++) {
			if (G[i][k] != -1) for (j = i + 1; j <= n; j++)
				if (G[k][j] != -1) {
					int d = G[i][k] + G[k][j];
					if (d < G[i][j] || G[i][j] == -1) G[i][j] = G[j][i] = d;
				}
		}
	}
}
void solve() {
	int n, m, a, b, w, i, j, unfull;
	memset(G, -1, sizeof(G));
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d%d", &a, &b, &w);
		if (G[a][b] == -1 || w < G[a][b]) G[a][b] = G[b][a] = w;
	}
	scanf("%d", &nr);
	for (i = 0; i < nr; i++)
		scanf("%d%d", &rep[i][0], &rep[i][1]);
	scanf("%d", &nc);
	for (i = 0; i < nc; i++)
		scanf("%d", &custom[i]);
	scanf("%d", &ns);
	for (i = 0; i < ns; i++)
		scanf("%d", &station[i]);
	floyd(n);
	init();
	S = 0, T = nc + nr + 2, unfull = nc + nr + 1;
	for (i = 0; i < nr; i++)
		addedge(S, i + 1, 0, 1);
	for (i = 0; i < nc; i++)
		addedge(nr + i + 1, T, 0, 1);
	addedge(unfull, T, 0, nr - nc);
	if (nr - nc) for (i = 0; i < nr; i++)
		addedge(i + 1, unfull, G[rep[i][0]][rep[i][1]], 1);
	for (i = 0; i < nr; i++)
		for (j = 0; j < nc; j++)
			addedge(i + 1, nr + j + 1, getmin(i, j), 1);
	costflow();
	double ave = (double) anscost / nr;
	int ans = (int) ceil(ave);
	printf("%02d:%02d\n", ans / 60 + 8, ans % 60);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}