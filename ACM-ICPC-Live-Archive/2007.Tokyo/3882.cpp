// 2007 Tokyo: And Then There Was One
// ACM-ICPC Live Archive 3882
// POJ 3517
#include <cstdio>
int main() {
	int n, k, m;
	while (scanf("%d%d%d", &n, &k, &m) && n) {
		int i, s = 0;
		for (i = 2; i < n; i++)
			s = (s + k) % i;
		s = (s + m) % n;
		printf("%d\n", s + 1);
	}
	return 0;
}