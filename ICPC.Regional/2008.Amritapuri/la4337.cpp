// 2008 Amritapuri: Pile it down
// ACM-ICPC Live Archive 4337
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1010
int t[N][N], sg[N][N];
int checkmin(int a, int b) {
	if (a == -1) return b;
	return min(a, b);
}
void calc() {
	int i, j, k, x, y, n = 1000;
	int dx[] = { 0, 1, 1 };
	int dy[] = { 1, 0, 1 };
	memset(t, -1, sizeof(t));
	memset(sg, 0, sizeof(sg));
	t[0][0] = 0;
	for (i = 1; i <= n; i++)
		t[i][0] = sg[i][0] = t[0][i] = sg[0][i] = t[i][i] = sg[i][i] = 1;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (sg[i][j]) continue;
			t[i][j] = 1;
			for (k = 0; k < 3; k++) {
				x = i - dx[k], y = j - dy[k];
				while (x >= 0 && y >= 0) {
					t[i][j] = max(t[i][j], t[x][y] + 1);
					x -= dx[k], y -= dy[k];
				}
			}
			for (k = 0; k < 3; k++) {
				x = i + dx[k], y = j + dy[k];
				while (x <= n && y <= n) {
					t[x][y] = checkmin(t[x][y], t[i][j] + 1);
					sg[x][y] = 1;
					x += dx[k], y += dy[k];
				}
			}
		}
	}
}
int main() {
	calc();
	int T, x, y, p;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &x, &y, &p);
		if (sg[x][y]) printf("Sita %d\n", t[x][y] + 2 * p);
		else printf("Gita %d\n", t[x][y] + 2 * p);
	}
	return 0;
}