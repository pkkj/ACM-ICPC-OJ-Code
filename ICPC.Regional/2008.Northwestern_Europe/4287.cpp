// 2008 Northwestern Europe: Proving Equivalences
// ACM-ICPC Live Archive 4287 
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20005
#define M 50005
struct EDGE {
	int b, next;
};
EDGE ET[M * 4];
int GA[N], GD[N], tot, pos[N];
 
inline void addedge(int *g, int s, int t) {
	EDGE x = { t, *(g + s) };
	ET[tot] = x;
	*(g + s) = tot++;
}
 
inline void add(int s, int t) {
	addedge(GA, s, t), addedge(GD, t, s);
}
 
int color[N], v[N], block[N], pp, n, outd[N], ind[N];
 
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
	int i, nblock = 0, in0 = 0, out0 = 0, n, m, a, b;
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
	if (nblock == 1) {
		printf("0\n");
		return;
	}
	for (i = 1; i <= n; i++)
		if (block[i] != i) for (int p = GA[i]; p != -1; p = ET[p].next)
			addedge(GA, block[i], block[ET[p].b]);
	memset(ind, 0, sizeof(ind));
	memset(outd, 0, sizeof(outd));
	for (i = 1; i <= n; i++)
		if (block[i] == i) for (int p = GA[i]; p != -1; p = ET[p].next)
			if (block[ET[p].b] != i) outd[i]++, ind[block[ET[p].b]]++;
 
	for (i = 1; i <= n; i++)
		if (block[i] == i) in0 += !ind[i], out0 += !outd[i];
	printf("%d\n", max(in0, out0));
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}