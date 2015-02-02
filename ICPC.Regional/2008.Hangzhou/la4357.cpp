// 2008 Hangzhou: Get-Together at Stockholm
// ACM-ICPC Live Archive 4357
#include <cstdio>
#include <cstring>
#define N 105
bool g[N][N];
int n, m, a, b, ans, v[N];
int find() {
	int i, j;
	for (i = 0; i < n; i++) {
		int ta = 0, tb = 0;
		if (v[i]) continue;
		for (j = 0; j < n; j++)
			if (!v[j] && i != j) ta += g[i][j], tb += !g[i][j];
		if (ta < a || tb < b) return i;
	}
	return -1;
}
 
void del(int x) {
	ans--, v[x] = 1;
	for (int i = 0; i < n; i++)
		g[x][i] = g[i][x] = 0;
}
void solve() {
	int x;
	memset(g, 0, sizeof(g));
	memset(v, 0, sizeof(v));
	while (m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}
	ans = n;
	while ((x = find()) != -1)
		del(x);
	printf("%d\n", ans);
 
}
int main() {
	int T = 0;
	while (scanf("%d%d%d%d", &n, &m, &a, &b) && n) {
		printf("Case #%d: ", ++T);
		solve();
	}
	return 0;
}