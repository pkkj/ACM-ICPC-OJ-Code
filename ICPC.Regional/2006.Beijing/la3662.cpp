// 2006 Beijing:  Another Minimum Spanning Tree
// ACM-ICPC Live Archive 3662
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 100005
#define BIG 100000000
const int INF = 1 << 30;
struct POINT {
	int x, y;
	void get() {
		scanf("%d%d", &x, &y);
	}
	void print() {
		printf("%d %d\n", x, y);
	}
	POINT() {
	}
	POINT(int x, int y) :
		x(x), y(y) {
	}
};
 
POINT P[N];
int n, m;
int dis(int a, int b) {
	return abs(P[a].x - P[b].x) + abs(P[a].y - P[b].y);
}
// Kruskal MST
struct EDGE {
	int x, y, w;
	EDGE() {
	}
	EDGE(int x, int y, int w) :
		x(x), y(y), w(w) {
	}
	bool operator <(const EDGE &e) const {
		return w < e.w;
	}
};
EDGE E[N * 10];
int fa[N];
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
long long kruskal() {
	int i, link = 1;
	long long ans = 0;
	sort(E, E + m);
	for (i = 0; i <= n; i++)
		fa[i] = i;
	for (i = 0; i < m && link < n; i++) {
		int x = E[i].x, y = E[i].y;
		x = find(x), y = find(y);
		if (x == y) continue;
		fa[x] = y;
		link++;
		ans += E[i].w;
	}
	return ans;
}
// End of Kruskal
// Sort and query, get all the edges in 45 degree
struct NODE {
	int v, p, l, r;
};
NODE T[N * 5];
int idx[N], yy[N], ny[N];
inline bool cmp(int i, int j) {
	int v1 = P[i].y - P[i].x;
	int v2 = P[j].y - P[j].x;
	if (v1 == v2) return ny[i] > ny[j];
	return v1 < v2;
}
void build(int p, int l, int r) {
	T[p].l = l, T[p].r = r, T[p].v = INF, T[p].p = -1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build((p << 1) | 1, mid + 1, r);
}
void insert(int p, int i) {
	if (ny[i] < T[p].l || ny[i] > T[p].r) return;
	if (P[i].x + P[i].y < T[p].v) {
		T[p].v = P[i].x + P[i].y;
		T[p].p = i;
	}
	if (T[p].l == T[p].r) return;
	insert(p << 1, i);
	insert((p << 1) | 1, i);
}
struct ANS {
	int v, p;
	ANS() {
	}
	ANS(int v, int p) :
		v(v), p(p) {
	}
	bool operator <(const ANS &a) const {
		return v < a.v;
	}
};
ANS query(int p, int i) {
	if (T[p].r < ny[i]) return ANS(INF, -1);
	if (ny[i] <= T[p].l) return ANS(T[p].v, T[p].p);
	return min(query(p << 1, i), query((p << 1) | 1, i));
}
 
void make() {
	int i, tot;
	for (i = 0; i < n; i++)
		idx[i] = i, yy[i] = P[i].y;
	sort(yy, yy + n);
	tot = unique(yy, yy + n) - yy;
	for (i = 0; i < n; i++)
		ny[i] = lower_bound(yy, yy + tot, P[i].y) - yy;
	sort(idx, idx + n, cmp);
	build(1, 0, tot + 1);
	for (i = 0; i < n; i++) {
		ANS a = query(1, idx[i]);
		if (a.p != -1) E[m++] = EDGE(idx[i], a.p, dis(idx[i], a.p));
		insert(1, idx[i]);
	}
}
void solve() {
	int i, j;
	for (i = 0; i < n; i++)
		P[i].get();
	m = 0;
	for (i = 0; i < 4; i++) {
		if (i > 0) {
			for (j = 0; j < n; j++) {
				int x = -P[j].y, y = P[j].x;
				if (i == 2) swap(x, y);
				P[j] = POINT(x, y);
			}
		}
		make();
	}
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		solve();
		printf("Case %d: Total Weight = %lld\n", T++, kruskal());
	}
	return 0;
}