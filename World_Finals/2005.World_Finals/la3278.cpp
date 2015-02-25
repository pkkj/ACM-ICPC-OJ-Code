// 2005 World Finals: Zones
// ACM-ICPC Live Archive 3278

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 25
struct NODE {
	bool has[N];
	int x, sz;
	void get() {
		scanf("%d", &sz);
		memset(has, 0, sizeof(has));
		for (int i = 0; i < sz; i++) {
			scanf("%d", &x);
			has[x - 1] = 1;
		}
		scanf("%d", &x);
	}
};
NODE nl[N];
bool cho[N];
int n, m, num[N], co, best;
vector<int> ans;
void dfs(int x, int u) {
	int i, j;
	vector<int> tmp;
	if (n - x + u < m) return;
	if (u == m || x == n) {
		int cur = 0;
		bool tb[N] = { 0 };
		for (i = 0; i < n; i++)
			if (cho[i]) {
				cur += num[i];
				for (j = 0; j < co; j++)
					if (nl[j].has[i]) tb[j] = 1;
			}
		for (j = 0; j < co; j++)
			if (tb[j]) cur += nl[j].x;
		if (cur > best) {
			for (i = 0; i < n; i++)
				if (cho[i]) tmp.push_back(i);
			ans = tmp;
			best = cur;
		} else if (cur == best) {
			bool ch = 1;
			for (i = 0; i < n; i++)
				if (cho[i]) tmp.push_back(i);
			for (i = 0; i < (int) min(tmp.size(), ans.size()); i++)
				if (tmp[i] > ans[i]) ch = 0;
			if (ch) ans = tmp;
		}
		return;
	}
	// Choose
	cho[x] = 1;
	dfs(x + 1, u + 1);
	// Not choose
	cho[x] = 0;
	dfs(x + 1, u);
}
void solve() {
	int i, j;
	for (i = 0; i < n; i++)
		scanf("%d", &num[i]);
	scanf("%d", &co);
	for (i = 0; i < co; i++)
		nl[i].get();
	for (i = 0; i < n; i++)
		for (j = 0; j < co; j++)
			if (nl[j].has[i]) num[i] -= nl[j].x;
	best = 0;
	memset(cho, 0, sizeof(cho));
	dfs(0, 0);
	printf("Number of Customers: %d\n", best);
	printf("Locations recommended:");
	for (i = 0; i < (int) ans.size(); i++)
		printf(" %d", ans[i] + 1);
	printf("\n\n");
}
int main() {
	int ca = 1;
	while (scanf("%d%d", &n, &m) && n + m) {
		printf("Case Number  %d\n", ca++);
		solve();
	}
	return 0;
}