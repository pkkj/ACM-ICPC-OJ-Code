// 2008 Beijing: Priest John's Busiest Day
// ACM-ICPC Live Archive 4328
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
struct NODE {
	long long b, e, m, len;
	bool operator<(const NODE &n) const {
		if (m == n.m) return len > n.len;
		return m < n.m;
	}
};
#define N 100005
NODE ll[N];
int main() {
	int n;
	while (scanf("%d", &n) && n) {
		int ok = 1, i;
		long long end;
		for (i = 0; i < n; i++) {
			scanf("%lld%lld", &ll[i].b, &ll[i].e);
			long long len = ll[i].e - ll[i].b + 1;
			ll[i].m = ll[i].b + len / 2 + len % 2 - 1;
			ll[i].len = len;
		}
		sort(ll, ll + n);
		end = ll[0].m + 1;
		for (i = 1; i < n && ok; i++) {
			end = max(end, ll[i].b) + ll[i].len / 2 + ll[i].len % 2;
			if (end > ll[i].e) ok = 0;
		}
		puts(ok ? "YES" : "NO");
	}
	return 0;
}