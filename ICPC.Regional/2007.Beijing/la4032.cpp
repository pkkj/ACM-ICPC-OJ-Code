// 2007 Beijing: Jewel Trading
// ACM-ICPC Live Archive 4032
#include <cstdio>
#include <cstring>
#include <cmath>
#define EPS 1e-3
double a, b, pre;
int n;
 
double F(double x) {
	return pre + (x - pre) / (1 + pow((x - a), b));
}
double trois() {
	double l, r, m, mm;
	l = pre, r = 1e5;
	while (l + EPS < r) {
		m = (l + r) / 2;
		mm = (m + r) / 2;
		double y1 = F(m), y2 = F(mm);
		if (y1 >= y2) r = mm;
		else l = m;
	}
	double m1 = F(ceil(m)), m2 = F(floor(m));
	return m1 > m2 ? m1 : m2;
}
 
void solve() {
	int i;
	scanf("%lf%lf", &a, &b);
	pre = a;
	for (i = 0; i < n - 1; i++)
		pre = trois();
	printf("%.2lf\n", pre);
}
int main() {
	int T = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", T++);
		solve();
	}
	return 0;
}