// CII 4667
// 2009 Hefei: Mersenne Prime
#include <cstdio>
 
int main() {
	bool is[258] = { 0 };
	is[2] = 1, is[3] = 1, is[5] = 1, is[7] = 1, is[13] = 1;
	is[17] = 1, is[19] = 1, is[31] = 1, is[61] = 1, is[89] = 1;
	is[107] = 1, is[127] = 1;
	int x;
	while (scanf("%d", &x) && x)
		printf(is[x] ? "%d:Prime\n" : "%d:NotPrime\n", x);
	return 0;
}
