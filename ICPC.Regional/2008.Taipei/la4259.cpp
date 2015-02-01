// 2008 Taipei: Dangerous Tunnels
// CII 4259
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 410
#define M N*N
#define INF 1000000
struct EDGE {
	int a, b, w;
	void get() {
		scanf("%d%d%d", &a, &b, &w);
		if (a > b) swap(a, b);
	}
	bool operator<(const EDGE &e) const {
		return w < e.w;
	}
};
int S, T;
struct edge {
	int x, y;
	int c, f;
	edge *nex, *bak;
	edge() {
	}
	edge(int x, int y, int c, int f, edge* nex) :
		x(x), y(y), c(c), f(f), nex(nex), bak(0) {
	}
	void* operator new(size_t, void *p) {
		return p;
	}
}*E[N];
int Q[100000], D[N];
void DFS() {
	memset(D, -1, sizeof D);
	int p1 = 0, p2 = 0;
	Q[p2++] = S;
	D[S] = 0;
	for (;;) {
		int i = Q[p1++];
		for (edge* e = E[i]; e; e = e->nex) {
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
		memcpy(cur, E, sizeof E);
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
	E[x] = new ((void*) data++) edge(x, y, w, w, E[x]);
	E[y] = new ((void*) data++) edge(y, x, 0, 0, E[y]);
	E[x]->bak = E[y], E[y]->bak = E[x];
}
EDGE el[M];
int n;
int check(int mid) {
	int i;
	memset(E, 0, sizeof(E));
	data = new edge[100000];
	base = data;
	S = 0, T = 2 * n + 1;
	for (i = 1; i <= n; i++)
		addedge(i, i + n, 1);
	for (i = 0; i <= mid; i++) {
		int x, y;
		if (el[i].a) x = el[i].a + n;
		else x = el[i].a;
		if (el[i].b == n + 1) y = T;
		else y = el[i].b;
		addedge(x, y, 1);
 
	}
	int ans = maxflow();
	delete[] base;
	return ans;
}
 
void solve() {
	int m, K, i;
	scanf("%d", &m);
	for (i = 0; i < m; i++)
		el[i].get();
	scanf("%d", &K);
	sort(el, el + m);
	int l, r, mid;
	l = 0, r = m - 1;
	if (check(r) < K) {
		printf("no solution\n");
		return;
	}
	while (l < r) {
		mid = (l + r) >> 1;
		if (check(mid) >= K) r = mid;
		else l = mid + 1;
	}
	printf("%d\n", el[r].w);
}
int main() {
	int st = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", st++);
		solve();
	}
	return 0;
}