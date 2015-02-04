// CII 4769
// 2009 Harbin: Fuzzy Google Suggest
#include <cstdio>
#include <cstring>
#define N 1100005
 
int child[N][26], cnt[N];
short vis[N];
int n, tot, len;
char ss[20];
void insert() {
	int x = 1, y, j = 0;
	cnt[x]++;
	while (ss[j]) {
		y = ss[j] - 'a';
		if (child[x][y] == -1) child[x][y] = tot++;
		x = child[x][y];
		cnt[x]++;
		j++;
	}
}
 
int dfs(int x, int p, int ed) {
	if (vis[x] == 2) return 1;
	if (ed == -1) return 0;
	if (p == len) {
		vis[x] = 2;
		return 1;
	}
	if (child[x][ss[p] - 'a'] != -1) {
		if (dfs(child[x][ss[p] - 'a'], p + 1, ed)) vis[x] = 1; // Nothing change
	}
	for (int i = 0; i < 26; i++) {
		int cur = ss[p] - 'a';
		if (i == cur || child[x][i] == -1) continue;
		if (dfs(child[x][i], p + 1, ed - 1)) vis[x] = 1; // Change a letter
		if (dfs(child[x][i], p, ed - 1)) vis[x] = 1; // Add a letter
	}
	if (dfs(x, p + 1, ed - 1)) if (vis[x] == 0) vis[x] = 1; // Delete a letter, should check vis first because it maybe 2, the end of a matched node
	return vis[x];
}
 
int dfs2(int x) {
	int ans = 0;
	if (vis[x] == 2) {
		return cnt[x];
	}
	for (int i = 0; i < 26; i++)
		if (vis[child[x][i]]) ans += dfs2(child[x][i]);
	return ans;
}

void solve() {
	int i, ed, Q;
	tot = 2;
	memset(child, -1, sizeof(child));
	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < n; i++) {
		scanf("%s", ss);
		insert();
	}
	scanf("%d", &Q);
	while (Q--) {
		memset(vis, 0, sizeof(vis));
		scanf("%s%d", ss, &ed);
		len = strlen(ss);
		dfs(1, 0, ed);
		printf("%d\n", dfs2(1));
	}
}
int main() {
	while (scanf("%d", &n) != EOF)
		solve();
	return 0;
}
