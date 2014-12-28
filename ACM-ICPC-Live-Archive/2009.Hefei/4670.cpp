// CII 4670 - Brute-force solution
// 2009 Hefei: Dominating Patterns
#include <cstdio>
#include <cstring>
#define LEN 1000005
#define N 155
int P[N];
char A[LEN], B[N][N];
int ans[N], len;
void match(int idx) {
	int i, j, m, n = len, ans = 0;
	P[1] = 0, j = 0;
	m = strlen(B[idx] + 1);
 
	for (i = 2; i <= m; i++) {
		while ((j > 0) && (B[idx][j + 1] != B[idx][i]))
			j = P[j];
		if (B[idx][j + 1] == B[idx][i])
			j++;
		P[i] = j;
	}
 
	j = 0;
	for (i = 1; i <= n; i++) {
		while (j > 0 && B[idx][j + 1] != A[i])
			j = P[j];
		if (B[idx][j + 1] == A[i])
			j++;
		if (j == m)
			ans++, j = P[j];
	}
	::ans[idx] = ans;
}
int main() {
	int n, i;
	while (scanf("%d", &n) && n) {
		int best = 0;
		for (i = 0; i < n; i++)
			scanf("%s", B[i] + 1);
		scanf("%s", A + 1);
		len = strlen(A + 1);
		for (i = 0; i < n; i++) {
			match(i);
			if (ans[i] > best)
				best = ans[i];
		}
		printf("%d\n", best);
		for (i = 0; i < n; i++)
			if (ans[i] == best)
				printf("%s\n", B[i] + 1);
	}
 
	return 0;
}
