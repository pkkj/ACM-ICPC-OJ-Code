// CII 5072
// 2010 Tokyo: Find the Multiples
#include <cstdio>
#include <cstring>
using namespace std;
 
// Hash table
struct HASHNODE {
	int st, next, v;
};
#define MOD 1000003
HASHNODE HE[MOD];
int HG[MOD], htot;
void hinit() {
	htot = 0;
	memset(HG, -1, sizeof(HG));
}
int insert(int x) {
	int i, p = x % MOD;
	for (i = HG[p]; ~i; i = HE[i].next)
		if (HE[i].st == x) return i;
	HASHNODE e = { x, HG[p], 0 };
	HG[p] = htot;
	HE[htot++] = e;
	return htot - 1;
}
 
// End of Hash table
#define N 100005
int a[N];
int main() {
	int n, s, w, q;
	while (scanf("%d%d%d%d", &n, &s, &w, &q) && n) {
		int g = s, i;
		// Generate the sequence
		for (i = 0; i < n; i++) {
			a[i] = (g / 7) % 10;
			if (g % 2 == 0) {
				g = (g / 2);
			} else {
				g = (g / 2) ^ w;
			}
		}
		hinit();
		int re = 0, mul = 1, ans = 0, cnt = 0;
		for (i = n - 1; i >= 0; i--) {
			if (q == 2 || q == 5) {
				if (a[i] % q == 0) cnt++;
				if (a[i]) ans += cnt;
			} else {
				re = (re + mul * a[i]) % q;
				mul = mul * 10 % q;
				cnt = ++HE[insert(re)].v;
				if (a[i]) {
					ans += cnt;
					if (re) ans--;
				}
			}
 
		}
		printf("%d\n", ans);
	}
	return 0;
}
