// 2005 Southwestern Europe: 4 Values whose Sum is 0
// ACM-ICPC Live Archive 3506
#include <cstdio>
#include <cstring>
#define M 4005
#define SIZE 4000037
using namespace std;
int a[M][4];
int value[SIZE], amount[SIZE], use[SIZE];
int locate(int s) {
	int h;
	h = s;
	while (h < 0)
		h += SIZE;
	while (h >= SIZE)
		h -= SIZE;
	while (use[h] && value[h] != s) {
		h++;
		if (h >= SIZE)
			h -= SIZE;
	}
	return h;
}
void insert(int s) {
	int posi = locate(s);
	if (!use[posi]) {
		use[posi] = 1;
		value[posi] = s;
	}
	amount[posi]++;
}

int main() {
	int n, i, j, x, T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++) {
		if (ca)
			printf("\n");
		long long ans = 0;
		memset(use, 0, sizeof(use));
		memset(amount, 0, sizeof(amount));
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			for (j = 0; j < 4; j++)
				scanf("%d", &a[i][j]);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				x = a[i][0] + a[j][1];
				insert(x);
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				x = a[i][2] + a[j][3];
				int posi = locate(-x);
				if (value[posi] == -x)
					ans += amount[posi];
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
