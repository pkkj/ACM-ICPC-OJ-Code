// 2003 Guangzhou: Sum of Factorials
// ACM-ICPC Live Archive 2953
// POJ 1775
#include <cstdio>
#include <cstring>
#define N 30
int a[N] = { 1, 1 };
int main() {
	int i, n;
	for (i = 2; i <= 12; i++)
		a[i] = a[i - 1] * i;

	while (scanf("%d", &n) && n >= 0) {
		if (n == 0) {
			puts("NO");
			continue;
		}
		i = 12;
		while (n >= 0 && i >= 0) {
			if (n >= a[i]) n -= a[i];
			i--;
		}
		if (n == 0) puts("YES");
		else puts("NO");
	}
	return 0;
}
