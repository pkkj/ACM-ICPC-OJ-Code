// CII 4201
// 2008 Dhaka: Switch Bulbs
#include <cstdio>
#include <cstring>
#define N ((1<<15)+1)
struct EDGE {
	int b, next;
};
int G[N], tot;
EDGE E[N * 100];
char ask[20];
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	G[a] = tot;
	E[tot++] = e;
}
int Q[N], d[N];
void bfs(int n) {
	int qh, qe, i;
	qh = qe = 0;
	Q[qe++] = 0;
	memset(d, -1, sizeof(d));
	d[0] = 0;
	while (qh < qe) {
		int head = Q[qh++];
		for (i = G[head]; ~i; i = E[i].next) {
			if (d[E[i].b] == -1) d[E[i].b] = d[head] + 1, Q[qe++] = E[i].b;
		}
	}
}
void solve() {
	int n, m, x, i, t, j, st, cnt, Q;
	scanf("%d%d", &n, &m);
	tot = 0;
	cnt = 1 << n;
	memset(G, -1, sizeof(G));
	for (i = 0; i < m; i++) {
		scanf("%d", &t);
		st = 0;
		for (j = 0; j < t; j++) {
			scanf("%d", &x);
			st |= (1 << x);
		}
		for (j = 0; j < cnt; j++)
			addedge(j, j ^ st);
	}
	bfs(1 << n);
	scanf("%d", &Q);
	while (Q--) {
		scanf("%s", ask);
		st = j = 0;
		for (i = n-1; i >= 0; i--,j++)
			if (ask[i] == '1') st |= (1 << j);
		printf("%d\n", d[st]);
	}
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d:\n", ca++);
		solve();
		printf("\n");
	}
	return 0;
}
