// 2009 Phuket: Relational Operators
// ACM-ICPC Live Archive 4716
#include <cstdio>
#include <cstring>
 
int main() {
	int ca = 1, a, b;
	char s[10];
	while (scanf("%d%s%d", &a, s, &b) && s[0] != 'E') {
		printf("Case %d: ", ca++);
		if (strcmp(s, "==") == 0) {
			if (a == b) printf("true\n");
			else printf("false\n");
		}
		if (strcmp(s, "<=") == 0) {
			if (a <= b) printf("true\n");
			else printf("false\n");
		}
		if (strcmp(s, ">=") == 0) {
			if (a >= b) printf("true\n");
			else printf("false\n");
		}
		if (strcmp(s, "<") == 0) {
			if (a < b) printf("true\n");
			else printf("false\n");
		}
		if (strcmp(s, ">") == 0) {
			if (a > b) printf("true\n");
			else printf("false\n");
		}
		if (strcmp(s, "!=") == 0) {
			if (a != b) printf("true\n");
			else printf("false\n");
		}
 
	}
	return 0;
}