// Rocky Mountain 2005: Last Digits
// ACM-ICPC Live Archive 3343
// POJ 2720
#include <cstdio>
#include <cstring>
#define N 100 + 5
typedef long long ll;
ll newmod(ll a, ll b) {
	return a <= b ? a : b + a % b;
}
int phi(int n) {
	int phi = n, i, j;
	for (i = 2, j = 4; j <= n; i++, j += i + i - 1)
		if (!(n % i)) {
			phi = phi / i * (i - 1);
			while (!(n % i))
				n /= i;
		}
	if (n > 1) phi = phi / n * (n - 1);
	return phi;
}

ll mod_exp(ll a, ll b, ll n) {
	ll hash = 1, factor = a, x = b;
	while (x) {
		if (x & 1) hash = newmod(hash * factor, n);
		factor = newmod(factor * factor, n);
		x >>= 1;
	}
	return hash;
}
// Calc B^B^B....^B mod M (The number of B is T)
int calc(ll B, ll T, ll M) {
	if (T == 0) return 1LL;
	int ph = phi(M);
	int t = calc(B, T - 1, ph);//Euler Law:a^b = (a ^ (b mod phi(m)) (mod m)
	return mod_exp(B, t, M);
}
int ans[N][N];
void solve(int b, int i, int n) {
	int x;
	if (ans[b][i] == -1) x = ans[b][i] = calc(b, i, 10000000) % 10000000;
	x = ans[b][i];
	char line[10];
	sprintf(line, "%.7d", x);
	puts(line + (7 - n));

}

int main() {
	//freopen("in.txt", "r", stdin);
	int b, n, i;
	memset(ans, -1, sizeof(ans));
	while (scanf("%d", &b) && b) {
		scanf("%d%d", &i, &n);
		solve(b, i, n);
	}

	return 0;
}
