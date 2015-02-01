// 2008 Taipei: Bonus Adjustment
// CII 4268
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#define INF 1000000
#define MAXN 105
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
}*E[MAXN];
int Q[100000], D[MAXN];
void DFS() {
	memset(D, -1, sizeof D);
	int p1 = 0, p2 = 0;
	Q[p2++] = S;
	D[S] = 0;
	for (;;) {
		int i = Q[p1++];
		for (edge* e = E[i]; e; e = e->nex) {
			if (e->c == 0)
				continue;
			int j = e->y;
			if (-1 == D[j]) {
				Q[p2++] = j;
				D[j] = D[i] + 1;
				if (j == T)
					return;
			}
		}
		if (p1 == p2)
			break;
	}
}
edge* cur[MAXN];
edge* path[MAXN];
int maxflow() {
	int flow = 0;
	int path_n;
	for (;;) {
		DFS();
		if (-1 == D[T])
			break;
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
				if (!e->c)
					continue;
				int j = e->y;
				if (D[i] + 1 == D[j])
					break;
			}
			cur[i] = e;
			if (e) {
				path[path_n++] = e;
				i = e->y;
			} else {
				D[i] = -1;
				if (!path_n)
					break;
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
#define N 55
double g0[N][N], g1[N][N];
double row[N], col[N];
int sgn(double x) {
	return x < -1e-8 ? -1 : x > 1e-8;
}
void solve() {
	int n, m, i, j, sum = 0;
	scanf("%d%d", &n, &m);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			scanf("%lf", &g0[i][j]);
			g1[i][j] = floor(g0[i][j]);
		}
	memset(row, 0, sizeof(row));
	memset(col, 0, sizeof(col));
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			row[i] += g0[i][j] - g1[i][j];
			col[j] += g0[i][j] - g1[i][j];
		}
	}
	memset(E, 0, sizeof(E));
	data = new edge[4000];
	base = data;
	S = 0, T = n + m + 1;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (sgn(g0[i][j] - g1[i][j]))
				addedge(i + 1, n + 1 + j, 1);
		}
	}
	for (i = 0; i < n; i++) {
		if (sgn(row[i]))
			addedge(S, i + 1, (int) (row[i] + 0.5));
		sum += (int) (row[i] + 0.5);
	}
	for (i = 0; i < m; i++)
		if (sgn(col[i]))
			addedge(i + 1 + n, T, (int) (col[i] + 0.5));
	if (maxflow() != sum)
		printf("no\n");
	else {
		data = base;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++)
				if (sgn(g0[i][j] - g1[i][j])) {
					if (data->f - data->c)
						printf("%.0lf ", g1[i][j] + 1);
					else
						printf("%.0lf ", g1[i][j]);
					data += 2;
				} else {
					printf("%.0lf ", g0[i][j]);
				}
			printf("\n");
		}
	}
	delete[] base;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
