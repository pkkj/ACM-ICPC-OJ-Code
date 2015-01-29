// CII 4127
// 2008 World Finals The Sky is the Limit
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define N 105
#define EPS 1e-8
inline int sgn(double x) {
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
};
struct NODE {
	double x, h, b;
	POINT p[3];
	void get() {
		scanf("%lf%lf%lf", &x, &h, &b);
		b /= 2;
		p[0] = POINT(x - b, 0), p[1] = POINT(x, h), p[2] = POINT(x + b, 0);
	}
};
 
inline double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
 
bool line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	cp = (c * v + d * u) / (u + v);
	return cp.x >= min(a.x, b.x) && cp.x <= max(a.x, b.x) && cp.y >= min(a.y, b.y) && cp.y <= max(a.y, b.y);
}
double dis(POINT &a, POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int n;
double num[N * N * 2];
POINT ph[N * N * 2], pl[N * N * 2];
NODE mo[N];
vector<double> intersect(NODE &a, NODE &b) {
	vector<double> ans;
	POINT it;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (line_inter(a.p[i], a.p[i + 1], b.p[j], b.p[j + 1], it)) ans.push_back(it.x);
	return ans;
}
double solve() {
	int i, j, cnt = 0, cnt2, k;
	double ans;
	for (i = 0; i < n; i++) {
		mo[i].get();
		num[cnt++] = mo[i].x, num[cnt++] = mo[i].x - mo[i].b, num[cnt++] = mo[i].x + mo[i].b;
	}
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			vector<double> it = intersect(mo[i], mo[j]);
			for (k = 0; k < (int) it.size(); k++)
				num[cnt++] = it[k];
		}
	sort(num, num + cnt);
	num[cnt] = num[cnt - 1] + 1;
	cnt++;
	for (i = cnt2 = 0; i < cnt - 1; i++)
		if (sgn(num[i] - num[i + 1])) num[cnt2++] = num[i];
 
	memset(ph, 0, sizeof(ph));
	memset(pl, 0, sizeof(pl));
	for (i = 0; i < n; i++) {
		for (k = 0; k < 2; k++) {
			POINT i1, i2;
			for (j = 0; j < cnt2; j++)
				if (sgn(num[j] - mo[i].p[k].x) == 0) break;
			for (; j < cnt2; j++) {
				if (sgn(num[j] - mo[i].p[k + 1].x) == 0) break;
				POINT p1 = POINT(num[j], -100), p2 = POINT(num[j], 100);
				line_inter(mo[i].p[k], mo[i].p[k + 1], p1, p2, i1);
				p1 = POINT(num[j + 1], -100), p2 = POINT(num[j + 1], 100);
				line_inter(mo[i].p[k], mo[i].p[k + 1], p1, p2, i2);
				if (max(i1.y, i2.y) >= ph[j].y - EPS && min(i1.y, i2.y) >= pl[j].y - EPS) {
					ph[j] = i1, pl[j] = i2;
					if (ph[j].y < pl[j].y) swap(ph[j], pl[j]);
				}
			}
		}
	}
	ans = 0;
	for (i = 0; i < cnt2; i++)
		if (sgn(ph[i].y) || sgn(pl[i].y)) ans += dis(ph[i], pl[i]);
	return ans;
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n)
		printf("Case %d: %.0lf\n\n", ca++, solve());
	return 0;
}
