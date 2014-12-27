// CII 5070
// 2010 Tokyo: Awkward Lights
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 650
#define M 26
int mm[N][N], st[M][M];
int dx[] = { 1, 1, -1, -1 };
int dy[] = { 1, -1, -1, 1 };
 
int gauss(int var, int equ) {
	int i, j, k, row, col;
	for (k = col = 0; k < equ && col < var; k++, col++) {
		row = k;
		for (i = k; i < equ; i++)
			if (mm[i][col]) {
				row = i;
				break;
			}
		if (k != row) for (i = k; i <= var; i++)
			swap(mm[k][i], mm[row][i]);
		if (mm[k][col] == 0) {
			k--;
			continue;
		}
		for (i = k + 1; i < equ; i++)
			if (mm[i][col])
				for (j = col; j <= var; j++)
					mm[i][j] = (mm[i][j] ^ mm[k][j]) & 1;
	}
	for (i = k; i < equ; i++)
		if (mm[i][col]) return 0;
	return 1;
}
 
int main() {
	int n, m, d, i, j, k;
	while (scanf("%d%d%d", &m, &n, &d) && n) {
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++)
				scanf("%d", &st[i][j]);
		memset(mm, 0, sizeof(mm));
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++) {
				int x = i * m + j, y;
				mm[x][x] = 1;
				mm[x][n * m] = st[i][j];
				for (int dir = 0; dir < 4; dir++) {
					for (k = 0; k <= d; k++) {
						int cx = i + dx[dir] * (d - k);
						int cy = j + dy[dir] * k;
						if (cx < 0 || cy < 0 || cx >= n || cy >= m) continue;
						y = cx * m + cy;
						mm[x][y] = 1;
					}
				}
			}
		printf("%d\n", gauss(n * m, n * m));
 
	}
 
}
