// 2006 Dhaka: Potentiometers
// ACM-ICPC Live Archive 2191
#include <cstdio>
#include <cstring>
 
#define N 200005
typedef long long ll;
#define lowbit(x) (x&(x^(x-1)))
ll C[N];
int n;
void modify(int pos, ll d) {
	while (pos <= n)
		C[pos] += d, pos += lowbit(pos);
}
ll query(int pos) {
	ll sum = 0;
	while (pos > 0)
		sum += C[pos], pos -= lowbit(pos);
	return sum;
}
 
ll base[N];
 
int main() {
	int i, ca = 1;
	while (scanf("%d", &n) && n) {
		char cmd[10];
		if (ca != 1) printf("\n");
		printf("Case %d:\n", ca++);
		memset(C, 0, sizeof(C));
		for (i = 1; i <= n; i++) {
			scanf("%lld", base + i);
			modify(i, base[i]);
		}
		while (scanf("%s", cmd) && cmd[0] != 'E') {
			int a, b;
			long long x;
			if (cmd[0] == 'S') {
				scanf("%d%lld", &a, &x);
				modify(a, x - base[a]);
				base[a] = x;
			} else if (cmd[0] == 'M') {
				scanf("%d%d", &a, &b);
				printf("%lld\n", query(b) - query(a - 1));
			}
		}
	}
	return 0;
}