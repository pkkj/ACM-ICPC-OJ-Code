// CII 4669
// 2009 Hefei: Laser in Cuboids
#include <cstdio>
 
int gcd(int m, int n) {
	int r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
int main() {
	int a, b, c;
	while (scanf("%d%d%d", &a, &b, &c) && a + b + c)
		printf("%d\n", a + b + c - gcd(a, b) - gcd(b, c) - gcd(a, c) + gcd(c,
				gcd(a, b)));
	return 0;
}
