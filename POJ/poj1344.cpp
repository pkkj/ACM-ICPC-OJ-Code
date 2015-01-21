// 2002 Kaohsiung: Tree Size Problem
// POJ 1344
#include <cstdio>
#include <cstring>
#define N 50
int n, D[N][N], vis[N];
void solve() {
	int ans = 0;
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			scanf("%d", &D[i][j]);

	for (int round = 0; round < n - 2; round++) {
		int minDis = 1<<30, next;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = j + 1; k < n; k++)
					if (!vis[i] && !vis[j] && !vis[k]) {
						int dis = (D[i][j] + D[i][k] - D[j][k]) / 2;
						if (dis < minDis) {
							next = i;
							minDis = dis;
						}
					}
		ans += minDis;
		vis[next] = 1;
	}

	int a = -1, b = -1;
	for (int i = 0; i < n; i++) {
		if (!vis[i])
			(a == -1) ? (a = i) : (b = i);
	}
	ans += D[a][b];
	printf("%d\n", ans);
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
}

