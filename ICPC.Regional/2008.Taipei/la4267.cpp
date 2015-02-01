// 2008 Taipei: Finding The Heaviest Path
// CII 4267
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 10005
 
int w[N], size[N];
long long cnt[N], sum;
struct EDGE {
	int b, next;
};
int G[N], tot, ans[N], len;
EDGE E[N * 2];
 
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
void dfs1(int x, int fa) {
	int i, j;
	cnt[x] = w[x], size[x] = 1;
	for (i = G[x]; ~i; i = E[i].next) {
		j = E[i].b;
		if (j != fa) {
			dfs1(j, x);
			cnt[x] += cnt[j], size[x] += size[j];
		}
	}
}
 
void dfs2(int x, int fa) {
	sum += w[x];
	ans[len++] = x;
	int i, j, pos = -1, sz = -1;
	long long big = -1;
	for (i = G[x]; ~i; i = E[i].next) {
		j = E[i].b;
		if (j != fa) {
			if (cnt[j] > big || cnt[j] == big && size[i] > sz) big = cnt[j], sz = size[j], pos = j;
		}
	}
	if (pos != -1) dfs2(pos, x);
}
void solve() {
	int n, root, i, j, x, m, st;
	scanf("%d%d", &n, &root);
	tot = 0;
	memset(G, -1, sizeof(G));
	for (i = 0; i < n; i++) {
		scanf("%d%d", &w[i], &m);
		for (j = 0; j < m; j++) {
			scanf("%d", &x);
			addedge(i, x);
			addedge(x, i);
		}
	}
	dfs1(root, -1);
	len = 0, sum = 0;
	dfs2(root, -1);
	printf("%lld\n", sum);
	st = 1;
	for (i = 0; i < len; i++) {
		if (st) st = 0;
		else printf(" ");
		printf("%d", ans[i]);
		if ((i + 1) % 10 == 0 && i + 1 != len) {
			printf("\n");
			st = 1;
		}
	}
 
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		solve();
		printf("\n");
	}
	return 0;
}