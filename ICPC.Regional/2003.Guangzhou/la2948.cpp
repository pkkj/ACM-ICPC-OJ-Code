// 2003 Guangzhou: Special Experiment
// ACM-ICPC Live Archive 2948
// POJ 1770
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 205
int n, m;
int st[N], ph[N], dp[N][2];
vector<int> G[N];
bool v[N];
//dp 0: not used; dp 1: used
void dfs(int x)
{
	int i, y;
	v[x] = 1;
	dp[x][0] = 0, dp[x][1] = st[x];
	for(i = 0; i < (int)G[x].size(); i++)
	{
		y = G[x][i];
		if(!v[y])
		{
			dfs(y);
			dp[x][0] += max(dp[y][0], dp[y][1]);
			dp[x][1] += dp[y][0];
		}
	}
}
int solve() {
	int i, j;
	for (i = 0; i < n; i++)
	{
		G[i].clear();
		scanf("%d", &st[i]);
	}
	for (i = 0; i < m; i++)
		scanf("%d", &ph[i]);
 
	sort(ph, ph + m);
	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)
		{
			if(binary_search(ph, ph+m, st[j] - st[i]))
				G[i].push_back(j), G[j].push_back(i);
		}
	memset(v, 0, sizeof(v));
	dfs(0);
	return max(dp[0][0], dp[0][1]);
}
int main() {
	while (scanf("%d%d", &n, &m) && n)
		printf("%d\n", solve());
	return 0;
}