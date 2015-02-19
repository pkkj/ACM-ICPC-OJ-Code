// 2008 Southeastern Europe: Internet Service Providers
// ACM-ICPC Live Archive 4191

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main() {
	freopen("in.txt", "r", stdin);
	long long n, c, t, ans, tt, u;
	while (scanf("%lld%lld", &n, &c) != EOF) {
		if (n == 0 || c == 0) {
			printf("0\n");
			continue;
		}
		tt = c / (2 * n);
		tt += 1, ans = tt * (c - tt * n);
		t = tt;
		tt -= 1;
		u = tt * (c - tt * n);
		if (u >= ans) ans = u, t = tt;
		tt -= 1;
		u = tt * (c - tt * n);
		if (u >= ans) ans = u, t = tt;
		printf("%lld\n", t);
	}
	return 0;
}