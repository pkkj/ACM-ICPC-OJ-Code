// 2006 Tokyo: Enjoyable Commutation
// ACM-ICPC Live Archive 3624
// POJ 3137
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 52
#define INF 99999999
using namespace std;
int n, m, K, S, T;
struct LIST {
	short v[N], sz;
	LIST() {
		init();
	}
	void init() {
		sz = 0;
	}
	void add(short x) {
		v[sz++] = x;
	}
	short &operator [](const int &i) {
		return v[i];
	}
	bool operator >(const LIST &p) const {
		int i = sz - 1, j = p.sz - 1;
		for (; i >= 0 && j >= 0; i--, j--)
			if (v[i] != p.v[j]) return v[i] > p.v[j];
		return sz > p.sz;
	}
	void reverse() {
		std::reverse(v, v + sz);
	}
};
 
// Declare of graph
struct EDGE {
	short y, next, len;
	EDGE() {
	}
	EDGE(short y, short next, short len) :
		y(y), next(next), len(len) {
	}
};
EDGE E[N * N];
short G[N], dd[N][N], tot;
void addedge(int a, int b, int w) {
	dd[a][b] = w;
	E[tot] = EDGE(b, G[a], w);
	G[a] = tot++;
}
 
// End of declare of graph
// DIJ shortest path
int dist[N], pre[N];
bool vis[N], block[N][N];
 
int dijkstra() {
	int i, j, x, best;
	for (i = 0; i < n; i++) {
		best = INF;
		for (j = 0; j < n; j++)
			if (dist[j] < best && !vis[j]) best = dist[j], x = j;
		if (best == INF) break;
		vis[x] = 1;
		for (j = G[x]; ~j; j = E[j].next) {
			int y = E[j].y;
			if (vis[y] || block[x][y]) continue;
			int ndis = dist[x] + dd[x][y];
			if (dist[y] < ndis) continue;
			if (dist[y] == ndis && x >= pre[y]) continue;
			pre[y] = x, dist[y] = ndis;
		}
	}
	return vis[T];
}
 
// End of Dij
// Yen loopless k-shortest path algorithm
struct PATH {
	LIST path, block;
	int len, dev;
	PATH() {
		path.sz = 0;
	}
	void print() {
		printf("%d", (int) path[path.sz - 1] + 1);
		for (int i = path.sz - 2; i >= 0; i--)
			printf("-%d", (int) path[i] + 1);
		printf("\n");
	}
	bool operator<(const PATH &p) const {
		if (len != p.len) return len > p.len;
		return path > p.path;
	}
};
PATH ans;
int getk;
void init_path() {
	memset(vis, 0, sizeof(vis));
	memset(pre, -1, sizeof(pre));
	for (int i = 0; i < n; i++)
		dist[i] = INF;
	dist[S] = 0;
}
void del_sub_path(PATH &p, int dev) {
	short back = p.path[0];
	vis[back] = 1;
	for (int i = 1; i < dev; i++) {
		short v = p.path[i];
		pre[v] = back;
		dist[v] = dist[back] + dd[back][v];
		vis[v] = 1;
		back = v;
	}
	vis[back] = 0;
}
 
PATH get_path() {
	PATH ans;
	ans.path.add(T);
	ans.len = dist[T];
	for (int i = pre[T]; i != -1; i = pre[i])
		ans.path.add(i);
	ans.path.reverse();
	return ans;
}
void yen() {
	priority_queue<PATH> Q;
	memset(block, 0, sizeof(block));
	getk = 0;
	init_path();
	if (dijkstra()) {
		PATH p = get_path();
		p.dev = 1;
		p.block.add(p.path[p.dev]);
		Q.push(p);
	}
	while (getk < K && !Q.empty()) {
		PATH p = Q.top();
		Q.pop();
		int dev = p.dev;
		while (dev < p.path.sz) {
			int pre = p.path[dev - 1];
			if (dev == p.dev) {
				for (int i = 0; i < p.block.sz; i++)
					block[pre][p.block[i]] = 1;
			} else block[pre][p.path[dev]] = 1;
			init_path();
			del_sub_path(p, dev);
			if (dijkstra()) {
				PATH np = get_path();
				np.dev = dev;
				if (dev == p.dev) np.block = p.block;
				else np.block.add(p.path[dev]);
				np.block.add(np.path[dev]);
				Q.push(np);
			}
			dev++;
		}
		memset(block, 0, sizeof(block));
		getk++;
		if (getk == K) ans = p;
	}
}
 
// End of yen algorithm
 
// Main
void read() {
	int a, b, w;
	memset(G, -1, sizeof(G));
	tot = 0;
	while (m--) {
		scanf("%d%d%d", &a, &b, &w);
		addedge(b - 1, a - 1, w);
	}
	S--, T--;
	swap(S, T);
}
void solve() {
	read();
	yen();
	if (getk < K) printf("None\n");
	else ans.print();
}
int main() {
	while (scanf("%d%d%d%d%d", &n, &m, &K, &S, &T) && n)
		solve();
	return 0;
}