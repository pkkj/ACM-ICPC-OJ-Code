// 2004 Shanghai: Amphiphilic Carbon Molecules
// POJ 2280
// ACM-ICPC Live Archive 3259
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define PI 3.1415926535897932384626
#define N 1005
#define EPS 1e-12
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct POINT {
	double x, y, a;
	int t;
	void get() {
		scanf("%lf%lf%d", &x, &y, &t);
	}
};
POINT P[N];
int n, ans, na, nb;

double fix(double x) {
	if (x < 0) x += 2 * PI;
	if (sgn(x - 2 * PI) >= 0) x -= 2 * PI;
	return x;
}
void update(int *cn1, int *cn2, int *cnm) {
	int t = cnm[0] + (nb - cn1[1] - cn2[1] - cnm[1]) + cn1[0] + cn1[1] + cn2[0] + cn2[1];
	if (P[0].t == 0) t++;
	ans = max(t, ans);
}
struct EVENT {
	double a;
	short t;
	EVENT() {
	}
	EVENT(double a, int t) :
		a(a), t(t) {
	}
	bool operator <(const EVENT &e) const {
		if (sgn(e.a - a) == 0) return t < e.t;
		return a < e.a;
	}
};
EVENT E[N * 3];
int tot;
inline int next(int x) {
	return (x + 1) % tot;
}
inline int prev(int x) {
	return (x - 1 + tot) % tot;
}
void calc() {
	int i, j, cnm[2] = { 0 }, cn1[2] = { 0 }, cn2[2] = { 0 };
	int p1, p2, p3, p4;
	double cur;
	tot = 0;
	for (i = 1; i < n; i++) {
		double v = atan2(P[i].y - P[0].y, P[i].x - P[0].x);
		E[tot++] = EVENT(fix(v), P[i].t);
		E[tot++] = EVENT(fix(v + PI), -3);
	}
	sort(E, E + tot);
	for (i = j = 0; i < tot; i++) {
			if (E[i].t == -3 && i && E[i - 1].t == -3 && sgn(E[i].a - E[i - 1].a) == 0) continue;
		E[j++] = E[i];
	}
	tot = j;
	for (p1 = 0;; p1 = (p1 + 1) % tot)
		if (E[p1].t == 0 || E[p1].t == 1) {
			cur = E[p1].a;
			break;
		}
	prev(p1);

	for (p2 = (p1 + 1) % tot; sgn(E[p2].a - cur) == 0; p2 = (p2 + 1) % tot) {
		if (E[p2].t == 0 || E[p2].t == 1) cn1[E[p2].t]++;
	}
	p2 = prev(p2);
	for (p3 = (p2 + 1) % tot;; p3 = (p3 + 1) % tot) {
		if (E[p3].t == -3 && sgn(fix(E[p3].a + PI) - cur) == 0) break;
		if (E[p3].t == 0 || E[p3].t == 1) cnm[E[p3].t]++;
	}
	for (p4 = (p3 + 1) % tot; sgn(E[p4].a - E[p3].a) == 0; p4 = (p4 + 1) % tot) {
		if (E[p4].t == 0 || E[p4].t == 1) cn2[E[p4].t]++;
	}
	p4 = prev(p4);
	update(cn1, cn2, cnm);
	double begin = cur;
	for (;;) {
		int pass = 0;
		for (p1 = (p1 + 1) % tot;; p1 = (p1 + 1) % tot) {
			if (sgn(cur - E[p1].a)) pass = 1;
			if (pass && (E[p1].t == 0 || E[p1].t == 1)) {
				cur = E[p1].a;
				break;
			}
			if (E[p1].t == 0 || E[p1].t == 1) cn1[E[p1].t]--;
		}
		p1 = prev(p1);
		if (sgn(begin - cur) == 0) break;
		pass = 0;
		for (p2 = (p2 + 1) % tot;; p2 = (p2 + 1) % tot) {
			if (sgn(E[p2].a - cur) == 0) pass = 1;
			if (pass && sgn(E[p2].a - cur)) break;
			if (E[p2].t == 0 || E[p2].t == 1) cn1[E[p2].t]++, cnm[E[p2].t]--;
		}
		p2 = prev(p2);
		for (p3 = (p3 + 1) % tot;; p3 = (p3 + 1) % tot) {
			if (E[p3].t == -3 && sgn(fix(E[p3].a + PI) - cur) == 0) break;
			if (E[p3].t == 0 || E[p3].t == 1) cnm[E[p3].t]++, cn2[E[p3].t]--;
		}
		pass = 0;
		for (p4 = (p4 + 1) % tot;; p4 = (p4 + 1) % tot) {
			if (p4 == p3) pass = 1;
			if (pass && sgn(E[p4].a - E[p3].a)) break;
			if (E[p4].t == 0 || E[p4].t == 1) cn2[E[p4].t]++;
		}
		p4 = prev(p4);
		update(cn1, cn2, cnm);
	}

}
void solve() {
	int i;
	na = nb = 0;
	for (i = 0; i < n; i++) {
		P[i].get();
		if (P[i].t == 0) na++;
		else nb++;
	}
	if (n <= 3) ans = n;
	else {
		ans = 0;
		for (i = 0; i < n; i++) {
			swap(P[i], P[0]);
			calc();
			swap(P[i], P[0]);
		}
	}
	printf("%d\n", ans);
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
}
