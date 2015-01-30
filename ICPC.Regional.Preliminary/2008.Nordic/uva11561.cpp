// 2008 Nordic: Getting Gold
// UVA 11561
#include <cstdio>
#include <cstring>
#define N 60
 
char map[N][N];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
struct NODE {
	int x, y;
	NODE() {
	}
	NODE(int x, int y) :
		x(x), y(y) {
	}
};
NODE Q[N * N * 2];
bool vis[N][N];
int main() {
	int i, w, h, j;
	while (scanf("%d%d", &w, &h) != EOF) {
		NODE st;
		for (i = 0; i < h; i++) {
			scanf("%s", map[i]);
			for (j = 0; j < w; j++)
				if (map[i][j] == 'P') st = NODE(i, j);
		}
		int ans = 0, qh = 0, qe = 0;
		Q[qe++] = st;
		memset(vis, 0, sizeof(vis));
		vis[st.x][st.y] = 0;
		while (qh < qe) {
			NODE top = Q[qh++];
			if (map[top.x][top.y] == 'G') ans++;
			int ok = 1, nx, ny;
			for (i = 0; i < 4; i++) {
				nx = top.x + dx[i], ny = top.y + dy[i];
				if (nx < 0 || ny < 0 || nx == h || ny == w) continue;
				if (map[nx][ny] == 'T') ok = 0;
			}
			if (ok == 0) continue;
			for (i = 0; i < 4; i++) {
				nx = top.x + dx[i], ny = top.y + dy[i];
				if (nx < 0 || ny < 0 || nx == h || ny == w) continue;
				if (!vis[nx][ny] && map[nx][ny] != '#') {
					Q[qe++] = NODE(nx, ny);
					vis[nx][ny] = 1;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}