// POJ 3734 Blocks
// PKU Campus 2009 (POJ Monthly Contest – 2009.05.17), Simon
#include <cstdio>
#include <cstring>
int len;
typedef long long ll;
#define N 3
#define M 10007
void matrix_mul(ll a[][N], ll b[][N]) {
	int i, j, k;
	ll x[N][N] = { 0 };
	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			for (k = 0; k < len; k++)
				x[i][j] += a[i][k] * b[k][j];
	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			a[i][j] = x[i][j] % M;
}
 
void matrix_power(ll a[][N], int exp) {
	ll x[N][N];
	int i, j;
	if (exp == 0) {
		memset(x, 0, sizeof(x));
		for (i = 0; i < len; i++)
			x[i][i] = 1;
		memcpy(a, x, sizeof(x));
		return;
	}
	for (i = 0; i < len; i++)
		for (j = 0; j < len; j++)
			x[i][j] = a[i][j];
	ll tp, n = 0;
	for (tp = 1; tp <= exp; tp *= 2, n++)
		;
	for (n -= 2; n >= 0; n--) {
		matrix_mul(a, a);
		if ((1 << n) & exp) matrix_mul(a, x);
	}
}
int main() {
	//freopen("in.txt", "r", stdin);
	int T, e;
	scanf("%d", &T);
	len = 3;
	while (T--) {
		ll a[N][N] = { { 2, 1, 0 }, { 2, 2, 2 }, { 0, 1, 2 } };
		scanf("%d", &e);
		matrix_power(a, e);
		printf("%lld\n", a[0][0]);
	}
	return 0;
}
