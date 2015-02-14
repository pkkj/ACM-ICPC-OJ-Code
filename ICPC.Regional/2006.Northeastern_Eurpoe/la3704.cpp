// 2006 Northeastern Europe: Cellular Automaton
// ACM-ICPC Live Archive 3704

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 505
int n;
long long M;

int iabs(int x) {
	return x < 0 ? -x : x;
}
void matrix_mul(long long a[N], long long b[N]) {
	int i, j;
	long long x[N] = { 0 };
	for (j = 0; j < n; j++)
		if (a[j])
			for (i = 0; i < n; i++)
				if (b[(i + n - j) % n])
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
		if ((1 << n) & exp)
			matrix_mul(a, x);
	}
}
long long in[N], mat[N];
int main() {
	freopen("in.txt", "r", stdin);
	int k, d, i, j;
	while (scanf("%d%lld%d%d", &n, &M, &d, &k) != EOF) {
		for (i = 0; i < n; i++)
			scanf("%lld", &in[i]);
		memset(mat, 0, sizeof(mat));
		for (i = 0; i < n; i++) {
			int a = iabs(0 - i), b = n - iabs(0 - i);
			mat[i] = min(a, b) <= d;
		}
		matrix_power(mat, k);
		for (i = 0; i < n; i++) {
			long long ans = 0;
			if (i)
				printf(" ");
			for (j = 0; j < n; j++)
				ans = (ans + mat[(j + n - i) % n] * in[j]) % M;
			printf("%lld", ans);
		}
		printf("\n");
	}
	return 0;
}
