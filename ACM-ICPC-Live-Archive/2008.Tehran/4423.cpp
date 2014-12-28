// CII 4423
// 2008 Tehran: String LD
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
char ch[N][N];
int len[N];
int getcommon(char *s1, char *s2, int len) {
	int ret = 0, i;
	for (i = len - 1; i >= 0; i--) {
		if (s1[i] != s2[i]) return ret;
		ret++;
	}
	return ret;
}
int n;
void solve() {
	int i, j, minlen = 10000;
	for (i = 0; i < n; i++) {
		scanf("%s", ch[i]);
		len[i] = strlen(ch[i]);
		minlen = min(minlen, len[i]);
	}
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			if (len[i] != len[j]) continue;
			int t = len[i] - getcommon(ch[i], ch[j], len[i]);
			minlen = min(t, minlen);
		}
	printf("%d\n", minlen - 1);
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
