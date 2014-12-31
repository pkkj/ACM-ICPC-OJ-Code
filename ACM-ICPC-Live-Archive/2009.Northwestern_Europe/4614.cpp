// CII 4614
// 2009 Northwestern Europe: Moving to Nuremberg
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50005
struct EDGE {
	int b, w, next;
};
EDGE E[N * 2];
int G[N], tot, ff[N];
void addedge(int a, int b, int w) {
	EDGE e = { b, w, G[a] };
	G[a] = tot;
	E[tot++] = e;
}
long long up[N], down[N], cup[N], cdown[N];
void dfs1(int x, int fa) {
	down[x] = 0, cdown[x] = ff[x];
	for (int i = G[x]; ~i; i = E[i].next) {
		if (E[i].b == fa) continue;
		dfs1(E[i].b, x);
		down[x] += down[E[i].b] + cdown[E[i].b] * E[i].w;
		cdown[x] += cdown[E[i].b];
	}
}
void dfs2(int x, int fa, int e) {
	if (x == 1) cup[x] = up[x] = 0;
	else {
		cup[x] = cup[fa] + cdown[fa] - cdown[x];
		up[x] = up[fa] + down[fa] - down[x] - cdown[x] * e + cup[x] * e;
	}
	for (int i = G[x]; ~i; i = E[i].next) {
		if (E[i].b == fa) continue;
		dfs2(E[i].b, x, E[i].w);
	}
}
void solve() {
	int i, n, a, b, w;
	long long best;
	memset(G, -1, sizeof(G));
	memset(ff, 0, sizeof(ff));
	tot = 0;
	scanf("%d", &n);
	for (i = 0; i < n - 1; i++) {
		scanf("%d%d%d", &a, &b, &w);
		addedge(a, b, w);
		addedge(b, a, w);
	}
	scanf("%d", &w);
	while (w--) {
		scanf("%d", &a);
		scanf("%d", &ff[a]);
	}
	cup[0] = cdown[0] = 0;
	dfs1(1, 0);
	dfs2(1, 0, 0);
	best = 1LL << 60LL;
	for (i = 1; i <= n; i++)
		best = min(best, down[i] + up[i]);
	printf("%lld\n", best * 2);
	int st = 1;
	for (i = 1; i <= n; i++)
		if (down[i] + up[i] == best) {
			if (st) st = 0;
			else printf(" ");
			printf("%d", i);
		}
	printf("\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
