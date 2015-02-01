// 2008 Amritapuri: Minesweeper
// CII 4335
#include <cstdio>
#define N 25
char ch[N][N];
int n, m;
int dx[] = { 1, 1, 1, 0, 0, -1, -1, -1 };
int dy[] = { 1, 0, -1, 1, -1, 1, 0, -1 };
int calc(int x, int y) {
	int ans = 0, i;
	for (i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx == -1 || ny == -1 || nx == n || ny == m) continue;
		ans += ch[nx][ny] == 'F';
	}
	return ans;
}
bool check(int x, int y) {
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (nx == -1 || ny == -1 || nx == n || ny == m) continue;
		if (ch[nx][ny] != 'F') return 1;
	}
	return 0;
}
int solve() {
	int i, j;
	scanf("%d%d\n", &n, &m);
	for (i = 0; i < n; i++)
		scanf("%s", ch[i]);
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			if (ch[i][j] == 'F') {
				if (!check(i, j)) return 0;
			} else if (calc(i, j) != ch[i][j] - '0') return 0;
 
		}
	return 1;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		puts(solve() ? "Well done Clark!" : "Please sweep the mine again!");
	return 0;
}