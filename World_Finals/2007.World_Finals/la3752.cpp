// 2007 World Finals: Containers
// ACM-ICPC Live Archive 3752

#include <cstdio>
#include <cstring>
#define N 1005
char s[N];
int dp[N];
void solve() {
	int i, j, n, ans = 0;
	dp[0] = 1;
	n = strlen(s);
	for (i = 1; i < n; i++) {
		dp[i] = 1;
		for (j = 0; j < i; j++) {
			if (s[i] > s[j]) dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
		}
	}
	for (i = 0; i < n; i++)
		ans = ans > dp[i] ? ans : dp[i];
	printf("%d\n", ans);
}
int main() {
	int ca = 1;
	while (scanf("%s", s) && s[0] != 'e') {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}