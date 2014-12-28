// CII 4203
// 2008 Dhaka: Puzzles of Triangles
#include <cstdio>
#include <cstring>
#define BIG 10000005
#define N 10000010
#define M 800000
typedef long long ll;
bool notp[N];
int pr[M], pn;
ll pf[2000];
int pe[2000];
 
void prime() {
	memset(notp, 0, sizeof(notp));
	pn = 0;
	for (int i = 2; i <= BIG; i++) {
		if (!notp[i]) pr[pn++] = i;
		for (int j = 0; j < pn && i * pr[j] <= BIG; j++) {
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
	if (x > 1) {
		pf[cnt] = x, pe[cnt] = 1;
		cnt++;
	}
	return cnt;
}
 
ll n;
ll expl(ll x, int t) {
	ll ans = 1;
	for (int i = 1; i <= t; i++)
		ans *= x;
	return ans;
}
void solve() {
	int cnt = frac(n);
	int i;
	ll k = 1;
	if (cnt == 1 && pe[0] == 1 || cnt == 0) {
		printf("Impossible\n");
		return;
	}
	for (i = 0; i < cnt; i++)
		k *= expl(pf[i], (pe[i] + 1) / 2);
	ll ans = n / k - 1;
	if (ans == 0) printf("Impossible\n");
	else printf("%lld\n", ans * 8);
}
int main() {
	int ca = 1;
	prime();
	while (scanf("%lld", &n) && n) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
