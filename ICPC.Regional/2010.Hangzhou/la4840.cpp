// CII 4840
// 2010 Hangzhou: National Day Parade
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 60
vector<int> pos[N];
int iabs(int x) {
	return x < 0 ? -x : x;
}
int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) && n) {
		int i, j, k, x, y, ans = 1 << 30, tans;
		for (i = 0; i < n; i++)
			pos[i].clear();
		for (i = 0; i < n * n; i++) {
			scanf("%d%d", &x, &y);
			pos[x - 1].push_back(y);
		}
 
		for (i = 0; i < n; i++)
			sort(pos[i].begin(), pos[i].end());
		for (i = 1; i <= m - n; i++) {
			tans = 0;
			for (j = 0; j < n; j++)
				for (k = 0; k < n; k++)
					tans += iabs(pos[j][k] - (i + k));
			ans = min(tans, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}
