// 2009 Phuket: Nowhere Money
// ACM-ICPC Live Archive 4721
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;
#define N 100
ll dp[N], ans[N];
int main() {
	//freopen("in.txt", "r", stdin);
	int i,  sz;
	ll x;
	dp[1] = 1, dp[2] = 2;
	for (i = 3; i <= 90; i++)
		dp[i] = dp[i - 2] + dp[i - 1];
	while (scanf("%lld", &x) != EOF) {
		printf("%lld\n", x);
		sz = 0;
		for (i = 90; x;) {
			if (x >= dp[i]) ans[sz++] = i, x -= dp[i];
			i--;
		}
		for (i = 0; i < sz; i++)
			printf("%lld ", ans[i]);
		printf("\n");
		for (i = 0; i < sz; i++)
			printf("%lld ", dp[ans[i]]);
		printf("\n\n");
	}
	return 0;
}