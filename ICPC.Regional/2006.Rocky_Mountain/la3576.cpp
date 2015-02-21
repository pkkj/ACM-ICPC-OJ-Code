// 2006 Rocky Mountain: Baskets of Gold Coins
// ACM-ICPC Live Archive 3576

#include <cstdio>
long long n, w, d, sum;
int main() {
	while (scanf("%lld%lld%lld%lld", &n, &w, &d, &sum) != EOF) {
		n -= 1;
		long long ss = (n * n + n) / 2, s2;
		s2 = ss * w;
		if (s2 == sum) printf("%lld\n", n + 1);
		else printf("%lld\n", (s2 - sum) / d);
	}
	return 0;
}