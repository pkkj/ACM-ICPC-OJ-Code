// CII 4901
// 2010 East Central NA: Flip It!
#include <cstdio>
#include <cstring>
#define N 30
int ca[N][N][N * N], h[N][N];
int main() {
	int T = 0, n, m, i, j, k, left, right, top, bottom;
	char s[2 * N], *ps;
	while (scanf("%d%d", &n, &m) && n) {
		printf("Case %d:", ++T);
		memset(ca, 0, sizeof(ca));
		memset(h, 0, sizeof(h));
		for (i = 0; i < n; i++)
			for (j = 0; j < m; j++) {
				scanf("%d", &ca[i][j][0]);
				h[i][j] = 1;
			}
		gets(s);
		gets(s);
		ps = s;
		left = top = 0;
		right = m - 1;
		bottom = n - 1;
		while (*ps) {
			if (*ps == 'T') {
				i = top;
				for (j = left; j <= right; j++)
					for (k = h[i][j] - 1; k >= 0; k--)
						ca[i + 1][j][h[i + 1][j]++] = -ca[i][j][k];
				top++;
			}
			if (*ps == 'B') {
				i = bottom;
				for (j = left; j <= right; j++)
					for (k = h[i][j] - 1; k >= 0; k--)
						ca[i - 1][j][h[i - 1][j]++] = -ca[i][j][k];
				bottom--;
 
			}
			if (*ps == 'L') {
				j = left;
				for (i = top; i <= bottom; i++)
					for (k = h[i][j] - 1; k >= 0; k--)
						ca[i][j + 1][h[i][j + 1]++] = -ca[i][j][k];
				left++;
			}
			if (*ps == 'R') {
				j = right;
				for (i = top; i <= bottom; i++)
					for (k = h[i][j] - 1; k >= 0; k--)
						ca[i][j - 1][h[i][j - 1]++] = -ca[i][j][k];
				right--;
			}
			ps++;
		}
		for (k = 0; k < n * m; k++)
			if (ca[top][left][k] > 0) {
				printf(" %d", ca[top][left][k]);
			}
		printf("\n");
	}
 
}
