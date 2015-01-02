// CII 4304
// 2008 Southwestern Europe: Transcribed Books
#include <cstdio>
typedef long long ll;
 
ll gcd(ll m, ll n) {
	ll r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
 
void solve() {
	ll max = 0, x, gc = 0;
	int i, j, n;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		ll sum = 0;
		for (j = 0; j < 9; j++) {
			scanf("%lld", &x);
			sum += x;
		}
		scanf("%lld", &x);
		if (x > max) max = x;
		sum -= x;
		if (sum < 0) sum = -sum;
		gc = gcd(sum, gc);
	}
	if (gc <= 1 || gc <= max) printf("impossible\n");
	else printf("%lld\n", gc);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
