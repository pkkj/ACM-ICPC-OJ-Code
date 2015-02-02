// 2007 Dhaka: The Bells are Ringing
// ACM-ICPC Live Archive 4060
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1000011
#define BIG 1000000
#define M 80000
bool notp[N];
int pr[M], pn;
int pf[500], pe[500];
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
ll lcm(ll a, ll b) {
	if (a == 0 || b == 0) return 0;
	return a / gcd(a, b) * b;
}
 
void prime() {
	memset(notp, 0, sizeof(notp));
	pn = 0;
	for (int i = 2; i < N; i++) {
		if (!notp[i]) pr[pn++] = i;
		for (int j = 0; j < pn && i * pr[j] < N; j++) {
			int k = i * pr[j];
			notp[k] = 1;
		}
	}
}
 
int frac(ll x) {
	int i, cnt = 0;
	for (i = 0; i < pn; i++) {
		if (pr[i] * pr[i] > x) break;
		if (x % pr[i] == 0) {
			pf[cnt] = pr[i], pe[cnt] = 0;
			while (x % pr[i] == 0) {
				x /= pr[i], pe[cnt]++;
			}
			cnt++;
		}
	}
	if (x <= BIG && x > 1) {
		pf[cnt] = x, pe[cnt] = 1;
		cnt++;
	}
	return cnt;
}
ll x;
int fac[N], cnt, cntf;
void getfactor(int p, ll v) {
	if (v > BIG || v > x) return;
	if (p == cnt) {
		fac[cntf++] = v;
		return;
	}
	ll t = 1;
	for (int i = 0; i <= pe[p]; i++) {
		getfactor(p + 1, t * v);
		t *= pf[p];
	}
}
int solve() {
	int i, j, k, ok = 0;
	cnt = frac(x);
	if (!cnt) return 0;
	cntf = 0;
	getfactor(0, 1);
	sort(fac, fac + cntf);
	for (i = 0; i < cntf; i++) {
		for (j = i + 1; j < cntf; j++) {
			if (fac[j] - fac[i] > 25) break;
			for (k = j + 1; k < cntf; k++) {
				if (fac[k] - fac[i] > 25) break;
				if (lcm(lcm(fac[i], fac[j]), fac[k]) == x) {
					ok = 1;
					printf("%d %d %d\n", fac[i], fac[j], fac[k]);
				}
			}
		}
	}
	return ok;
}
int main() {
	int ca = 1;
	prime();
	while (scanf("%lld", &x) && x) {
		printf("Scenario %d:\n", ca++);
		if (!solve()) printf("Such bells don't exist\n");
		printf("\n");
	}
	return 0;
}