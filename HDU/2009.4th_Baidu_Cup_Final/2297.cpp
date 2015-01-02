// HDU 2297
// The 4th Baidu Cup Final: Run
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define EPS 1e-15
#define N 50005
int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator /(const double & v) {
		return POINT(x / v, y / v);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
	bool operator ==(const POINT &p) {
		return sgn(p.x -x)==0 && sgn(p.y -y)==0;
	}
	void print() {
		printf("(%.3lf %.3lf) ", x, y);
	}
};
struct LINE {
	POINT a, b;
	LINE() {
	}
	LINE(double x1, double y1, double x2, double y2) :
		a(x1, y1), b(x2, y2) {
	}
};
 
double cross(POINT &p, POINT &a, POINT &b) {
	return (a.x - p.x) * (b.y - p.y) - (b.x - p.x) * (a.y - p.y);
}
int at[N];
LINE ls[N];
bool cmp(int i, int j) {
	if (at[i] - at[j] == 0) return sgn(cross(ls[j].a, ls[j].b, ls[i].b)) >= 0;
	return at[i] < at[j];
}
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return -1;
}
bool notin(int x, int y, int z) {
	POINT pt;
	line_inter(ls[x].a, ls[x].b, ls[y].a, ls[y].b, pt);
	return sgn(cross(ls[z].a, ls[z].b, pt)) < 0;
}
int ord[N], dq[N];
void halfplane(int n) {
	int i, tn, bot, top;
	POINT tt, pre = POINT(-1, -1);
	for (i = 0; i < n; i++)
		ord[i] = i;
	sort(ord, ord + n, cmp);
	for (i = tn = 1; i < n; i++)
		if (at[ord[i]] - at[ord[i - 1]]) ord[tn++] = ord[i];
	bot = 1, top = 2, n = tn;
	dq[bot] = ord[0], dq[top] = ord[1];
	for (i = 2; i < n; i++) {
		while (bot < top && notin(dq[top - 1], dq[top], ord[i]))
			top--;
		dq[++top] = ord[i];
	}
	int ans = top - bot + 1;
	for (i = bot + 1; i <= top; i++) {
		line_inter(ls[dq[i - 1]].a, ls[dq[i - 1]].b, ls[dq[i]].a, ls[dq[i]].b, tt);
		if (tt.x <= 0 || tt == pre) ans--;
		pre = tt;
	}
	printf("%d\n", ans);
}
 
void solve() {
	int n, i;
	double p;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%lf%d", &p, &at[i]);
		ls[i] = LINE(0, p, 30.0, p + 30.0 * at[i]);
	}
	halfplane(n);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
