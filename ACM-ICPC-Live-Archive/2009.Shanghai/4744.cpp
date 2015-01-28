// 2009 Shanghai: Brute-force Algorithm
// ACM-ICPC Live Archive 4744
#include <cstdio>
#include <cstring>
#define N 2
typedef long long LL;
 
LL M;
LL newmod(LL a, LL b) {
	return a <= b ? a : b + a % b;
}
void matrix_mul(LL a[][N], LL b[][N]) {
	int i, j, k;
	LL x[N][N] = { { 0, 0 }, { 0, 0 } };
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < N; k++)
				x[i][j] += a[i][k] * b[k][j];
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			a[i][j] = newmod(x[i][j], M);
}
 
void matrix_power(LL a[][N], LL exp) {
	LL x[N][N];
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			x[i][j] = a[i][j];
	LL tp, n = 0;
	for (tp = 1; tp <= exp; tp *= 2, n++)
		;
	for (n -= 2; n >= 0; n--) {
		matrix_mul(a, a);
		if ((1 << n) & exp) matrix_mul(a, x);
	}
}
 
LL phi(LL n) {
	LL phi = n, i, j;
	for (i = 2, j = 4; j <= n; i++, j += i + i - 1)
		if (!(n % i)) {
			phi = phi / i * (i - 1);
			while (!(n % i))
				n /= i;
		}
	if (n > 1) phi = phi / n * (n - 1);
	return phi;
}
 
LL mod_exp2(LL a, LL b, LL n) {
	LL hash = 1, factor = a, x = b;
	while (x) {
		if (x & 1) hash = newmod(hash * factor, n);
		factor = newmod(factor * factor, n);
		x >>= 1;
	}
	return hash;
}
 
LL f(LL x, LL n, LL p) {
	LL mm[N][N] = { { 1, 1 }, { 1, 0 } };
	M = phi(p);
	matrix_power(mm, n);
	return mod_exp2(x, mm[1][1], p);
}
LL solve() {
	LL ans, a, b, P, n;
	scanf("%lld%lld%lld%lld", &a, &b, &P, &n);
	if (!a || !b) return 0;
	if (n == 1) return a % P;
	ans = f(a, n - 1, P) * f(b, n, P) % P;
	return ans;
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--)
		printf("Case #%d: %lld\n", ca++, solve());
	return 0;
}