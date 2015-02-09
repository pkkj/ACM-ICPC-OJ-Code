// 2005 Southwestern Europe: Consecutive ones
// ACM-ICPC Live Archive 3511
#include <cstdio>
#include <cstring>
#define N 405
bool map[N][N], use[N];
int cnt[N], ans[N], n, m;
void init() {
	int i, j;
	char cmd[500];
	scanf("%d\n%d\n", &n, &m);
	memset(cnt, 0, sizeof(cnt));
	memset(use, 0, sizeof(use));
	for (i = 0; i < n; i++) {
		scanf("%s", cmd);
		for (j = 0; j < m; j++) {
			bool p = cmd[j] == '1';
			map[i][j] = p;
			if (j) cnt[i] += p;
		}
	}
	ans[0] = 0;
}
int dfs(int x) {
	int i, j, ok;
	if (x == m) return 1;
	for (i = 1; i < m; i++) {
		if (use[i]) continue;
		for (j = 0, ok = 1; j < n && ok; j++)
			if (cnt[j] && !map[j][i] && map[j][ans[x - 1]]) ok = 0;
		if (!ok) continue;
		use[i] = 1, ans[x] = i;
		for (j = 0; j < n; j++)
			cnt[j] -= map[j][i];
		if (dfs(x + 1)) return 1;
		use[i] = 0;
		for (j = 0; j < n; j++)
			cnt[j] += map[j][i];
	}
	return 0;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca) printf("\n");
		init();
		dfs(1);
		for (int i = 0; i < m; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
