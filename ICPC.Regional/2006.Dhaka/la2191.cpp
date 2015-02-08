// 2006 Dhaka: Mobile Casanova
// ACM-ICPC Live Archive 2189
#include <cstdio>
#include <cstring>
#define N 100005
 
typedef long long ll;
char list[N][20];
ll num[N];
int main() {
	int n, i, j, len, ca = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d:\n", ca++);
		for (i = 0; i < n; i++) {
			scanf("%s", list[i]);
			sscanf(list[i], "%lld", &num[i]);
		}
		len = strlen(list[0]);
		int begin = 0, st = 1;
		for (i = 1; i < n; i++) {
 
			if (num[i] - num[i - 1] > 1) {
				if (i - begin == 1) {
					printf("%s", list[begin]);
				} else {
					printf("%s-", list[begin]);
					for (j = 0; j < len; j++)
						if (list[begin][j] != list[i - 1][j]) break;
					for (; j < len; j++)
						printf("%c", list[i - 1][j]);
				}
				printf("\n");
				begin = i;
			}
		}
 
		if (i - begin == 1) {
			printf("%s", list[begin]);
		} else {
			printf("%s-", list[begin]);
			for (j = 0; j < len; j++)
				if (list[begin][j] != list[i - 1][j]) break;
			for (; j < len; j++)
				printf("%c", list[i - 1][j]);
		}
		printf("\n\n");
	}
	return 0;
}