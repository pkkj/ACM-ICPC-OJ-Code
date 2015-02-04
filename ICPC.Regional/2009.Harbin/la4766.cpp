// CII 4770
// 2009 Harbin: Gold Mines
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 1009
#define MAXM 500000
#define MAXF 0x0FFFFFFF
#define INF 9000000
struct EDGE {
	int a, b;
	int cost, c, f, next;
};
EDGE E[MAXM];
int G[N], tot;
int dist[N], low[N], pre[N];
int S, T, ans, anscost;
bool spfa() {
	queue<int> Q;
	bool inQ[N] = { 0 };
	fill(dist, dist + N, MAXF);
	memset(pre, -1, sizeof pre);
	dist[S] = 0, inQ[S] = 1, low[S] = MAXF;
	Q.push(S);
	while (!Q.empty()) {
		int k = Q.front();
		Q.pop();
		inQ[k] = 0;
		for (int p = G[k]; p != -1; p = E[p].next) {
			int t = E[p].b, w = E[p].cost, c = E[p].c, f = E[p].f;
			if (f < c && dist[k] + w < dist[t]) {
				dist[t] = dist[k] + w;
				pre[t] = p;
				low[t] = min(low[k], c - f);
				if (!inQ[t]) {
					inQ[t] = 1;
					Q.push(t);
				}
			}
		}
	}
	return dist[T] != MAXF;
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
	EDGE e = { a, b, cost, c, f, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
void addedge(int a, int b, int cost, int flow) {
	add(a, b, cost, flow, 0), add(b, a, MAXF, 0, 0);
}
 
void init() {
	memset(G, -1, sizeof G);
	tot = 0;
}
 
struct ELIST {
	int a, b;
	void get() {
		scanf("%d%d", &a, &b);
	}
};
int mine[10], val[N], n, m, ng;
ELIST el[N * N / 2];
int check(int st) {
	int i;
	init();
	S = n * 2 + 2, T = n * 2 + 3;
	for (i = 0; i < ng * 2; i++) {
		if (st & (1 << i)) addedge(S, mine[i] * 2, 0, 1);
		else addedge(mine[i] * 2 + 1, T, 0, 1);
	}
	for (i = 0; i < n; i++) {
		addedge(i * 2, i * 2 + 1, val[i], 1);
	}
	for (i = 0; i < m; i++) {
		addedge(el[i].a * 2 + 1, el[i].b * 2, 0, 1);
		addedge(el[i].b * 2 + 1, el[i].a * 2, 0, 1);
	}
	costflow();
	if (ans == ng) return anscost;
	return INF;
}
 
void solve() {
	int i, ans = INF, cnt, total = 0;
	bool vis[1 << 8] = { 0 };
	scanf("%d%d", &n, &m);
	for (i = 0; i < m; i++)
		el[i].get();
	scanf("%d", &ng);
	for (i = 0; i < 2 * ng; i++)
		scanf("%d", &mine[i]);
	for (i = 0; i < n; i++) {
		scanf("%d", &val[i]);
		total += val[i];
	}
	cnt = 1 << (2 * ng);
	for (i = 1; i < cnt; i++) {
		if (vis[i]) continue;
		int st = i, c1 = 0;
		while (st) {
			c1 += (st & 1) > 0;
			st >>= 1;
		}
		if (c1 != ng) continue;
		int fi = ~i;
		fi = fi & ((1 << (ng * 2)) - 1);
		vis[fi] = 1;
		ans = min(ans, check(i));
	}
	if (ans == INF) ans = -1;
	else ans = total - ans;
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
