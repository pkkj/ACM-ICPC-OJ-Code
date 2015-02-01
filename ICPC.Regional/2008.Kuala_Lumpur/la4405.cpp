// 2008 Kuala Lumpur: Tariff Plan
// ACM-ICPC Live Archive 4405
#include <cstdio>
#include <cstring>
 
void solve() {
	int s1 = 0, s2 = 0, n, l, x;
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &l);
		x = (l + 30) / 30;
		s1 += x * 10;
		x = (l + 60) / 60;
		s2 += x * 15;
	}
	if (s1 < s2) printf("Mile %d\n", s1);
	else if (s2 < s1) printf("Juice %d\n", s2);
	else printf("Mile Juice %d\n", s1);
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}