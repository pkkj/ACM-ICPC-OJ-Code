// CII 4902
// 2010 East Central NA: Maze
#include <cstdio>
#include <cstring>
#define N 35
char map[6][N][N];
int n;
struct NODE {
	int x, y, z, d;
	NODE() {
	}
	NODE(int x, int y, int z, int d) :
		x(x), y(y), z(z), d(d) {
	}
 
};
NODE q[N * N * N];
int dis[N][N][N];
int from[N][N][N];
int dx[] = { 0, 0, 1, -1, 0, 0 };
int dy[] = { -1, 1,0, 0, 0, 0 };
int dz[] = { 0, 0, 0, 0, 1, -1 };
char ch[] = { 'F', 'B', 'L', 'R', 'U', 'D' };
void solve() {
	int i, j, qh = 0, qe = 0, step;
	char ans[N * N];
	memset(dis, -1, sizeof(dis));
	getchar();
	for (i = 0; i < 6; i++)
		for (j = 0; j < n; j++)
			gets(map[i][j]);
 
	q[qe++] = NODE(1, 1, 1, 0);
	dis[1][1][1] = 0;
	while (qh < qe) {
		NODE top = q[qh++];
		if (top.x == n - 2 && top.y == n - 2 && top.z == n - 2) break;
		for (i = 0; i < 6; i++) {
			int nx = top.x + dx[i], ny = top.y + dy[i], nz = top.z + dz[i], nd = top.d + 1;
			if (map[0][n - nz - 1][n - nx - 1] == 'X') continue;
			if (map[1][n - nz - 1][ny] == 'X') continue;
			if (map[2][n - nz - 1][nx] == 'X') continue;
			if (map[3][n - nz - 1][n - ny - 1] == 'X') continue;
			if (map[4][n - ny - 1][n - nx - 1] == 'X') continue;
			if (map[5][ny][n - nx - 1] == 'X') continue;
			if (dis[nx][ny][nz] != -1 && dis[nx][ny][nz] <= nd) continue;
			q[qe++] = NODE(nx, ny, nz, nd);
			dis[nx][ny][nz] = nd;
			from[nx][ny][nz] = i;
		}
	}
	step = dis[n - 2][n - 2][n - 2];
	int cx = n - 2, cy = n - 2, cz = n - 2;
	for (i = 0; i < step; i++) {
		int idx = from[cx][cy][cz];
		ans[i] = ch[idx];
		cx -= dx[idx], cy -= dy[idx], cz -= dz[idx];
	}
	for (i = step - 1; i >= 0; i--)
		printf("%c", ans[i]);
 
}
int main() {
	while (scanf("%d", &n) && n) {
		solve();
		printf("\n");
	}
	return 0;
}
