// 2006 Northeastern Europe: Java vs C++
// ACM-ICPC Live Archive 3711

#include <cstdio>
#include <cstring>

#define CPP 1
#define JAVA 2
#define BAD 3

void solve(char *str) {
	int i, len = strlen(str), mode = 0;

	if ((str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_' || str[len - 1] == '_')
		mode = BAD;
	else if (strstr(str, "_"))
		mode = CPP;
	if (mode == CPP || mode == 0)
		for (i = 0; i < len; i++) {
			if (str[i] >= 'A' && str[i] <= 'Z') {
				if (mode == CPP)
					mode = BAD;
				else if (!mode)
					mode = JAVA;
				break;
			}
			if (str[i] == '_' && str[i - 1] == '_') {
				mode = BAD;
				break;
			}
		}

	if (mode == BAD) {
		puts("Error!");
		return;
	}
	if (mode == 0) {
		puts(str);
		return;
	}
	if (mode == JAVA) {
		i = 0;
		while (i < len - 1) {
			putchar(str[i]);
			if ((str[i + 1] >= 'A' && str[i + 1] <= 'Z')) {
				str[i + 1] += 'a' - 'A';
				putchar('_');
			}
			i++;
		}
		putchar(str[len - 1]);

	} else if (mode == CPP) {
		i = -1;
		while (i < len - 1) {
			i++;
			if (str[i] == '_')
				continue;
			if (i > 0 && str[i - 1] == '_')
				str[i] += 'A' - 'a';
			putchar(str[i]);
		}
	}
	putchar('\n');
}

int main() {
	char str[300];
	freopen("in.txt", "r", stdin);
	while (scanf("%s", str) != EOF)
		solve(str);
	return 0;
}
