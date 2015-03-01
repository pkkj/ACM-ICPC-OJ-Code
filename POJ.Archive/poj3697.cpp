// 2008 Hefei Preliminary: USTC campus network
// POJ 3697
#include <cstdio>
#include <vector>
#include <cstring>
#define N 10006
using namespace std;
int used[N];
vector<int> G[N];
int solve(int n) {
	vector<int> v;
	int i, j, ans = 0, nt;
	v.push_back(1);
	used[1] = 1;
	while (1) {
		int notgo[N];
		for (i = 0; i <= n; i++)
			notgo[i] = 0;
		for (i = 0; i < v.size(); i++)
			for (j = 0; j < G[v[i]].size(); j++)
				notgo[G[v[i]][j]]++;
		nt = v.size();
		v.clear();
		for (i = 1; i <= n; i++)
			if (!used[i] && notgo[i] != nt)
				used[i] = 1, v.push_back(i), ans++;
		if (v.size() == 0)
			return ans;
	}
}

int main() {
	int T = 0, i, a, b, m, n;
	while (scanf("%d%d", &n, &m) && n) {
		memset(used, 0, sizeof(used));
		for (i = 0; i <= n; i++)
			G[i].clear();
		for (i = 0; i < m; i++) {
			scanf("%d%d", &a, &b);
			G[a].push_back(b), G[b].push_back(a);
		}
		printf("Case %d: %d\n", ++T, solve(n));
	}
	return 0;
}