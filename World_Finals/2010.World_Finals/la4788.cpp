// 2010 World Finals: Castles
// ACM-ICPC Live Archive 4788

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
int def[N], die[N], req[N], n;
typedef long long LL;
LL dp[N], lost[N];
struct EDGE {
	int x, next;
};
struct NODE {
	LL lost, min;
	bool operator<(const NODE &n) const {
		return min - lost > n.min - n.lost;
	}
};
 
int G[N], tot;
EDGE E[N * 2];
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
void dfs(int x, int fa) {
	LL ret = 0;
	int i, son = 0;
	NODE tmp[N];
	lost[x] = def[x] + die[x];
 
	for (i = G[x]; ~i; i = E[i].next) {
		if (E[i].x == fa)
			continue;
		dfs(E[i].x, x);
		lost[x] += lost[E[i].x];
		tmp[son].lost = lost[E[i].x], tmp[son].min = dp[E[i].x];
		son++;
	}
	if (son == 0) {
		dp[x] = max((LL) req[x], lost[x]);
		return;
	}
	sort(tmp, tmp + son);
	ret = max(tmp[son - 1].min, tmp[son - 1].lost);
	for (i = son - 2; i >= 0; i--) {
		ret += tmp[i].lost;
		ret = max(ret, tmp[i].min);
	}
	ret += die[x] + def[x];
	ret = max(ret, (LL) req[x]);
	dp[x] = ret;
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n) {
		int a, b, i;
		LL ans = 1LL << 60LL;
		for (i = 0; i < n; i++)
			scanf("%d%d%d", &req[i], &die[i], &def[i]);
		memset(G, -1, sizeof(G));
		tot = 0;
		for (i = 0; i < n - 1; i++) {
			scanf("%d%d", &a, &b);
			addedge(a - 1, b - 1);
			addedge(b - 1, a - 1);
		}
		for (i = 0; i < n; i++) {
			dfs(i, -1);
			ans = min(ans, dp[i]);
		}
		printf("Case %d: %lld\n", ca++, ans);
	}
}
