// 2006 Dhaka: Paint the Roads
// ACM-ICPC Live Archive 2197
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define MAXM 10000
#define MAXN 100
#define MAXF 0x0FFFFFFF
 
struct edge {
	int a, b;
	int cost, c, f, next;
};
edge ET[MAXM];
int EH[MAXN], tot;
int dist[MAXN], low[MAXN], pre[MAXN];
 
int S, T, ans, anscost;
 
bool spfa() {
	queue<int> Q;
	bool inQ[MAXN] = { 0 };
	fill(dist, dist + MAXN, MAXF);
	memset(pre, -1, sizeof pre);
	dist[S] = 0, inQ[S] = 1, low[S] = MAXF;
	Q.push(S);
	while (!Q.empty()) {
		int k = Q.front();
		Q.pop();
		inQ[k] = 0;
		for (int p = EH[k]; p != -1; p = ET[p].next) {
			int T = ET[p].b, w = ET[p].cost, c = ET[p].c, f = ET[p].f;
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
	return dist[T] != MAXF;
}
void costflow() {
	ans = 0, anscost = 0;
	while (spfa()) {
		int p = pre[T];
		ans += low[T];
		anscost += low[T] * dist[T];
		while (p != -1) {
			ET[p].f += low[T];
			ET[p ^ 1].f -= low[T];
			ET[p ^ 1].cost = -ET[p].cost;
			p = pre[ET[p].a];
		}
	}
}
void add(int a, int b, int cost, int c, int f = 0) {
	edge E = { a, b, cost, c, f, EH[a] };
	ET[tot] = E;
	EH[a] = tot++;
}
void addedge(int a, int b, int cost, int flow) {
	add(a, b, cost, flow, 0), add(b, a, MAXF, 0, 0);
}
 
void init() {
	memset(EH, -1, sizeof EH);
	tot = 0;
}
void solve() {
	int i, n, m, k, a, b, w;
	init();
	scanf("%d%d%d", &n, &m, &k);
	S = n * 2, T = n * 2 + 1;
 
	for (i = 0; i < n; i++) {
		addedge(S, i, 0, k);
		addedge(i + n, T, 0, k);
	}
	while (m--) {
		scanf("%d%d%d", &a, &b, &w);
		addedge(a, b + n, w, 1);
	}
	costflow();
	if (ans == n * k) printf("%d\n", anscost);
	else printf("-1\n");
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}