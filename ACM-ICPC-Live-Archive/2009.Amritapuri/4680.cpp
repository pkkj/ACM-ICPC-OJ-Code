// CII 4680
// 2009 Amritapuri: Trip Compulsion
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 3005
#define INF 2000000011
struct EDGE {
	int a, b, x;
	void get() {
		scanf("%d%d%d", &a, &b, &x);
	}
	bool operator <(const EDGE &e) const {
		return x < e.x;
	}
};
int n, m, fa[N];
EDGE e[N];
void init() {
	for (int i = 0; i < n; i++)
		fa[i] = i;
}
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
void solve() {
	int s, t, i, j, ans = INF;
	scanf("%d%d", &n, &m);
	scanf("%d%d", &s, &t);
	for (i = 0; i < m; i++)
		e[i].get();
	sort(e, e + m);
	for (i = 0; i < m; i++) {
		init();
		for (j = i; j < m && find(s) != find(t); j++)
			fa[find(e[j].a)] = find(e[j].b);
		if (find(s) == find(t)) ans = min(e[j-1].x - e[i].x, ans);
	}
	if (ans == INF) printf("NO PATH\n");
	else printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
