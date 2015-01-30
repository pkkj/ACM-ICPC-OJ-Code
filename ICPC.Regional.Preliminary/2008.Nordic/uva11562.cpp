// 2008 Nordic: Hard Evidence
// UVA 11562
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define N 205
#define EPS 1e-7

#define PI 3.1415926535897932
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("[%.3lf %.3lf]\n", x, y);
	}
	POINT() {
	}
	POINT(double x, double y) :
			x(x), y(y) {
	}
};
struct SEG {
	double a, b;
	SEG() {
	}
	SEG(double a, double b) :
			a(a), b(b) {
	}
	bool operator<(const SEG &s) const {
		return a < s.a;
	}
	void print() {
		printf("(%.3lf %.3lf)\n", a / PI * 180, b / PI * 180);
	}

};
void fix(double &x) {
	if (x < 0)
		x += 2 * PI;
	else if (x >= 2 * PI)
		x -= 2 * PI;
}

int n;
double r;
POINT pl[N];
vector<SEG> hu[N];
vector<SEG> sunion(vector<SEG> a, vector<SEG> b) {
	int i, j;
	SEG t1, t2;
	vector<SEG> ans;
	for (i = 0; i < (int) a.size(); i++)
		for (j = 0; j < (int) b.size(); j++) {
			t1 = a[i], t2 = b[j];
			if (t1.a > t2.a)
				swap(t1, t2);
			if (t1.b > t2.a)
				ans.push_back(SEG(t2.a, min(t1.b, t2.b)));
		}
	return ans;
}

void gethu(POINT &a, POINT &b, int idx) {
	double A, B, C, x1, x2, dx, dy;
	dx = b.x - a.x, dy = b.y - a.y;
	A = dx * dx + dy * dy;
	B = 2 * dx * a.x + 2 * dy * a.y;
	C = a.x * a.x + a.y * a.y - r * r;
	double del = sqrt(B * B - 4 * A * C);
	x1 = (-B - del) / 2.0 / A;
	x2 = (-B + del) / 2.0 / A;
	POINT ia = POINT(a.x + dx * x1, a.y + dy * x1);
	POINT ib = POINT(a.x + dx * x2, a.y + dy * x2);
	double ha = atan2(ia.y, ia.x);
	double hb = atan2(ib.y, ib.x);
	fix(ha), fix(hb);
	hu[idx].clear();
	if (ha > hb) {
		hu[idx].push_back(SEG(ha, 2 * PI));
		hu[idx].push_back(SEG(0, hb));
	} else
		hu[idx].push_back(SEG(ha, hb));

}
double sqr(double x) {
	return x * x;
}
double dot(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
double F(double x, const POINT &p1, const POINT &p2) {
	POINT o = POINT(cos(x) * r, sin(x) * r);
	double d1 = sqrt(sqr(p1.x - o.x) + sqr(p1.y - o.y));
	double d2 = sqrt(sqr(p2.x - o.x) + sqr(p2.y - o.y));
	return dot(o, p1, p2) / d1 / d2;
}

double tri(SEG s, const POINT &p1, const POINT &p2) {
	double l, r, m1, m2;
	l = s.a, r = s.b;
	while (l + EPS < r) {
		m1 = l + (r - l) / 3.0;
		m2 = r - (r - l) / 3.0;
		double y1 = F(m1, p1, p2), y2 = F(m2, p1, p2);
		if (y1 < y2)
			r = m2;
		else
			l = m1;
	}
	double ans = F(l, p1, p2);
	return ans;

}
void solve() {
	int i, j, k;
	double ans = 1000;
	for (i = 0; i < n; i++)
		pl[i].get();
	for (i = 0; i < n; i++) {
		POINT a = pl[i], b = pl[(i + 1) % n];
		gethu(a, b, i);
	}
	for (i = 0; i < n; i++) {
		vector<SEG> co = hu[i];
		for (j = (i + 1) % n; j % n != i; j = (j + 1) % n) {
			for (k = 0; k < (int) co.size(); k++) {
				double t = tri(co[k], pl[i], pl[j]);
				ans = min(ans, t);
			}
			co = sunion(co, hu[j]);
			if (co.size() >= 2 && sgn(co[co.size() - 2].b - co[co.size() - 1].a) == 0) {
				co[co.size() - 22].b = co[co.size() - 1].b;
				co.pop_back();
			}
			if (!co.size())
				break;
		}
	}
	printf("%.7lf\n", acos(ans));
}
int main() {
	while (scanf("%d%lf", &n, &r) != EOF)
		solve();
	return 0;
}
