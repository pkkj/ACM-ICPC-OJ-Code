// 2008 Jakarta: Jollybee Tournament
// ACM-ICPC Live Archive 4147
#include <cstdio>
#include <cstring>
#define N 1050
 
int num[N];
bool temp[N];
void solve() {
	int n, m, i, j, ans = 0, tot, x;
	scanf("%d%d", &n, &m);
	memset(temp, 0, sizeof(temp));
	for (i = 0; i < m; i++) {
		scanf("%d", &x);
		temp[x - 1] = 1;
	}
	m = 0;
	for (i = 0; i < (1 << n); i++)
		if (temp[i] == 0) num[m++] = i;
	for (i = 0; i < n; i++) {
		tot = 0;
		for (j = 0; j < m; j++) {
			if (j + 1 < m && (num[j] ^ 1) == num[j + 1]) {
				num[tot++] = num[j] / 2;
				j++;
			} else {
				ans++;
				num[tot++] = num[j] / 2;
			}
		}
		m = tot;
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}