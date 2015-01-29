// 2007 Tokyo: The Teacher’s Side of Math
// POJ 3526
// ACM-ICPC Live Archive 3891
// Aizu OJ 1284
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 250
#define RANGE 25
int a, m, b, n;
double c[RANGE][RANGE], mn[N][RANGE], x[RANGE];
int add[N][N];

double fixZero(double x){
	if (fabs(x) < 1e-5)
		return 0;
	return x;
}
int gauss(int var, int equ) {
	int i, j, k, row, col;
	for (k = col = 0; k < equ && col < var; k++, col++) {
		row = k;
		for (i = k + 1; i < equ; i++)
			if (fabs(mn[i][col]) > fabs(mn[row][col])) row = i;
		if (k != row) for (i = k; i <= var; i++)
			swap(mn[k][i], mn[row][i]);
		if (mn[k][col] == 0) {
			k--;
			continue;
		}
		for (i = k + 1; i < equ; i++)
			if (mn[i][col]) {
				double tmp = mn[i][col] / mn[k][col];
				for (j = col; j <= var; j++)
					mn[i][j] -= tmp * mn[k][j];
			}
	}
	for (i = k; i < equ; i++)
		if (mn[i][col]) return -1;
	if (var - k) return var - k;
	for (i = var - 1; i >= 0; i--) {
		x[i] = mn[i][var];
		for (j = i + 1; j < var; j++)
			x[i] -= mn[i][j] * x[j];
		x[i] /= mn[i][i];
	}
	return 0;
}

void solve(){
	memset(mn, 0, sizeof(mn));
	int var = n * m, equ = 0;
	// Assign the index of equation for coefficient of A^ma * B^mb
	for (int i = 0; i <= var; i++){
		for (int j = 0; j <= i; j++){
			int ma = i - j, mb = j;
			if (ma != 0 && ma % m == 0 || mb != 0 && mb % n == 0)
				continue;
			add[ma][mb] = equ++;
		}
	}
	// Setup the matrix of the linear equations with binomial theorem
	// x_0, x_2 ... x_mn is the coefficient of x^0, x^1 ... x^n in F(t)
	for (int i = 0; i <= var; i++){
		for (int j = 0; j <= i; j++){
			int ma = i - j, mb = j;
			int la = ma % m, lb = mb % n;
			mn[add[la][lb]][i] += pow((double)a, double(ma / m)) * pow((double)b, (double)(mb / n)) * c[i][j];
		}
	}
	// The coefficient of x^(mn) is always 1
	int gau = gauss(var, equ);
	printf("1");
	for (int i = var - 1; i >= 0; i--)
		printf(" %.0lf", fixZero(-x[i]));
	printf("\n");
}

int main() {
	c[0][0] = 1;
	for (int i = 1; i < RANGE; i++){
		c[i][0] = 1;
		for (int j = 1; j < RANGE; j++)
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
	}
	while (scanf("%d%d%d%d", &a, &m, &b, &n) && a)
		solve();
	return 0;
}

