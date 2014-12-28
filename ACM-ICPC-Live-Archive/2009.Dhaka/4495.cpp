// CII 4495
// 2009 Dhaka: Foot Notes
#include <cstdio>
#include <cstring>
#include <vector>
 
using namespace std;
#define N 505
#define S 105
#define INF 1<<29
int n, s, w;
vector<int> foot[N];
int need[N][N], dp[N];
bool has[N], avoid[N][N];
int solve() {
	int x, xi, i, j, k;
	scanf("%d%d%d", &n, &s, &w);
	for (i = 1; i <= n; i++)
		foot[i].clear();
	memset(avoid, 0, sizeof(avoid));
	for (i = 0; i < w; i++) {
		scanf("%d", &x);
		for (j = 0; j < x; j++) {
			scanf("%d", &xi);
			if (!avoid[xi][i]) foot[xi].push_back(i), avoid[xi][i] = 1;
		}
	}
	memset(need, 0, sizeof(need));
	for (i = 1; i <= n; i++) {
		int sz = foot[i].size();
		if (sz >= s) return -1;
		need[i][i] = sz;
		memset(has, 0, sizeof(has));
		for (k = 0; k < sz;k++)
			has[foot[i][k]] = 1;
		for (j = i + 1; j < i + s && j <= n; j++) {
			for (k=0; k <  foot[j].size(); k++)
				if (!has[foot[j][k]]) has[foot[j][k]] = 1, sz++;
			if (sz + j - i + 1 > s) need[i][j] = INF;
			else need[i][j] = sz;
 
		}
	}
	dp[0] = 0;
	for (i = 1; i <= n; i++)
		dp[i] = INF;
	for (i = 0; i <= n; i++) {
		for (j = i; j <= i + s; j++) {
			if (need[i + 1][j] + j - i > s) break;
			dp[j] = min(dp[j], dp[i] + need[i + 1][j]);
		}
	}
 
	return dp[n];
}
int main() {
	freopen("in.txt", "r", stdin);
	int T, ca = 1;
	scanf("%d", &T);
	while (T--)
		printf("Case %d: %d\n", ca++, solve());
 
	return 0;
}
