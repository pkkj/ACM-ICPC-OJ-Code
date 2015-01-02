// HDU 2292
// The 4th Baidu Cup Final: Minimum Heap 
#include<cstdio>
#include<cstring>
using namespace std;
#define N 1005
long long dp[N], tree[N*2], c[N][N], lc[N], rc[N], m;
void make(int n) {
	int i, j;
	memset(tree, 0, sizeof(tree));
	for (i = n; i >= 1; i--) {
		tree[i]++;
		tree[i] += tree[i * 2];
		tree[i] += tree[i * 2 + 1];
	}
	for (i = 0; i <= n; i++) {
		c[i][0] = 1;
		for (j = 1; j <= n; j++)
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % m;
	}
	for (i = 1; i <= n; i++)
		lc[tree[i]] = tree[i * 2], rc[tree[i]] = tree[i * 2 + 1];
}
 
long long f(long long x) {
	if (dp[x] != -1) return dp[x];
	return dp[x] = (((f(lc[x]) * f(rc[x])) % m) * c[x - 1][lc[x]]) % m;
}
int main() {
	int T;
	long long n;
	scanf("%d", &T);
	while (T--) {
		memset(dp, -1, sizeof(dp));
		dp[0] = dp[1] = dp[2] = 1, dp[3] = 2;
		scanf("%lld%lld", &n, &m);
		make(n);
		printf("%lld\n", f(n) % m);
	}
	return 0;
}
