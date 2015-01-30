// 2008 Nordic: Event Planning
// UVA 11559
#include <cstdio>
#define N 25
int price[N], a[N][N];
int main() {
	int n, b, h, w, i, j;
	while (scanf("%d%d%d%d", &n, &b, &h, &w) != EOF) {
		int best = b, ok = 0;
		for (i = 0; i < h; i++) {
			scanf("%d", &price[i]);
			for (j = 0; j < w; j++) {
				scanf("%d", &a[i][j]);
				if (a[i][j] >= n && price[i] * n <= best) best = price[i] * n, ok = 1;
			}
		}
		if (ok) printf("%d\n", best);
		else printf("stay home\n");
	}
	return 0;