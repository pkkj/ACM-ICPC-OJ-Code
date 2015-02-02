// 2008 Jakarta: Greatest Expert Enough?
// ACM-ICPC Live Archive 4142
#include <cstdio>
#define N 10005
 
char name[N][30];
int seg[N][2];
void solve() {
	int n, i, Q, x;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%s%d%d", name[i], &seg[i][0], &seg[i][1]);
	scanf("%d", &Q);
	while (Q--) {
		int ok = 0, pos;
		scanf("%d", &x);
		for (i = 0; i < n && ok < 2; i++) {
			if (seg[i][0] <= x && x <= seg[i][1]) ok++, pos = i;
		}
		if (ok == 0 || ok >= 2) printf("UNDETERMINED\n");
		else printf("%s\n", name[pos]);
	}
}
int main() {
	int T, st = 1;
	scanf("%d", &T);
	while (T--) {
		if (st == 1) st = 0;
		else printf("\n");
		solve();
	}
	return 0;
}