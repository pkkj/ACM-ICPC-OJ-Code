// 2008 Kuala Lumpur: ASCII Diamondi
// ACM-ICPC Live Archive 4403
#include <cstdio>
#include <cstring>
int n, x1, x2, y1, y2;
int iabs(int x) {
	return x < 0 ? -x : x;
}
void solve() {
	int i, j;
	scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	for (i = x1; i <= x2; i++) {
		for (j = y1; j <= y2; j++) {
			int a = i % (2*n-1), b = j % (2*n-1);
			int v = iabs(b - (n - 1)) + iabs(a - (n - 1));
			if (v >= n) printf(".");
			else printf("%c", 'a' + (v % 26));
		}
		printf("\n");
	}
}
int main() {
	int T = 1;
	//freopen("in.txt", "r", stdin);
	while (scanf("%d", &n) && n) {
		printf("Case %d:\n", T++);
		solve();
	}
	return 0;
}