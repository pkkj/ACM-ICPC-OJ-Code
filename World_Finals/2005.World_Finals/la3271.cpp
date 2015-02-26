// 2005 World Finals: The Traveling Judges Problem
// ACM-ICPC Live Archive 3271

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 25
#define INF 1<<29
int nc, dc, nr, np;
int G[N][N], peo[N];
int T[N][2], bestT[N][2];
vector<int> ans;
int best;
void prim(int sel) {
	int sum = 0, i, j, n = 0, pt[N], dist[N], next, mm, pre[N];
	bool v[N] = { 0 };
	memset(T, 0, sizeof(T));
	for (i = 0; i < nc; i++) {
		if ((1 << i) & sel) pt[n++] = i;
	}
	for (i = 0; i < n; i++)
		dist[pt[i]] = G[dc][pt[i]], pre[i] = dc;
	v[dc] = 1;
	for (i = 0; i < n - 1; i++) {
		mm = INF, next = -1;
		for (j = 0; j < n; j++)
			if (!v[pt[j]] && dist[pt[j]] < mm) next = pt[j], mm = dist[pt[j]];
		v[next] = 1;
		T[i][0] = next, T[i][1] = pre[next];
		sum += mm;
		for (j = 0; j < n; j++) {
			if (!v[pt[j]] && G[next][pt[j]] < dist[pt[j]]) dist[pt[j]] = G[next][pt[j]], pre[pt[j]] = next;
		}
	}
	if (sum > best || (sum == best && n > (int) ans.size())) return;
	if (sum == best)
		for (i = 0; i < n; i++) {
			if (pt[i] != ans[i]) {
				if (pt[i] > ans[i]) return;
				break;
			}
	}
	ans.clear();
	for (i = 0; i < n; i++)
		ans.push_back(pt[i]);
	best = sum;
	memcpy(bestT, T, sizeof(bestT));
}
vector<int> path[N];
int curp;
bool dfs(int x, int fa) {
	int i, next;
	if (x == dc) {
		path[curp].push_back(x);
		return 1;
	}
	for (i = 0; i < nr; i++) {
		if (bestT[i][0] == x) next = bestT[i][1];
		else if (bestT[i][1] == x) next = bestT[i][0];
		else continue;
		if (next != fa) if (dfs(next, x)) {
			path[curp].push_back(x);
			return 1;
		}
	}
	return 0;
}
void solve() {
	int a, b, x, i, j, cnt;
	scanf("%d%d", &dc, &nr);
	dc--;
	for (i = 0; i < nc; i++)
		for (j = 0; j < nc; j++)
			G[i][j] = INF;
	while (nr--) {
		scanf("%d%d%d", &a, &b, &x);
		a--, b--;
		G[a][b] = G[b][a] = x;
	}
	scanf("%d", &np);
	for (i = 0; i < np; i++) {
		scanf("%d", &peo[i]);
		peo[i]--;
		path[i].clear();
	}
	cnt = 1 << nc;
	best = INF;
	for (i = 1; i < cnt; i++) {
		if (!((1 << dc) & i)) continue;
		int ok = 1;
		for (j = 0; j < np && ok; j++)
			if (!((1 << peo[j]) & i)) ok = 0;
		if (ok) {
			prim(i);
		}
	}
	nr = (int) ans.size() - 1;
	for (i = 0; i < np; i++) {
		curp = i;
		dfs(peo[i], -1);
	}
	printf("%d\n", best);
	for (i = 0; i < np; i++) {
		int st = 1;
		printf("   ");
		for (j = (int) path[i].size()- 1; j >=0 ; j--) {
			if (st) st = 0;
			else printf("-");
			printf("%d", path[i][j]+1);
		}
		printf("\n");
	}
	printf("\n");
}
int main() {
	int ca = 1;
	while (scanf("%d", &nc) && nc != -1) {
		printf("Case %d: distance = ", ca++);
		solve();
	}
	return 0;
}