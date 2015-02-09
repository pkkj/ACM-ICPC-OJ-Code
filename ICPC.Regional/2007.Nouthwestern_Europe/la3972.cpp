// 2007 Nouthwestern Europe: March of the Penguins
// ACM-ICPC Live Archive 3972
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define NP 105
#define INF 100000000
const int maxn = 20010;
int N, S, T;
struct EDGE {
	int x, y;
	int c, rc;
	EDGE *nex, *bak;
	EDGE() {
	}
	EDGE(int x, int y, int c, EDGE* nex) :
			x(x), y(y), c(c), rc(c), nex(nex), bak(0) {
	}
	void* operator new(size_t, void *p) {
		return p;
	}
}*E[maxn];
int Q[maxn], D[maxn];
void DFS() {
	memset(D, -1, sizeof D);
	int p1 = 0, p2 = 0;
	Q[p2++] = S;
	D[S] = 0;
	for (;;) {
		int i = Q[p1++];
		for (EDGE* e = E[i]; e; e = e->nex) {
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
EDGE* cur[maxn];
EDGE* path[maxn];
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

			EDGE* e;
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

struct POINT {
	double x, y;
	int in, out;
};
inline double sqr(double x) {
	return x * x;
}
double dis(const POINT &p1, const POINT &p2) {
	return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}

void reset() {
	for (int i = 0; i <= N; i++) {
		for (EDGE* e = E[i]; e; e = e->nex) {
			e->c = e->rc;
		}
	}
}
void solve() {
	int i, j, np, id, total = 0;
	double d;
	POINT plist[NP];
	memset(E, 0, sizeof E);
	scanf("%d%lf", &np, &d);
	S = 0, N = np * 2 + 1;

	EDGE* data = new EDGE[100000];
	EDGE* base = data;
	for (i = 0, id = 1; i < np; i++, id += 2) {
		int x, y, w;
		scanf("%lf%lf%d%d", &plist[i].x, &plist[i].y, &plist[i].in, &plist[i].out);
		total += plist[i].in;
		x = S, y = id, w = plist[i].in;
		E[x] = new ((void*) data++) EDGE(x, y, w, E[x]);
		E[y] = new ((void*) data++) EDGE(y, x, 0, E[y]);
		E[x]->bak = E[y], E[y]->bak = E[x];

		x = id, y = id + 1, w = plist[i].out;
		E[x] = new ((void*) data++) EDGE(x, y, w, E[x]);
		E[y] = new ((void*) data++) EDGE(y, x, 0, E[y]);
		E[x]->bak = E[y], E[y]->bak = E[x];
	}

	d *= d;
	for (i = 0; i < np; i++)
		for (j = i + 1; j < np; j++) {
			if (dis(plist[i], plist[j]) <= d) {
				int x, y, w = INF;
				x = i * 2 + 2, y = j * 2 + 1;
				E[x] = new ((void*) data++) EDGE(x, y, w, E[x]);
				E[y] = new ((void*) data++) EDGE(y, x, 0, E[y]);
				E[x]->bak = E[y], E[y]->bak = E[x];

				x = j * 2 + 2, y = i * 2 + 1;
				E[x] = new ((void*) data++) EDGE(x, y, w, E[x]);
				E[y] = new ((void*) data++) EDGE(y, x, 0, E[y]);
				E[x]->bak = E[y], E[y]->bak = E[x];
			}
		}
	int ok = 0, begin = true;
	for (i = 0; i < np; i++) {
		T = i * 2 + 1;
		if (total == maxflow()) {
			if (begin)
				begin = false;
			else
				printf(" ");
			printf("%d", i), ok = 1;
		}
		reset();
	}
	if (!ok)
		printf("-1");
	printf("\n");

	delete[] base;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
