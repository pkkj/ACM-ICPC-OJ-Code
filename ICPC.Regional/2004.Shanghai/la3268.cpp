// 2004 Shanghai: Jamie's Contact Groups
// POJ 2289
// ACM-ICPC Live Archive 3268
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 1600
#define INT_MAX 1<<30
int S, T;
struct edge {
	int x, y;
	int c, f;
	edge *nex, *bak;
	edge() {
	}
	edge(int x, int y, int c, edge* nex) :
			x(x), y(y), c(c), f(0), nex(nex), bak(0) {
	}
	void* operator new(size_t, void *p) {
		return p;
	}
}*E[N];
int Q[N], D[N];
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
edge* cur[N];
edge* path[N];
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
				int d = INT_MAX;
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
#define M 1005
vector<int> contact[M];
int n, m;
int netflow(int v) {
	int i, j, x, y, w;
	memset(E, 0, sizeof E);
	S = 0;
	T = n + m + 1;
	edge* data = new edge[1000000]; //记住开足边数
	edge* base = data;
	for (i = 1; i <= n; i++) {
		x = S, y = i, w = 1;
		E[x] = new ((void*) data++) edge(x, y, w, E[x]);
		E[y] = new ((void*) data++) edge(y, x, 0, E[y]);
		E[x]->bak = E[y], E[y]->bak = E[x];
		for (j = 0; j < (int) contact[i].size(); j++) {
			x = i, y = contact[i][j] + 1 + n, w = 1;
			E[x] = new ((void*) data++) edge(x, y, w, E[x]);
			E[y] = new ((void*) data++) edge(y, x, 0, E[y]);
			E[x]->bak = E[y], E[y]->bak = E[x];
		}
	}
	for (i = 1; i <= m; i++) {
		x = n + i, y = T, w = v;
		E[x] = new ((void*) data++) edge(x, y, w, E[x]);
		E[y] = new ((void*) data++) edge(y, x, 0, E[y]);
		E[x]->bak = E[y], E[y]->bak = E[x];
	}
	int ret = maxflow();
	delete[] base;
	return ret;
}

inline bool isletter(char ch);
inline bool isdigit(char ch);
char cmd[500000];
void readline(int id) {
	char num[10];
	int i = 0, j = 0, x;
	gets(cmd);
	int len = strlen(cmd);
	cmd[len] = ' ', cmd[len + 1] = 0;
	while (isletter(cmd[i]))
		i++;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i]) {
		j = 0;
		while (cmd[i] != ' ')
			num[j++] = cmd[i++];
		while (cmd[i] == ' ')
			i++;
		num[j] = 0;
		sscanf(num, "%d", &x);
		contact[id].push_back(x);
	}

}
void solve() {
	int i;
	for (i = 1; i <= n; i++) {
		contact[i].clear();
		readline(i);
	}
	int l, mid, r, tt;
	l = 1, r = n + 1;
	while (l < r) {
		mid = (l + r) / 2;
		tt = netflow(mid);
		if (tt >= n)
			r = mid;
		else
			l = mid + 1;
	}
	printf("%d\n", l);
}

int main() {
	while (scanf("%d%d\n", &n, &m) && n + m)
		solve();
	return 0;
}

inline bool isletter(char ch) {
	return (ch >= 'a' & ch <= 'z' || ch >= 'A' && ch <= 'Z');
}
inline bool isdigit(char ch) {
	return ch >= '0' && ch <= '9';
}
