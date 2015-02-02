// 2008 Beijing: Destroying the bus stations
// ACM-ICPC Live Archive 4322
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 1000000
#define N 105
int S, T;
struct edge {
	int x, y;
	int c, f;
	edge *nex,
			*bak;
	edge() {
	}
	edge(int x, int y, int c, int f, edge* nex)
	:
		x(x), y(y), c(c), f(f), nex(nex), bak(0) {
	}
	void* operator new(size_t, void *p) {
		return p;
	}
}*G[N];
int Q[100000], D[N];
void DFS() {
	memset(D, -1, sizeof D);
	int p1 = 0, p2 = 0;
	Q[p2++] = S;
	D[S] = 0;
	for (;;) {
		int i = Q[p1++];
		for (edge* e = G[i]; e; e = e->nex) {
			if (e->c == 0) continue;
			int j = e->y;
			if (-1 == D[j]) {
				Q[p2++] = j;
				D[j] = D[i] + 1;
				if (j == T) return;
			}
		}
		if (p1 == p2) break;
	}
}
edge* cur[N];
edge* path[N];
int maxflow() {
	int flow = 0;
	int path_n;
	for (;;) {
		DFS();
		if (-1 == D[T]) break;
		memcpy(cur, G, sizeof G);
		path_n = 0;
		int i = S;
		for (;;) {
			if (i == T) {
				int k;
				int mink = 0;
				int d = INF;
				for (k = 0; k < path_n; ++k) {
					if ((path[k]->c) < d) {
						d = path[k]->c;
						mink = k;
					}
				}
				for (k = 0; k < path_n; ++k) {
					(path[k]->c) -= d;
					((path[k]->bak)->c) += d;
				}
				path_n = mink;
				i = path[path_n]->x;
				flow += d;
			}
 
			edge* e;
			for (e = cur[i]; e; e = e->nex) {
				if (!e->c) continue;
				int j = e->y;
				if (D[i] + 1 == D[j]) break;
			}
			cur[i] = e;
			if (e) {
				path[path_n++] = e;
				i = e->y;
			} else {
				D[i] = -1;
				if (!path_n) break;
				path_n--;
				i = path[path_n]->x;
			}
		}
	}
	return flow;
}
 
edge *base, *data;
void addedge(int x, int y, int w) {
	G[x] = new ((void*) data++) edge(x, y, w, w, G[x]);
	G[y] = new ((void*) data++) edge(y, x, 0, 0, G[y]);
	G[x]->bak = G[y], G[y]->bak = G[x];
}
 
int n, m, k;
bool g[N][N];
int d1[N], d2[N];
 
void bfs1() {
	int qh, qe, inq = 1, next, step = 1;
	memset(d1, -1, sizeof(d1));
	qh = qe = 0;
	Q[qe++] = 1;
	d1[1] = 0;
	while (qh < qe) {
		next = 0;
		while (inq--) {
			int top = Q[qh++];
			for (int i = 1; i <= n; i++)
				if (g[top][i] && d1[i] == -1) {
					d1[i] = step, Q[qe++] = i;
					next++;
				}
		}
		inq = next;
		step++;
	}
}
void bfs2() {
	int qh, qe, inq = 1, next, step = 1;
	memset(d2, -1, sizeof(d2));
	qh = qe = 0;
	Q[qe++] = n;
	d2[n] = 0;
	while (qh < qe) {
		next = 0;
		while (inq--) {
			int top = Q[qh++];
			for (int i = 1; i <= n; i++)
				if (g[i][top] && d2[i] == -1) {
					d2[i] = step, Q[qe++] = i;
					next++;
				}
		}
		inq = next;
		step++;
	}
}
 
void read() {
	int a, b;
	memset(g, 0, sizeof(g));
	while (m--) {
		scanf("%d%d", &a, &b);
		g[a][b] = 1;
	}
}
void build() {
	bool use[N] = { 0 };
	int i, j;
	for (i = 1; i <= n; i++)
		if (d1[i] + d2[i] <= k) use[i] = 1;
	memset(G, 0, sizeof(G));
	data = new edge[100000];
	base = data;
	for (i = 1; i <= n; i++) {
		if (!use[i]) continue;
		addedge(i, i + n, 1);
		for (j = 1; j <= n; j++) {
			if (use[j] && g[i][j]) addedge(i + n, j, 1);
		}
	}
	S = 1 + n, T = n;
	printf("%d\n", maxflow());
	delete[] base;
}
 
int main() {
	while (scanf("%d%d%d", &n, &m, &k) && n) {
		read();
		bfs1();
		bfs2();
		build();
	}
	return 0;
}