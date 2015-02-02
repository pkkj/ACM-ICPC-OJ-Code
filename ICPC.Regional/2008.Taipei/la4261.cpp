// 2008 Taipei: Trip Planning
// ACM-ICPC Live Archive 4261
#include <cstdio>
#include <cstring>
#define N 1005
 
int dis[N], n;
int pre[N], size[N], ans[N];
long long dp[N];
long long f(long long x) {
	return (100 - x) * (100 - x);
}
void getans() {
	int i = n, j = size[n] - 1;
	ans[j--] = n;
	while (i != -1) {
		i = pre[i];
		ans[j--] = i;
	}
}
void solve() {
	int i, j;
	for (i = 0; i < n; i++)
		scanf("%d", dis + i);
	dp[0] = 0, pre[0] = -1, size[0] = 1;
	for (i = 1; i <= n; i++) {
		int s = 0;
		dp[i] = 1LL << 40LL;
		size[i] = pre[i] = 1 << 29;
		for (j = i - 1; j >= 0; j--) {
			s += dis[j];
			long long cur = dp[j] + f(s);
			if (cur <= dp[i]) {
				if (cur < dp[i]) {
					dp[i] = cur;
					pre[i] = j;
					size[i] = size[j] + 1;
				} else if (size[j] + 1 <= size[i]) {
					if (size[j] + 1 < size[i]) size[i] = size[j] + 1, pre[i] = j;
					else if (j < pre[i]) pre[i] = j;
				}
			}
		}
	}
	printf("p=%lld\n", dp[n]);
	getans();
	for (i = 0; i < size[n]; i++) {
		printf(" %d", ans[i]);
		if ((i + 1) % 30 == 0 && (i + 1) != size[n]) printf("\n");
	}
	printf("\n");
}
int main() {
	int st = 1;
	while (scanf("%d", &n) && n) {
		if (st) st = 0;
		else printf("\n");
		solve();
	}
	return 0;
}