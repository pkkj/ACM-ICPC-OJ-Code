// CII 4302
// 2008 Southwestern Europe: Toll Road
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 200005
int dp[N];
struct NODE {
	int b, v;
	NODE() {
	}
	NODE(int b, int v) :
		b(b), v(v) {
	}
};
vector<NODE> G[N];
int n, s, ans = 0;
int v[N];
void dfs1(int x, int d) {
	v[x] = d;
	for (int i = 0; i < (int) G[x].size(); i++)
		if (!v[G[x][i].b]) dfs1(G[x][i].b, d + 1);
}
 
void dfs2(int x) {
	int i;
	dp[x] = 0;
	for (i = 0; i < G[x].size(); i++) {
		if (v[x] > v[G[x][i].b]) continue;
		dfs2(G[x][i].b);
		if (dp[G[x][i].b] + G[x][i].v > 0) dp[x] += dp[G[x][i].b] + G[x][i].v;
	}
	ans = max(ans, dp[x]);
}
void solve() {
	s = -1;
	memset(G, 0, sizeof(G));
	while (n--) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		if (s == -1) s = a;
		G[a].push_back(NODE(b, w));
		G[b].push_back(NODE(a, w));
	}
	memset(v, 0, sizeof(v));
	dfs1(s, 1);
	ans = 0;
	dfs2(s);
	printf("%d\n", ans);
}
 
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
