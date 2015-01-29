// CII 4303
// 2008 Southwestern Europe: Top Secret
#include <cstdio>
#include <cstring>
#define N 1005
int n;
long long M;
 
//在循环矩阵中，取M[a,b]为M[(b-a+n)%n]
void matrix_mul(long long a[N], long long b[N]) {
	int i, j;
	long long x[N] = { 0 };
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			x[i] = (x[i] + a[j] * b[(i + n - j) % n]) % M;
	for (i = 0; i < n; i++)
		a[i] = x[i];
}
 
void matrix_power(long long a[N], long long exp) {
	long long x[N];
	int i;
	if (exp == 0) {
		for (i = 1; i < n; i++)
			a[i] = 0;
		a[0] = 1;
		return;
	}
	for (i = 0; i < n; i++)
		x[i] = a[i];
	long long tp, n = 0;
	for (tp = 1; tp <= exp; tp *= 2, n++)
		;
	for (n -= 2; n >= 0; n--) {
		matrix_mul(a, a);
		if ((1 << n) & exp) matrix_mul(a, x);
	}
}
long long in[N], mat[N];
void solve() {
	int s, l, r, x, i, j;
	scanf("%d%d%d%d%d", &n, &s, &l, &r, &x);
	for (i = 0; i < n; i++)
		scanf("%lld", &in[i]);
	M = 1;
	while (x)
		M *= 10, x--;
	memset(mat, 0, sizeof(mat));
	mat[0] = 1, mat[1] = r, mat[n - 1] = l;
	matrix_power(mat, s);
	for (i = 0; i < n; i++) {
		long long ans = 0;
		if(i)printf(" ");
		for (j = 0; j < n; j++)
			ans = (ans + mat[(j + n - i) % n] * in[j]) % M;
		printf("%lld", ans);
	}
	printf("\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
