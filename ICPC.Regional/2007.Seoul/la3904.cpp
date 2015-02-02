// 2007 Seoul: Tile Code
// ACM-ICPC Live Archive 3904
#include <cstdio>
#include <cstring>
#define N 35
long long f[N], s[N];
void pre() {
	int i;
	f[1] = 1, f[2] = 3;
	for (i = 3; i <= 30; i++)
		f[i] = f[i - 2] * 2 + f[i - 1];
	for (i = 3; i <= 30; i++) {
		if (i % 2) s[i] = f[(i - 1) / 2];
		else s[i] = 2 * f[(i - 2) / 2] + f[i / 2];
	}
}
int main() {
	pre();
	int T, x;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &x);
		printf("%lld\n", (s[x] + f[x]) / 2);
	}
	return 0;
}