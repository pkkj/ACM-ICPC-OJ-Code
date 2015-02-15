// Rocky Mountain 2005: Faulty Odometer
// ACM-ICPC Live Archive 3342
// POJ 2719

#include <cstdio>
#include <cstring>

int nine[11] = { 1 };
int main() {
	char s[20], ch;
	int i, sum, j;
	for (i = 1; i <= 10; i++)
		nine[i] = nine[i - 1] * 9;
	while (scanf("%s", s) && s[0] - '0') {
		sum = j = 0;
		for (i = strlen(s) - 1; i >= 0; i--, j++) {
			if ((ch = s[i]) > '4')
				ch--;
			sum += nine[j] * (ch - '0');
		}
		printf("%s: %d\n", s, sum);
	}
	return 0;
}
