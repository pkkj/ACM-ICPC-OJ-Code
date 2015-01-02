// CII 4296
// 2008 Southwestern Europe: Bring Your Own Horse 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 3005
#define M 100005
struct EDGE {
	int a, b, w;
	bool operator <(const EDGE &e) const {
		return w < e.w;
	}
};
struct NODE {
	int b, w;
	NODE() {
	}
	NODE(int b, int w) :
		b(b), w(w) {
	}
};
int fa[N];
void inits(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i;
}
 
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
 
void uniset(int a, int b) {
	a = find(a), b = find(b);
	fa[a] = b;
}
EDGE el[M];
vector<NODE> G[N];
int ans, t;
int dfs(int fa, int x, int best) {
	if (x == t) {
		ans = best;
		return 1;
	}
	for (int i = 0; i < (int) G[x].size(); i++) {
		if (G[x][i].b == fa) continue;
		if (dfs(x, G[x][i].b, max(best, G[x][i].w))) return 1;
	}
	return 0;
}
void solve() {
	int n, m, i, ss = 1;
	scanf("%d%d", &n, &m);
	inits(n);
	for (i = 0; i < m; i++) {
		scanf("%d%d%d", &el[i].a, &el[i].b, &el[i].w);
	}
	sort(el, el + m);
	i = 0;
	memset(G, 0, sizeof(G));
	while (ss < n) {
		int a = el[i].a, b = el[i].b;
		if (find(a) != find(b)) {
			ss++;
			uniset(a, b);
			G[a].push_back(NODE(b, el[i].w));
			G[b].push_back(NODE(a, el[i].w));
		}
		i++;
	}
	int Q;
	scanf("%d", &Q);
	while (Q--) {
		int a, b;
		scanf("%d%d", &a, &b);
		t = b, ans = 0;
		dfs(-1, a, 0);
		printf("%d", ans);
		if(Q)
			printf("\n");
	}
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d\n", ca++);
		solve();
		printf("\n\n");
	}
	return 0;
}
