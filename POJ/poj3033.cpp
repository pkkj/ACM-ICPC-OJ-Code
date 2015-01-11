// POJ 3033
// Nordic 2006: Traveling Salesman
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
// Graph
#define NG 6006
struct EDGE {
	int b, next;
};
EDGE E[NG * 1000];
int G[NG], tot;
 
void addedge(int x, int y) {
	EDGE e = { y, G[x] };
	G[x] = tot;
	E[tot++] = e;
}
// End of graph
// Hash table
#define M 100000
const long long BP = 1011LL;
const long long BP2 = BP * BP;
const long long BP3 = BP * BP * BP;
struct HNODE {
	int x1, y1, z1, x2, y2, z2, next;
	vector<int> G;
};
HNODE HE[M];
int HG[M], htot;
typedef long long ll;
void insert(int x1, int y1, int z1, int x2, int y2, int z2, int id) {
	long long p;
	int i, j;
	ll ax1 = abs(x1), ay1 = abs(y1), az1 = abs(z1);
	ll ax2 = abs(x2), ay2 = abs(y2), az2 = abs(z2);
	p = ((ax1 + ay1 * BP + az1 * BP2) % M + (ax2 * BP2 % M + ay2 * BP3 + az2 * BP3) % M + M) % M;
	for (i = HG[p]; ~i; i = HE[i].next) {
		if (HE[i].x1 == x1 && HE[i].y1 == y1 && HE[i].z1 == z1 && HE[i].x2 == x2 && HE[i].y2 == y2 && HE[i].z2 == z2) {
			for (j = 0; j < (int) HE[i].G.size(); j++) {
				addedge(id, HE[i].G[j]);
				addedge(HE[i].G[j], id);
			}
			HE[i].G.push_back(id);
			return;
		}
	}
	HNODE e = { x1, y1, z1, x2, y2, z2, HG[p] };
	e.G.clear();
	e.G.push_back(id);
	HE[htot] = e;
	HG[p] = htot++;
}
 
void hinit() {
	htot = 0;
	memset(HG, -1, sizeof(HG));
}
// End of hash table
 
struct POINT {
	int x, y, z;
	void get() {
		scanf("%d%d%d", &x, &y, &z);
	}
	void print() {
		printf("%d %d %d\n", x, y, z);
	}
	bool operator <(const POINT &p) const {
		if (x != p.x) return x < p.x;
		if (y != p.y) return y < p.y;
		return z < p.z;
	}
};
int n;
bool vis[NG];
int Q[NG * 2];
int bfs(int st, int end) {
	int step = 0, ind = 1, qh, qe, next, i;
	memset(vis, 0, sizeof(vis));
	qh = qe = 0;
	Q[qe++] = st;
	vis[st] = 1;
	while (qh < qe) {
		next = 0;
		while (ind--) {
			int top = Q[qh++];
			if (top == end) return step;
			for (i = G[top]; ~i; i = E[i].next) {
				if (vis[E[i].b] == 0) {
					Q[qe++] = E[i].b;
					next++;
					vis[E[i].b] = 1;
				}
			}
		}
		ind = next, step++;
	}
	return -1;
}
void solve() {
	int i, j, m;
	POINT p0, pp, cp, a, b;
	memset(G, -1, sizeof(G));
	tot = 0;
	hinit();
	for (i = 0; i < n; i++) {
		scanf("%d", &m);
		for (j = 0; j < m; j++) {
			cp.get();
			a = cp, b = pp;
			if (b < a) swap(a, b);
			if (j > 0) {
				insert(a.x, a.y, a.z, b.x, b.y, b.z, i);
			} else p0 = cp;
			pp = cp;
		}
		a = p0, b = cp;
		if (b < a) swap(a, b);
		insert(a.x, a.y, a.z, b.x, b.y, b.z, i);
	}
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d", &i, &j);
		printf("%d\n", bfs(i - 1, j - 1));
	}
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
