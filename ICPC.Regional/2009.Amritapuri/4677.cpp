// CII 4677
// 2009 Amritapuri: Interleaved Periodic String
#include <cstdio>
#include <cstring>
 
char s[100];
void solve() {
	scanf("%s", s);
	int len = strlen(s);
	int ans = 1, i;
	for (i = 1; i < len; i++)
		if (s[i] != s[0]) ans = 2;
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
