// 2008 Southeastern Europe: Lucky Numbers
// ACM-ICPC Live Archive 4189

#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX  1000000000001LL
using namespace std;
#define N 10100
#define M 1000000
long long ta[N], num[M], S[M];
int p1, p2, p3;
void dfs(long long n, int d) {
	if (d == 12) return;
	ta[p1++] = n;
	dfs(n * 10 + 4, d + 1);
	dfs(n * 10 + 7, d + 1);
}
 
void dfs2(int be, long long x) {
	long long xx, ll;
	int i;
	for (i = be; i < p1; i++) {
		ll = MAX / x;
		if (ll < ta[i]) return;
		xx = x * ta[i];
		num[p2++] = xx;
		dfs2(i, xx);
	}
}
int solve() {
	long long a, b;
	int ans;
	pair<long long *, long long *> pa, pb;
	scanf("%lld%lld", &a, &b);
	pa = equal_range(S, S + p3, a);
	pb = equal_range(S, S + p3, b);
	ans = pb.second - pa.first;
	return ans;
 
}
void init() {
	int i;
	p1 = p2 = p3 = 0;
	dfs(4, 0);
	dfs(7, 0);
	sort(ta, ta + p1);
	dfs2(0, 1);
	sort(num, num + p2);
	for (i = 0; i < p2; i++)
		if (i == 0 || (i && num[i] != num[i - 1])) S[p3++] = num[i];
}
int main() {
	int T;
	init();
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}