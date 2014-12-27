// CII 5069
// 2010 Tokyo: Towns along a Highway
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
 
#define N 405
#define M 25
int d[N], has[N], n, total;
int dis[M][M];
set<vector<int> > ans;
int adddis(int sub[], int ndis, int &sz, int a, int b) {
	if (!has[ndis]) return 0;
	dis[a][b] = dis[b][a] = ndis;
	has[ndis]--;
	sub[sz++] = ndis;
	return 1;
}
void dfs(int l, int r) {
	int cur, i, sz, ok, sub[N];
	if (l == r - 1) {
		vector<int> tans;
		for (i = 1; i < n; i++)
			tans.push_back(dis[i][i + 1]);
		ans.insert(tans);
		return;
	}
	for (cur = d[0] - 1;; cur--)
		if (has[cur]) break;
 
	// PUT THE GAP IN THE LEFT
	ok = 1;
	sz = 0;
	for (i = 1; ok && i <= l; i++)
		if (!adddis(sub, d[0] - cur - dis[1][i], sz, i, l + 1)) ok = 0;
	for (i = r; ok && i <= n; i++)
		if (!adddis(sub, cur - dis[i][n], sz, l + 1, i)) ok = 0;
	if (ok) dfs(l + 1, r);
	for (i = 0; i < sz; i++)
		has[sub[i]]++;
 
	// PUT THE GAP IN THE RIGHT
	ok = 1;
	sz = 0;
	for (i = 1; ok && i <= l; i++)
		if (!adddis(sub, cur - dis[1][i], sz, i, r - 1)) ok = 0;
	for (i = r; ok && i <= n; i++)
		if (!adddis(sub, d[0] - cur - dis[i][n], sz, i, r - 1)) ok = 0;
	if (ok) dfs(l, r - 1);
	for (i = 0; i < sz; i++)
		has[sub[i]]++;
 
}
void solve() {
	int i;
	memset(has, 0, sizeof(has));
	memset(dis, 0, sizeof(dis));
	total = n * (n - 1) / 2;
	for (i = 0; i < total; i++) {
		scanf("%d", d + i);
		has[d[i]]++;
	}
	dis[1][n] = dis[n][1] = d[0];
	ans.clear();
	dfs(1, n);
	for (set<vector<int> >::iterator it = ans.begin(); it != ans.end(); it++) {
		for (i = 0; i < it->size(); i++) {
			if (i) printf(" ");
			printf("%d", (*it)[i]);
		}
		printf("\n");
	}
	printf("-----\n");
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
