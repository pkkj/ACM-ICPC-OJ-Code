// 2008 Dhaka: Stopping Doom's Day
// ACM-ICPC Live Archive 4209
#include <cstdio>
#define M 10007
typedef long long ll;
ll gcdext(ll a, ll b, ll &x, ll &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	ll r = gcdext(b, a % b, x, y);
	ll t = x;
	x = y;
	y = t - a / b * y;
	return r;
}
ll modular_linear_equation(ll a, ll b, ll n) {
	ll d, x, y;
	d = gcdext(a, n, x, y);
	if (b % d) return -1;
	x *= (b / d);
	x = (x % (n / d) + n / d) % (n / d);
	return x;
}
ll mod_exp(ll a, ll b, ll n) {
	ll hash = 1, factor = a, x = b;
	while (x) {
		if (x & 1) hash = (hash * factor) % n;
		factor = (factor * factor) % n;
		x >>= 1;
	}
	return hash;
}
int main() {
	ll n, ans;
	while (scanf("%lld", &n) != EOF, n) {
		//y = (107/22680)x^10  ＋ (23/-756)x^8  ＋ (71/1080)x^6   ＋(103/-1134)x^4 ＋ (16/315)x^2
		ans = mod_exp(n, 10, M) * 107 * modular_linear_equation(22680, 1, M) % M;
		ans -= mod_exp(n, 8, M) * 23 * modular_linear_equation(756, 1, M) % M;
		ans += mod_exp(n, 6, M) * 71 * modular_linear_equation(1080, 1, M) % M;
		ans -= mod_exp(n, 4, M) * 103 * modular_linear_equation(1134, 1, M) % M;
		ans += mod_exp(n, 2, M) * 16 * modular_linear_equation(315, 1, M) % M;
		ans = (ans + M) % M;
		ans = (ans + M) % M;
		printf("%lld\n", ans);
	}
	return 0;
}
