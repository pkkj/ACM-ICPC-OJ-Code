// 2008 Jakarta: Greatest K-Palindrome Substring
// ACM-ICPC Live Archive 4144
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1005
char s[N];
void solve() {
	int len, k, i, a, b, kk, ans = 1, cur;
	scanf("%s%d", s, &k);
	len = strlen(s);
	for (i = 0; i < len; i++) {
		cur = 1;
		a = i - 1, b = i + 1, kk = k;
		while (kk > 0 && a >= 0 && b < len) {
			if (s[a] != s[b]) kk--;
			a--, b++;
			cur += 2;
		}
		while (a >= 0 && b < len) {
			if (s[a] != s[b]) break;
			a--, b++;
			cur += 2;
		}
		ans = max(cur, ans);
	}
	for (i = 1; i < len; i++) {
		cur = 2;
		a = i - 2, b = i + 1, kk = k;
		if (s[i] != s[i - 1] && k == 0) continue;
		if (s[i] != s[i - 1]) kk--;
		while (kk > 0 && a >= 0 && b < len) {
			if (s[a] != s[b]) kk--;
			a--, b++;
			cur += 2;
		}
		while (a >= 0 && b < len) {
			if (s[a] != s[b]) break;
			a--, b++;
			cur += 2;
		}
		ans = max(cur, ans);
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}