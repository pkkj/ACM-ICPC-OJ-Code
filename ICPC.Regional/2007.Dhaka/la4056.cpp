// 2007 Dhaka: Nested Squares
// ACM-ICPC Live Archive 4056
#include <cstdio>
#include <cstring>
#define N 50005
char s[N];
int iabs(int x)
{
	return x < 0 ? -x : x;
}
void solve() {
	int Q, cq = 1, x1, x2, y1, y2, i, j, len;
	scanf("%s%d", s, &Q);
	len = strlen(s);
	while (Q--) {
		printf("Query %d:\n", cq++);
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		for (i = x1; i <= x2; i++) {
			for (j = y1; j <= y2; j++) {
				int d1 = iabs(i - len), d2 = iabs(j - len);
				int d = d1 > d2 ? d1 : d2;
				printf("%c", s[len-1-d]);
			}
			printf("\n");
		}
	}
	printf("\n");
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Square %d:\n", ca++);
		solve();
	}
	return 0;
}