// POJ 3532
// POJ Founder Monthly Contest – 2008.03.16: Resistance
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 105
 
double g[N][N], r[N][N], b[N];
int gauss(double mm[N][N], double x[N], int var, int equ) {
	int i, j, k, row, col;
	for (k = col = 0; k < equ && col < var; k++, col++) {
		row = k;
		for (i = k + 1; i < equ; i++)
			if (fabs(mm[i][col]) > fabs(mm[row][col])) row = i;
		if (k != row) for (i = k; i <= var; i++)
			swap(mm[k][i], mm[row][i]);
		if (mm[k][col] == 0) {
			k--;
			continue;
		}
		for (i = k + 1; i < equ; i++)
			if (mm[i][col]) {
				double tmp = mm[i][col] / mm[k][col];
				for (j = col; j <= var; j++)
					mm[i][j] -= tmp * mm[k][j];
			}
	}
	for (i = k; i < equ; i++)
		if (mm[i][col]) return -1;
	if (var - k) return var - k;
	for (i = var - 1; i >= 0; i--) {
		x[i] = mm[i][var];
		for (j = i + 1; j < var; j++)
			x[i] -= mm[i][j] * x[j];
		x[i] /= mm[i][i];
	}
	return 0;
}
int main() {
	int n, m, i, j;
	int x, y, z;
	scanf("%d %d", &n, &m);
	memset(r, 0, sizeof(r));
	memset(g, 0, sizeof(g));
	while (m--) {
		scanf("%d %d %d", &x, &y, &z);
		x--, y--;
		if (r[x][y] == 0) r[x][y] = r[y][x] = z;
		else {
			r[x][y] = r[x][y] * z / (r[x][y] + z);
			r[y][x] = r[x][y];
		}
	}
	for (i = 1; i < n - 1; ++i)
		for (j = 0; j < n; j++) {
			if (i != j && r[i][j] != 0) {
				g[i][j] += 1.0 / r[i][j];
				g[i][i] -= 1.0 / r[i][j];
			}
		}
	g[0][0] = g[n - 1][n - 1] = g[0][n] = 1;
	gauss(g, b, n, n);
	double sum = 0.0;
	for (i = 1; i < n; i++)
		if (r[0][i]) sum += (b[0] - b[i]) / r[0][i];
	printf("%.2lf\n", b[0] / sum);
	return 0;
}
