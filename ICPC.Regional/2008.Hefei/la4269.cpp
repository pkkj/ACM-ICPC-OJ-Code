// 2008 Hefei: A Simple Game
// ACM-ICPC Live Archive 4269

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 30005
int a[N], n, t;
int gcd(int m, int n) {
	int r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
int bin1(int x) {
	int l = 0, r = n - 1, m;
	if (x * a[n - 1] <= t) return 0;
	if (x * a[0] > t) return n;
	while (l < r) {
		m = (l + r) >> 1;
		if (a[m] * x <= t) {
			l = m + 1;
			if (a[l] * x > t) {
				m++;
				break;
			}
		} else {
			r = m;
			if (a[m - 1] * x <= t) break;
		}
	}
	return n - m;
}
int bin2(int x) {
	int l = 0, r = n - 1, m;
	if (x * a[n - 1] > t) return n;
	if (x * a[0] <= t) return 0;
	while (l < r) {
		m = (l + r) >> 1;
		if (a[m] * x <= t) {
			r = m - 1;
			if (a[r] * x > t) {
				m--;
				break;
			}
		} else {
			l = m;
			if (a[m + 1] * x <= t) break;
		}
	}
	return m + 1;
}
void solve() {
	int i, ans = 0, dd;
	for (i = 0; i < n; i++)
		scanf("%d", a + i);
	sort(a, a + n);
	if (n == 1) {
		if (a[0] * a[0] > t) printf("1/1\n");
		else printf("0/1\n");
		return;
	}
	for (i = 0; i < n; i++) {
		if (a[i] >= 0) ans += bin1(a[i]);
		else ans += bin2(a[i]);
	}
	dd = gcd(ans, n * n);
	printf("%d/%d\n", ans / dd, n * n / dd);
}
int main() {
	int T = 0;
	while (scanf("%d%d", &n, &t) && n) {
		printf("Case %d: ", ++T);
		solve();
	}
	return 0;
}
