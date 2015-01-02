// SGU 222 Little Rooks
#include <cstdio>
#include <cstring>
long long f(long long x) {
	long long ans = 1;
	while (x > 1)
		ans *= x--;
	return ans;
}
int main() {
	long long n, k, ans;
	scanf("%lld%lld", &n, &k);
	if (k > n) printf("0\n");
	else {
		ans = f(n) / f(n - k);
		ans *= f(n) / f(k) / f(n - k);
		printf("%lld\n", ans);
	}
	return 0;
}
