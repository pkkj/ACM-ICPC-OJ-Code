// CII 4772
// 2009 Harbin: FM
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 609
#define BA 9
#define MAXM 10000
#define MAXF 0x0FFFFFFF
struct EDGE {
	int a, b;
	int cost, c, f, next;
};
EDGE E2[MAXM], E[MAXM];
int G2[N], G[N], tot;
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
 
int table[7][8] = { { 1, 2, 1, 1, 2, 1, 1, 2 }, { 1, 2, 1, 1, 3, 1, 1, 1 }, { 1, 2, 1, 1, 3, 0, 0, 3 }, { 1, 3, 0, 0, 3, 1, 1, 2 }, { 1, 3,
		0, 0, 4, 1, 1, 1 }, { 1, 3, 1, 1, 3, 0, 0, 2 }, { 1, 4, 1, 1, 3, 0, 0, 1 } };
int n;
 
void solve() {
	int i, j, x, ans[12], best = -1;
	char s[50];
	init();
	S = n + 20;
	T = S + 1;
	for (i = 0; i < n; i++) {
		scanf("%s", s);
		addedge(BA + i, T, 0, 1);
		for (j = 0; j < 8; j++) {
			scanf("%d", &x);
			if (x) addedge(j, BA + i, -x, 1);
		}
	}
	memcpy(E2, E, sizeof(E));
	memcpy(G2, G, sizeof(G));
	for (i = 0; i < 7; i++) {
		memcpy(E, E2, sizeof(E));
		memcpy(G, G2, sizeof(G));
		for (j = 0; j < 8; j++)
			if (table[i][j]) addedge(S, j, 0, table[i][j]);
		costflow();
		ans[i] = -anscost;
		if (ans[i] > best) best = ans[i];
	}
	for (i = 0; i < 7; i++)
		if (ans[i] == best) {
			if (i < 6) printf("Formation %c has the highest points %d.\n", 'A' + i, best);
			else printf("Formation China has the highest points %d.\n", best);
		}
	printf("\n");
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
