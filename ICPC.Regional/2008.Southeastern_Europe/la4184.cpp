// 2008 Southeastern Europe: Sky Code
// ACM-ICPC Live Archive 4184

#include <cstdio>
#include <cstring>
#include <cmath>
#define N 10005
long long c4[N];
int sum[N], pp[35], pc, ptx[N];
int m;
bool ji[N];
const int maxsz = 10005;
const int maxsz2 = maxsz / 2;
const int maxsqrt = sqrt(double(maxsz)) / 2;
 
char PR[N / 16 + 2];
int prt[N], prcnt;
 
int isprime(int n) {
	return ((n & 1) || (2 == n)) && (PR[(n) >> 4] & (1 << (((n) >> 1) & 7)));
}
void sieve() {
	int i;
	memset(PR, 255, sizeof PR);
	PR[0] = 0xFE;
	for (i = 1; i < maxsqrt; i++)
		if (PR[i >> 3] & (1 << (i & 7))) for (int j = i + i + i + 1; j < maxsz2; j += i + i + 1)
			PR[j >> 3] &= ~(1 << (j & 7));
	prt[0] = 2;
	for (i = 3, prcnt = 1; i <= 10005; i += 2)
		if (isprime(i)) prt[prcnt++] = i;
}
int divide(int x) {
	int i, ans = 0;
	for (i = 0; i < prcnt && x > 1; i++) {
		if (x % prt[i] == 0) {
			x /= prt[i];
			if (x % prt[i] == 0) return 0;
			ans++;
		}
	}
	return ans;
}
 
void divide2(int x) {
	int i;
	pc = 0;
	for (i = 0; i < prcnt && x > 1; i++) {
		if (x % prt[i] == 0) {
			pp[pc++] = prt[i];
			while (x % prt[i] == 0)
				x /= prt[i];
		}
	}
}
void init() {
	int i;
	c4[0] = c4[1] = c4[2] = c4[3] = 0;
	for (long long ll = 4LL; ll <= 10000LL; ll++)
		c4[ll] = ll * (ll - 1) * (ll - 2) * (ll - 3) / 24;
	sieve();
	for (m = 0, i = 2; i <= 10005; i++) {
		int ret = divide(i);
		if (ret) {
			ji[m] = ret % 2 == 1, ptx[i] = m;
			m++;
		}
	}
}
 
void solve(int n) {
	int i, j, x;
	memset(sum, 0, sizeof(sum));
	long long ans = c4[n];
	while (n--) {
		scanf("%d", &x);
		divide2(x);
		for (i = 0; i < (1 << pc); i++) {
			int mask = i, tmp = 1;
			j = 0;
			for (; mask; mask >>= 1, j++)
				if (mask & 1) tmp *= pp[j];
			if (tmp != 1) sum[ptx[tmp]]++;
		}
	}
	for (i = 0; i < m; i++) {
		if (ji[i]) ans -= c4[sum[i]];
		else ans += c4[sum[i]];
	}
	printf("%lld\n", ans);
}
int main() {
	int n;
	init();
	while (scanf("%d", &n) != EOF)
		solve(n);
	return 0;
}