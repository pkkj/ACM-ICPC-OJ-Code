// CII 4682
// 2009 Amritapuri: XOR Sum
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100005
 
unsigned int a[N], xs[N];
 
int son[29 * N][2];
int tot = 1;
void insert(int x) {
	int i, next, cur = 1;
	for (i = 31; i >= 0; i--) {
		unsigned int m = (1 << i);
		next = (x & m) > 0;
		if (son[cur][next] == -1) son[cur][next] = ++tot;
		cur = son[cur][next];
	}
}
 
int ans;
void find(int x) {
	int i, cur = 1, opp = 0;
	for (i = 31; i >= 0; i--) {
		unsigned int m = (1 << i);
		int next = (x & m) > 0;
		if (son[cur][!next] != -1) {
			cur = son[cur][!next];
			if (!next) opp = opp | m;
		} else {
			cur = son[cur][next];
			if (next) opp = opp | m;
		}
	}
	ans = max(ans, opp ^ x);
}
void solve() {
	int n, i;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	xs[0] = 0;
	tot = 1;
	memset(son, -1, sizeof(son));
	for (i = 1; i <= n; i++) {
		xs[i] = xs[i - 1] ^ a[i];
		insert(xs[i]);
	}
	ans = 0;
	for (i = 0; i <= n; i++)
		find(xs[i]);
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
