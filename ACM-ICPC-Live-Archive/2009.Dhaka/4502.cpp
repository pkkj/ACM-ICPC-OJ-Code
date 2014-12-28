// CII 4502
// 2009 Dhaka: How Many bases?
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define MOD 100000007LL
#define N 10011
#define M 80000
#define NF 500
bool notp[N];
int pr[M], pn;

struct RANGE {
	int a, b;
};
int cnt;
RANGE range[NF];
ll ans;
int t, n, m;
int pf[NF], pe[NF];

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
			while (x % pr[i] == 0)
				x /= pr[i], pe[cnt]++;
			cnt++;
		}
	}
	if (x > 1) {
		pf[cnt] = x, pe[cnt] = 1;
		cnt++;
	}
	return cnt;
}


ll solve() {
	int i, j, sz, tot;
	cnt = frac(n);
	for (i = 0; i < cnt; i++) {
		pe[i] *= m;
		range[i].a = pe[i] / (t + 1) + 1;
		range[i].b = pe[i] / t;
	}
	ans = 0, tot = 1<<cnt;
	for (i = 1; i < tot; i++) {
		sz = 0;
		ll tmp = 1;
		for (j = 0; j < cnt; j++) {
			if (!((1 << j) & i)) tmp = tmp * (range[j].b + 1) % MOD;
			else {
				sz++;
				if (range[j].b >= range[j].a) tmp = tmp * (range[j].b - range[j].a + 1) % MOD;
				else tmp = 0;
			}
		}
		if (sz % 2) ans = (ans + tmp) % MOD;
		else ans = (ans - tmp + MOD) % MOD;
	}

	return ans;
}
int main() {
	int ca = 1;
	freopen("in.txt", "r", stdin);
	prime();
	while (scanf("%d%d%d", &n, &m, &t) && n)
		printf("Case %d: %lld\n", ca++, solve());
	return 0;
}

