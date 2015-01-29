// 2008 Northwestern Europe: Disgruntled Judge
// ACM-ICPC Live Archive 4289
#include <cstdio>
#include <cstdlib>
#define N 10000
#define M 10001
int x[N];
 
int main() {
	int n, i, a, b, y, ok;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", x + i);
	while (1) {
		a = rand() % M, b = rand() % M;
		y = x[0];
		ok = 1;
		for (i = 0; i < n && ok; i++) {
			if (x[i] != y) ok = 0;
			y = (y * a + b) % M;
			y = (y * a + b) % M;
		}
		if (ok) {
			for (i = 0; i < n; i++)
				printf("%d\n", (x[i] * a + b) % M);
			return 0;
		}
	}
	return 0;
}