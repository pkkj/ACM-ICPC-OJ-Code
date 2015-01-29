// CII 4123
// 2008 World Finals: Glenbow Museum
#include <cstdio>
#include <cstring>
long long f(long long x) {
	return x * (x - 1) * (x - 2) * (x - 3) / 4 / 3 / 2;
}
int main() {
	long long n, ans;
	int ca = 1;
	while (scanf("%lld", &n) && n) {
		if (n % 2) ans = 0;
		else {
			n = (n + 4) / 2;
			ans = f(n) + f(n - 1);
		}
		printf("Case %d: %lld\n", ca++, ans);
	}
	return 0;
}
