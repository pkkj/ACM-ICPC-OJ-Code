// 2008 Amritapuri: Paper Presentation
// CII 4333
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 20
 
// Union set
int fa[N];
 
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
void init(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i;
}
void sunion(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) fa[x] = y;
}
// End of union set
char cmd[N];
bool G[N][N], vis[N];
int toposize[N], bid, n;
vector<int> block[N];
long long A[N];
void precalc() {
	long long i;
	A[1] = 1;
	for (i = 2; i <= 8; i++)
		A[i] = A[i - 1] * i;
}
long long calc(int st, int mask) {
	long long s1, s2, sum = 0;
	int i;
	s1 = s2 = 1;
	for (i = 0; i < bid; i++) {
		if ((st & (1 << i)) == (mask << i)) {
			sum += (int) block[i].size();
			s1 *= toposize[i];
			s2 *= A[(int) block[i].size()];
		}
	}
	if (sum != n / 2) return 0;
	return A[sum] / s2 * s1;
}
long long solve() {
	int i, j, k;
	long long ans;
	scanf("%d", &n);
	n *= 2;
	bid = 0;
	for (i = 0; i < n; i++) {
		scanf("%s", cmd);
		for (j = 0; j < n; j++)
			G[i][j] = cmd[j] == 'Y';
	}
	init(n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			if (G[i][j]) sunion(i, j);
	}
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < n; i++) {
		if (vis[i]) continue;
		block[bid].clear();
		block[bid].push_back(i);
		vis[i] = 1;
		for (j = i + 1; j < n; j++) {
			if (find(i) == find(j)) {
				block[bid].push_back(j);
				vis[j] = 1;
			}
		}
		if ((int) block[bid].size() > n / 2) return 0;
		bid++;
	}
	for (i = 0; i < bid; i++) {
		sort(block[i].begin(), block[i].end());
		toposize[i] = 0;
		do {
			int ok = 1;
			for (j = 0; j < (int) block[i].size() && ok; j++)
				for (k = j + 1; k < (int) block[i].size() && ok; k++) {
					int x = block[i][j], y = block[i][k];
					if (G[y][x]) ok = 0;
				}
			toposize[i] += ok;
		} while (next_permutation(block[i].begin(), block[i].end()));
		if (!toposize[i]) return 0;
	}
	ans = 0;
	for (i = 1; i < (1 << bid); i++)
		ans += calc(i, 0) * calc(i, 1);
	return ans;
}
int main() {
	int T;
	precalc();
	scanf("%d", &T);
	while (T--)
		printf("%lld\n", solve());
	return 0;
}