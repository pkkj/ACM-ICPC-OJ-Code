// 2007 Dhaka: Bachelor Arithmetic
// ACM-ICPC Live Archive 4055
#include <cstdio>
#include <cmath>
int main() {
	int B, S, T=1;
	while (scanf("%d%d", &B, &S) && B + S) {
		printf("Case %d: ", T++);
		if (B - 1 == 0) printf(":-\\\n");
		else {
			if(B==S || B<S)
				printf(":-|\n");
			else if(B>S)
				printf(":-(\n");
		}
 
	}
}