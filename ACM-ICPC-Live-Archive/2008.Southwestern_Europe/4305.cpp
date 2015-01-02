// CII 4305
// 2008 Southwestern Europe: Wizards
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 25
double xi[N], da[N];
double mm[N][N];
#define EPS 1e-8
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
int gauss(int var, int equ) {
	int i, j, k, row, col;
	for (k = col = 0; k < equ && col < var; col++) {
		row = k;
		for (i = k + 1; i < equ; i++)
			if (fabs(mm[i][col]) > fabs(mm[row][col])) row = i;
		if (k != row) for (i = k; i < var; i++)
			swap(mm[k][i], mm[row][i]);
		if (sgn(mm[k][col]) == 0) return 1;
		for (i = k + 1; i < equ; i++)
			if (sgn(mm[i][col])) {
				double tmp = mm[i][col] / mm[k][col];
				for (j = col; j < var; j++)
					mm[i][j] -= tmp * mm[k][j];
			}
		k++;
	}
	return 0;
}
void solve() {
	int n, i, j, k, sz;
	scanf("%d", &n);
	for (i = n; i >= 0; i--)
		scanf("%lf", &xi[i]);
 
	for (i = 0; i < n; i++) {
		da[i] = (i + 1) * xi[i + 1];
	}
	memset(mm, 0, sizeof(mm));
	sz = n + n - 1;
	for (i = 0; i < n - 1; i++)
		for (j = 0, k = n; j < n + 1; j++, k--)
			mm[i][i + j] = xi[k];
	for (i = 0; i < n; i++)
		for (j = 0, k = n - 1; j < n; j++, k--)
			mm[i + n - 1][i + j] = da[k];
	if (!gauss(sz, sz)) printf("Yes!\n");
	else printf("No!\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
