// 2008 Southeastern Europe: GCD Determinant
// ACM-ICPC Live Archive 4190

#include <cstdio>
#include <cstring>
#define MM 1000000007
int n;
long long phi(long long n) {
	long long phi = n, i, j;
	for (i = 2, j = 4; j <= n; i++, j += i + i - 1)
		if (!(n % i)) {
			phi = phi / i * (i - 1);
			while (!(n % i))
				n /= i;
		}
	if (n > 1) phi = phi / n * (n - 1);
	return phi;
}

void solve() {
	long long ans = 1;
	while(n--)
	{
		long long x;
		scanf("%lld", &x);
		ans *= phi(x);
		ans %= MM;
	}
	printf("%lld\n", ans);
}
int main() {

	while (scanf("%d", &n) != EOF)
		solve();
	return 0;
}
