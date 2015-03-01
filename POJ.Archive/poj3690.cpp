// 2008 Hefei Preliminary: Constellations
// POJ 3690
#include <cstdio>
#define M 1003
#define N 55
long long mask[N], st[M][M];
int n, m, t, p, q;
void init() {
	mask[1] = 1;
	for (int i = 2; i <= 51; i++)
		mask[i] = (mask[i - 1] << 1) + 1;
}
int solve() {
	int i, j, k, ans = 0, fail;
	for (i = 1; i <= n; i++) {
		getchar();
		st[i][1] = 0;
		for (j = 1; j <= q; j++)
			st[i][1] = (st[i][1] << 1) + (getchar() == '*');
		for (k = 2; j <= m; j++, k++)
			st[i][k] = ((st[i][k - 1] << 1) + (getchar() == '*')) & mask[q];

	}
	while (t--) {
		long long mt[N];
		getchar();
		for (i = 1; i <= p; i++)
			for (getchar(), j = 1, mt[i] = 0; j <= q; j++)
				mt[i] = (mt[i] << 1) + (getchar() == '*');

		for (i = 1; i <= n - p + 1; i++)
			for (j = 1; j <= m - q + 1; j++) {
				fail = 0;
				for (k = 0; k < p; k++)
					if (st[i + k][j] != mt[k + 1]) {
						fail = 1;
						break;
					}
				if (!fail)
					goto out;
			}
	out: ans += !fail;
	}
	return ans;
}

int main() {
	int T = 0;
	init();
	while (scanf("%d%d%d%d%d", &n, &m, &t, &p, &q) && p)
		printf("Case %d: %d\n", ++T, solve());
	return 0;
}