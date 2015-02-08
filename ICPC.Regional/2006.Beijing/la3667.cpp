// 2006 Beijing: Ruler
// ACM-ICPC Live Archive 3667
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 55
#define M 1000005
int n, a[N];
int best, ans[N], tans[N];
bool need[M];
int vis[M * 3];
int DEP, ok, cmax;
void dfs(int p, int dep, int left) {
	int i, j, k;
	if (left == 0) {
		int mm1, mm2;
		mm1 = mm2 = 0;
		for (i = 0; i < dep; i++)
			mm1 = max(mm1, tans[i]);
		if (mm1 < cmax) {
			for (i = 0; i < dep; i++)
				ans[i] = tans[i];
			cmax = mm1;
		}
		ok = 1;
	}
	if (dep == DEP) return;
	for (i = p; i < n; i++) {
		if (vis[a[i]]) continue;
		for (j = 0; j < dep; j++) {
			int pos = a[i] + tans[j];
			int nleft = left;
			for (k = 0; k < dep; k++) {
				int next = abs(pos - tans[k]);
				if (vis[next] == 0 && need[next]) {
					nleft--;
					vis[next] = dep;
				}
			}
			tans[dep] = pos;
			dfs(i, dep + 1, nleft);
			for (k = 0; k < dep; k++) {
				int next = abs(pos - tans[k]);
				if (vis[next] == dep) vis[next] = 0;
			}
		}
	}
	for (i = p; i < n; i++) {
		for (j = 0; j < dep; j++) {
			int pos = tans[j] - a[i];
			int nleft = left;
			if (pos <= 0) continue;
			for (k = 0; k < dep; k++) {
				int next = abs(pos - tans[k]);
				if (vis[next] == 0 && need[next]) {
					nleft--;
					vis[next] = dep;
				}
			}
			tans[dep] = pos;
			dfs(i, dep + 1, nleft);
			for (k = 0; k < dep; k++) {
				int next = abs(pos - tans[k]);
				if (vis[next] == dep) vis[next] = 0;
			}
		}
	}
}
void solve() {
	int i, j = 0, x;
	memset(need, 0, sizeof(need));
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		if (!need[x]) need[x] = 1, a[j++] = x;
	}
	n = j;
	tans[0] = ans[0] = 0;
	memset(vis, 0, sizeof(vis));
	ok = 0, cmax = M * 5;
	for (DEP = 2; DEP <= 7; DEP++) {
		dfs(0, 1, n);
		if (ok) break;
	}
	sort(ans, ans + DEP);
	printf("%d\n", DEP);
	for (i = 0; i < DEP; i++)
		printf("%d ", ans[i]);
	printf("\n");
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d:\n", T++);
		solve();
	}
	return 0;
}