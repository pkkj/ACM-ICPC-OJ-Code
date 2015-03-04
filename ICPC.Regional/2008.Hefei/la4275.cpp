// 2008 Hefei: Rational Number Approximation
// ACM-ICPC Live Archive 4275

#include <cstdio>
long long gcd(long long m, long long n) {
	long long r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
int main() {
	long long a, b, n;
	int T = 0;
	while (scanf("%lld%lld%lld", &a, &b, &n) && (a + b)) {
		long long x1, x3, y1, y3, x2, y2, gd, l, r, m, k1, k2;
		gd = gcd(a, b);
		a /= gd, b /= gd;
		printf("Case %d: ", ++T);
		if (b <= n) {
			printf("%lld/%lld %lld/%lld\n", a, b, a, b);
			continue;
		}
		x1 = 0, y1 = 1, x3 = 1, y3 = 1;
		while (1) {
			x2 = x1 + x3, y2 = y1 + y3;
			if (y2 > n) break;
			l = 1, r = n;
			if (a * y2 < b * x2) {
				while (l < r) {
					m = (l + r + 1) / 2;
					k1 = m * x1 + x3, k2 = m * y1 + y3;
					if (m * y1 + y3 > n || k1 * b < k2 * a) r = m - 1;
					else l = m;
				}
				x3 = l * x1 + x3, y3 = l * y1 + y3;
			} else {
				while (l < r) {
					m = (l + r + 1) / 2;
					k1 = x1 + m * x3, k2 = y1 + m * y3;
					if (y1 + m * y3 > n || k1 * b > k2 * a) r = m - 1;
					else l = m;
				}
				x1 = x1 + l * x3, y1 = y1 + l * y3;
			}
		}
		printf("%lld/%lld %lld/%lld\n", x1, y1, x3, y3);
	}
	return 0;
}
