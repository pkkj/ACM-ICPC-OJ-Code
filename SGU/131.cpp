// SGU 131 Hardwood floor
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 9
long long f[2][1 << N];
int n, m, t;
void dfs(int p, int s1, int s2, int b1, int b2) {
	if (p == m) {
		// When p == m, check whether b1 == 0 and b2 == 0 before counting. No piece could exceed the floors.
		if (!b1 && !b2) f[t][s1] += f[!t][s2];
		return;
	}
	if (!b1 && !b2) {
		// Tiling 1
		dfs(p + 1, (s1 << 1) | 1, s2 << 1, 0, 0);
		// Tiling 2
		dfs(p + 1, (s1 << 1) | 1, s2 << 1, 1, 0);
		// Tiling 3
		dfs(p + 1, (s1 << 1) | 1, s2 << 1, 0, 1);
	}
	if (!b1) {
		// Tiling 4
		dfs(p + 1, (s1 << 1) | 1, ((s2 << 1) | 1) - b2, 1, 0);
		// Tiling 5
		dfs(p + 1, (s1 << 1) | 1, ((s2 << 1) | 1) - b2, 1, 1);
	}
	// Tiling 6
	if (!b2) dfs(p + 1, (s1 << 1) + b1, s2 << 1, 1, 1);
	// Tiling 7
	dfs(p + 1, (s1 << 1) + b1, ((s2 << 1) | 1) - b2, 0, 0);
}
int main() {
	memset(f, 0, sizeof(f));
	scanf("%d%d", &n, &m);
	if (m > n) swap(n, m);
	f[0][(1 << m) - 1] = 1;
	t = 1;
	for (int i = 1; i <= n; i++, t = !t) {
		memset(f[t], 0, sizeof(f[t]));
		dfs(0, 0, 0, 0, 0);
	}
	printf("%lld\n", f[!t][(1 << m) - 1]);
	return 0;
}
