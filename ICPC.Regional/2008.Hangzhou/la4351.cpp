// 2008 Hangzhou: A Pair of Graphs
// ACM-ICPC Live Archive 4351
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 9
bool g1[N][N], g2[N][N];
int n, m1, m2, arr[N];
void solve() {
	int a, b, i, j, ia, ib, da, db, t, ans = 1 << 29;
	scanf("%d%d%d%d", &ia, &ib, &da, &db);
	memset(g1, 0, sizeof(g1));
	memset(g2, 0, sizeof(g2));
	for (i = 0; i < m1; i++) {
		scanf("%d%d", &a, &b);
		g1[a][b] = g1[b][a] = 1;
	}
	for (i = 0; i < m2; i++) {
		scanf("%d%d", &a, &b);
		g2[a][b] = g2[b][a] = 1;
	}
	if (n > 1) {
		for (i = 0; i < n; i++)
			arr[i] = i;
		while (next_permutation(arr, arr + n)) {
			t = 0;
			for (i = 0; i < n; i++)
				for (j = i + 1; j < n; j++) {
					a = arr[i], b = arr[j];
					if (g1[a][b] == g2[i][j])
						continue;
					if (!g1[a][b] && g2[i][j])
						t += min(ia, db);
					else
						t += min(ib, da);
				}
			ans = min(ans, t);
		}
	} else
		ans = 0;
	printf("%d\n", ans);
}
int main() {
	int T = 0;
	while (scanf("%d%d%d", &n, &m1, &m2) && n) {
		printf("Case #%d: ", ++T);
		solve();
	}
	return 0;
}
