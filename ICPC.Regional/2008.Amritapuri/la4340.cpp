// 2008 Amritapuri: Find Terrorists
// CII 4340
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstring>
using namespace std;
const int maxsz = 10005;
const int maxsz2 = maxsz / 2;
const int maxsqrt = sqrt(double(maxsz)) / 2;
char a[maxsz / 16 + 2];
 

inline int isprime(int n) {
	return ((n & 1) || (2 == n)) && (a[(n) >> 4] & (1 << (((n) >> 1) & 7)));
}
void sieve() {
	memset(a, 255, sizeof a);
	a[0] = 0xFE;
	for (int i = 1; i < maxsqrt; i++)
		if (a[i >> 3] & (1 << (i & 7))) for (int j = i + i + i + 1; j < maxsz2; j += i + i + 1)
			a[j >> 3] &= ~(1 << (j & 7));
}
#define N 10005
int cnt[N];
int calc(int x) {
	if (cnt[x] != -1) return cnt[x];
	int i, sum = 0;
	for (i = 1; i <= x; i++)
		if (x % i == 0) sum++;
	return cnt[x] = isprime(sum);
}
void solve() {
	int l, h, i, ok = 0;
	scanf("%d%d", &l, &h);
	cnt[1] = 0;
	for (i = l; i <= h; i++) {
		if (calc(i)) {
			if (ok) printf(" ");
			printf("%d", i);
			ok = 1;
		}
	}
	if (!ok) printf("-1");
	printf("\n");
}
int main() {
	sieve();
	int T;
	memset(cnt, -1, sizeof(cnt));
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}