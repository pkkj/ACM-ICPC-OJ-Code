// 2008 Kuala Lumpur: Match Maker
// ACM-ICPC Live Archive 4404
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
 
#define N 20
 
char s[10000];
string s1[N], s2[N];
bool g[N][N];
int n;
long long dp[17][(1 << 16) + 1];
int pre[17][(1 << 16) + 1];
int find(string *l, string s) {
	for (int i = 0; i < n; i++)
		if (l[i] == s) return i + 1;
}
 
void read() {
	int i, j, len, x, y;
	string tt;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s\n", s);
		s1[i] = s;
	}
	for (i = 0; i < n; i++) {
		scanf("%s\n", s);
		s2[i] = s;
	}
	sort(s1, s1 + n, greater<string> ());
	sort(s2, s2 + n);
	memset(g, 0, sizeof(g));
	for (i = 0; i < n; i++) {
		gets(s);
		tt = "";
		len = strlen(s);
		s[len] = ' ';
		for (j = 0;; j++) {
			if (s[j] == ':') break;
			tt += s[j];
		}
		x = find(s1, tt);
		j += 2;
		tt = "";
		for (; j <= len; j++) {
			if (s[j] == ' ') {
				y = find(s2, tt);
				g[x][y] = 1;
				tt = "";
			} else tt += s[j];
		}
	}
}
 
void solve() {
	int tot = (1 << n), i, j, k;
	memset(dp, 0, sizeof(dp));
	memset(pre, -1, sizeof(pre));
	dp[0][0] = 1;
	for (i = 1; i <= n; i++) {
		for (j = 0; j < tot; j++) {
			if (dp[i - 1][j]) {
				for (k = 1; k <= n; k++)
					if (g[i][k]) {
						int next = j | (1 << (k - 1));
						if (next != j) {
							dp[i][next] += dp[i - 1][j];
							pre[i][next] = j;
						}
					}
			}
		}
	}
}
void print() {
	int i, cc, pp, a, b, match[N];
	if (!dp[n][(1 << n) - 1]) {
		printf("No Way\n");
		return;
	}
	printf("%lld\n", dp[n][(1 << n) - 1]);
	cc = (1 << n) - 1;
	for (i = n; i >= 1; i--) {
		match[i - 1] = 0;
		pp = pre[i][cc];
		a = cc, b = pp;
		while (a || b) {
			if ((a & 1) != (b & 1)) break;
			a >>= 1, b >>= 1, match[i - 1]++;
		}
		cc = pp;
	}
	int st = 1;
	for (i = n-1; i>=0; i--) {
		if (st) st = 0;
		else printf(" ");
		printf("%s %s", s1[i].c_str(), s2[match[i]].c_str());
	}
	printf("\n");
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d:\n", ca++);
		read();
		solve();
		print();
	}
	return 0;
}