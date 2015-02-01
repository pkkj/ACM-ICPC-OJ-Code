// 2008 Kuala Lumpur: Triangle Hazard
// ACM-ICPC Live Archive 4413
#include <cstdio>
#include <cmath>
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("%.8lf %.8lf ", x, y);
	}
};
double dis(POINT &a, POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
 
POINT menelause(POINT p, POINT q, POINT r, double m1, double m2, double m3, double m4, double m5, double m6) {
	POINT ans;
	double L, k1, k2, x;
	L = dis(q, p);
	k1 = (m5 / m6) * (m1 + m2) / m2;
	k2 = (m1 + m2) / m1 * (m4 / m3);
	k1 = 1 / k1, k2 = 1 / k2;
	x = (L + k2 * L) / (k1 - k2);
	ans.x = (r.x - p.x) * (x + L) / L + p.x;
	ans.y = (r.y - p.y) * (x + L) / L + p.y;
	return ans;
}
void solve() {
	POINT p, q, r;
	double m1, m2, m3, m4, m5, m6;
	p.get();
	q.get();
	r.get();
	scanf("%lf%lf%lf%lf%lf%lf", &m1, &m2, &m3, &m4, &m5, &m6);
	menelause(p, q, r, m1, m2, m3, m4, m5, m6).print();
	menelause(q, r, p, m3, m4, m5, m6, m1, m2).print();
	menelause(r, p, q, m5, m6, m1, m2, m3, m4).print();
	printf("\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}