// 2008 Taipei: Road Networks
// CII 4262
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1005
struct EDGE {
	int b, next;
};
EDGE ET[700005];
int GA[N], GD[N], tot, pos[N];
 
inline void addedge(int *g, int s, int t) {
	EDGE x = { t, *(g + s) };
	ET[tot] = x;
	*(g + s) = tot++;
}
 
inline void add(int s, int t) {
	addedge(GA, s, t), addedge(GD, t, s);
}
 
int color[N], v[N], block[N], pp;
void dfs1(int x) {
	v[x] = 1;
	for (int i = GA[x]; i != -1; i = ET[i].next)
		if (!v[ET[i].b]) dfs1(ET[i].b);
	pos[pp++] = x;
}
void dfs2(int x, int id) {
	v[x] = 0, block[x] = id;
	for (int i = GD[x]; i != -1; i = ET[i].next)
		if (v[ET[i].b]) dfs2(ET[i].b, id);
}
void solve() {
	int i, nblock = 0, n, m, a, b;
	memset(GA, -1, sizeof(GA));
	memset(GD, -1, sizeof(GD));
	tot = 0;
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &a, &b);
		add(a, b);
	}
	pp = 1;
	memset(v, 0, sizeof(v));
	for (i = 1; i <= n; i++)
		if (!v[i]) dfs1(i);
	for (i = n; i >= 1; i--)
		if (v[pos[i]]) dfs2(pos[i], pos[i]), nblock++;
	printf("%d\n", nblock);
}
 
int main() {
	int T, x;
	scanf("%d", &T);
	while (T--) {
		solve();
		scanf("%d", &x);
	}
	return 0;
}