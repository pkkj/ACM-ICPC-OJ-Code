// CII 4494
// 2009 Dhaka: How Many Ones Needed?
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
long long a, b;
long long dp[50];
long long bin(long long x) {
	long long i, ans;
	for (i = 1;; i++) {
		if ((1LL << i) <= x) ans = i;
		else break;
	}
	return ans;
}
long long f(long long x) {
	if (x == 0) return 0;
	if (x == 1) return 1;
	long long b = bin(x);
	long long u = (1LL << b);
	return dp[b] + f(x - u) + x - u + 1;
}
long long solve() {
	if (a <= 1) return f(b);
	return f(b) - f(a - 1);
}
int main() {
	int ca = 1, i;
	long long t = 2;
	dp[0] = 0, dp[1] = 1;
	for (i = 2; i <= 32; i++) {
		dp[i] = dp[i - 1] * 2LL + t;
		t <<= 1LL;
	}
	while (scanf("%lld%lld", &a, &b) && a + b)
		printf("Case %d: %lld\n", ca++, solve());
	return 0;
}
