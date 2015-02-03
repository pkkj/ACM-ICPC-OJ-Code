// 2009 Phuket: Airplane Parking
// ACM-ICPC Live Archive 4712
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 305
struct RANGE {
	int b, e;
	void get() {
		scanf("%d%d", &b, &e);
	}
};
int va[N], n, tt[N * 2], st[N], dp[N * 2];
RANGE ra[N];
int getv(int id) {
	if (va[id] != -1) return va[id];
	int can[N], tot = 0, i, j, begin, end;
	begin = ra[id].b, end = ra[id].e;
	for (i = 0; i < n; i++)
		if (i != id && ra[i].b >= begin && ra[i].e <= end) {
			can[tot++] = i;
			getv(i);
		}
	dp[begin] = 0;
	for (i = begin + 1; i <= end; i++) {
		dp[i] = dp[i - 1];
		for (j = 0; j < tot; j++)
			if (ra[can[j]].e == i)
				dp[i] = max(dp[i], dp[ra[can[j]].b] + va[can[j]]);
	}
	int ans = 0;
	for (i = begin; i <= end; i++)
		ans = max(dp[i], ans);
	return va[id] = ans + st[id];
}
 
void solve() {
	int i, j = 0, tot = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		int re = 0;
		ra[tot].get();
		st[tot] = 1;
		for (j = 0; j < tot; j++)
			if (ra[j].b == ra[tot].b && ra[j].e == ra[tot].e) {
				re = 1;
				break;
			}
		if (re) st[j]++;
		else tot++;
		tt[i * 2] = ra[i].b, tt[i * 2 + 1] = ra[i].e;
	}
	n = tot;
	sort(tt, tt + 2 * n);
	tot = unique(tt, tt + 2 * n) - tt;
	for (i = 0; i < n; i++) {
		ra[i].b = lower_bound(tt, tt + tot, ra[i].b) - tt + 1;
		ra[i].e = lower_bound(tt, tt + tot, ra[i].e) - tt + 1;
	}
	st[n] = 0;
	ra[n].b = 1, ra[n].e = tot + 1;
	memset(va, -1, sizeof(va));
	printf("%d\n", getv(n));
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}