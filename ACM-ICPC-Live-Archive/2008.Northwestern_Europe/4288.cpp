// 2008 Northwestern Europe: Cat vs. Dog
// ACM-ICPC Live Archive 4288
#include <cstdio>
#include <cstring>
#define N 505
 
struct ITEM {
	char s1[20], s2[20];
};
bool g[N][N], v[N];
int n, link[N];
ITEM il[N];
int dfs(int t) {
	int i;
	for (i = 1; i <= n; i++) {
		if (!v[i] && g[t][i]) {
			v[i] = 1;
			if (link[i] == -1 || dfs(link[i])) {
				link[i] = t;
				return 1;
			}
		}
	}
	return 0;
}
void solve() {
	int i, j, ans = 0;
	memset(g, 0, sizeof(g));
	scanf("%d%d%d", &i, &j, &n);
	for (i = 1; i <= n; i++)
		scanf("%s%s", il[i].s1, il[i].s2);
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
			if (strcmp(il[i].s1, il[j].s2) == 0 || strcmp(il[i].s2, il[j].s1) == 0) g[i][j] = g[j][i] = 1;
	memset(link, -1, sizeof(link));
	for (i = 1; i <= n; i++) {
		memset(v, 0, sizeof(v));
		ans += dfs(i);
	}
	printf("%d\n", (n * 2 - ans) / 2);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}