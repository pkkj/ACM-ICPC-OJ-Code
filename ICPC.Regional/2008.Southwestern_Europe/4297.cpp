// CII 4297
// 2008 Southwestern Europe: First Knight
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1650
int n, m;
double mm[N][N];
double gauss(int size) {
	int i, j, k;
	for (k = 0; k < size; k++) {
		for (i = k + 1; i < min(k + 1 + m, size); i++) {
			if (fabs(mm[i][k]) > 1e-12) {
				double tmp = mm[i][k] / mm[k][k];
				for (j = k; j < min(k + 1 + m, size); j++)
					mm[i][j] -= tmp * mm[k][j];
				mm[i][size] -= tmp * mm[k][size];
			}
		}
	}
	return mm[size-1][size] / mm[size-1][size-1];
}
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
double solve() {
	int i, j, k, size;
	memset(mm, 0, sizeof(mm));
	size = n * m;
	for (i = 1; i < size; i++)
		mm[i][size] = 1;
	for (k = 0; k < 4; k++)
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				int nx, ny, p1, p2;
				double p;
				scanf("%lf\n", &p);
				nx = i + dx[k], ny = j + dy[k];
				if (nx < 0 || nx == n || ny < 0 || ny == m || p == 0) continue;
				p1 = m * i + j, p2 = m * nx + ny;
				p1 = n * m - p1 - 1, p2 = n * m - p2 - 1;
				mm[p1][p2] = -p;
			}
		}
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			mm[m * i + j][m * i + j] = 1;
	return gauss(size);
}
int main() {
	while (scanf("%d%d", &n, &m) && n)
		printf("%.3lf\n", solve());
	return 0;
}
