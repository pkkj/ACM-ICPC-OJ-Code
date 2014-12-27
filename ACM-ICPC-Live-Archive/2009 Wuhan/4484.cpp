// CII 4484
// 2009 Wuhan: Box Relations
#include <cstdio>
#include <cstring>
#define N 2005
int n, Q;
 
struct EDGE {
	int b, next;
};
 
EDGE E[100000*3];
int G[3][N], tot;
int d[3][N];
int ans[3][N];
bool vis[3][N];
void addedge(int g, int x, int y) {
	EDGE e = { y, G[g][x] };
	E[tot] = e;
	G[g][x] = tot++;
	d[g][y]++;
}
 
bool solve() {
	int x, y, i, j, k;
	char cmd[4];
	memset(G, -1, sizeof(G));
	memset(d, 0, sizeof(d));
	tot = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < 3; j++)
			addedge(j, i, i + n);
	}
 
	while (Q--) {
		scanf("%s%d%d", cmd, &x, &y);
		x--, y--;
		if (cmd[0] == 'I') {
			for (i = 0; i < 3; i++) {
				addedge(i, y, x + n);
				addedge(i, x, y + n);
			}
		} else if (cmd[0] == 'X') {
			addedge(0, x + n, y);
		} else if (cmd[0] == 'Y') {
			addedge(1, x + n, y);
		} else if (cmd[0] == 'Z') {
			addedge(2, x + n, y);
		}
	}
	memset(vis, 0, sizeof(vis));
	for (k = 0; k < 3; k++) {
		for (i = 0; i < 2 * n; i++) {
			int pt = -1;
			for (j = 0; j < 2 * n; j++) {
				if (!vis[k][j] && d[k][j] == 0) {
					pt = j;
					break;
				}
			}
			if (pt == -1) return 0;
			vis[k][pt] = 1;
			ans[k][pt] = i;
			for (j = G[k][pt]; ~j; j = E[j].next) {
				d[k][E[j].b]--;
			}
		}
 
	}
	printf("POSSIBLE\n");
	for (i = 0; i < n; i++) {
		printf("%d %d %d %d %d %d\n", ans[0][i], ans[1][i], ans[2][i], ans[0][i + n], ans[1][i + n], ans[2][i + n]);
	}
	return 1;
}
 
int main() {
	int ca = 1;
	while (scanf("%d%d", &n, &Q) && n) {
		printf("Case %d: ", ca++);
		if (!solve()) printf("IMPOSSIBLE\n");
		printf("\n");
	}
	return 0;
}
