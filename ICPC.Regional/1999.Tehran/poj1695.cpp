// 1999 Tehran: Magazine Delivery
// POJ 1695

#include <cstdio>
#include <cstring>

const int MAX = 1 << 20;
const int N = 32;

int d[N][N], f[N][N][N], n;

void dp() {
	memset(f, 127, sizeof(f));
	f[1][1][1] = 0;
	for (int k = 2; k <= n; k++)
		for (int i = 1; i < k; i++)
			for (int j = 1; j < k; j++) {
				if (f[i][j][k - 1] + d[i][k] < f[j][k - 1][k])
					f[j][k - 1][k] = f[i][j][k - 1] + d[i][k];
				if (f[i][j][k - 1] + d[j][k] < f[i][k - 1][k])
					f[i][k - 1][k] = f[i][j][k - 1] + d[j][k];
				if (f[i][j][k - 1] + d[k - 1][k] < f[i][j][k])
					f[i][j][k] = f[i][j][k - 1] + d[k - 1][k];
			}

	int ans = f[1][1][n];
	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			if (f[i][j][n] < ans)
				ans = f[i][j][n];
	printf("%d\n", ans);
}

int main() {
	int T, i, j;
	scanf("%d", &T);
	while (T--) {
		memset(d, 0, sizeof(d));
		scanf("%d", &n);
		for (i = 1; i < n; i++)
			for (j = i + 1; j <= n; j++) {
				scanf("%d", &d[i][j]);
				d[j][i] = d[i][j];
			}
		dp();
	}
	return 0;
}
