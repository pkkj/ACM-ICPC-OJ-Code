// 2009 Nordic: Beacons
// HDU 3146

#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;
#define N 1005
#define PI 3.141592653589
#define EPS 1e-8
int n, m;
struct POINT {
	double x, y, r;
	void get1() {
		scanf("%lf%lf", &x, &y);
	}
	void get2() {
		scanf("%lf%lf%lf", &x, &y, &r);
	}
};
POINT mo[N], ba[N];

int sgn(double x) {
	return x < -EPS ? -1 : x > 0;
}
// Union set
int fa[N];
void init(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i;
}
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
void sunion(int x, int y) {
	x = find(x), y = find(y);
	fa[x] = y;
}
// End of union set
struct EVENT {
	int type;
	double ang, dis;
	int id;
	EVENT() {
	}
	EVENT(int type, double ang, double dis) :
		type(type), ang(ang), dis(dis) {
	}
	EVENT(int type, double ang, double dis, int id) :
		type(type), ang(ang), dis(dis), id(id) {
	}
};
EVENT el[N * 5];
int ranking[N * 5];
void fixang(double &x) {
	if (x < 0) x += 2 * PI;
	if (x > 2 * PI) x -= 2 * PI;
}
double sqr(double x) {
	return x * x;
}
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
void getang(POINT &o, POINT &p, double &a1, double &a2, double &dd) {
	double dop;
	double a = atan2(p.y - o.y, p.x - o.x);
	dop = dis(o, p);
	double delta = asin(p.r / dop);
	dd = sqrt(dop * dop - p.r * p.r);
	a1 = a - delta, a2 = a + delta;
	fixang(a1), fixang(a2);
}
bool cmp(int a, int b) {
	if (sgn(el[a].ang - el[b].ang) == 0) return el[a].type < el[b].type;
	return el[a].ang < el[b].ang;
}
void make(int idx) {
	int tot = 0, i, j;
	double mim2pi = 1e30;
	for (i = 0; i < m; i++) {
		double a1, a2, dd;
		getang(ba[idx], mo[i], a1, a2, dd);
		if (a1 < a2) {
			el[tot++] = EVENT(0, a1, dd);
			el[tot++] = EVENT(2, a2, dd);
		}
		else {
			el[tot++] = EVENT(0, a1, dd);
			el[tot++] = EVENT(2, 2 * PI, dd);
			el[tot++] = EVENT(0, 0, dd);
			el[tot++] = EVENT(2, a2, dd);
			mim2pi = min(dd, mim2pi);
		}
	}
	for (i = 0; i < n; i++) {
		if (i == idx) continue;
		double ang = atan2(ba[i].y - ba[idx].y, ba[i].x - ba[idx].x);
		fixang(ang);
		el[tot++] = EVENT(1, ang, dis(ba[i], ba[idx]), i);
	}
	for (i = 0; i < tot; i++)
		ranking[i] = i;
	sort(ranking, ranking + tot, cmp);
	multiset<double> S;
	for (i = 0; i < tot; i++) {
		j = ranking[i];
		if (el[j].type == 0) {
			S.insert(el[j].dis);
		}
		else if (el[j].type == 1) {
			if (sgn(el[j].ang - 2 * PI) == 0 || sgn(el[j].ang) == 0) {
				if (el[j].dis <= mim2pi) sunion(el[j].id, idx);
			}
			else if ((int)S.size() == 0 || ((int)S.size() > 0 && el[j].dis <= *S.begin())) {
				sunion(el[j].id, idx);
			}
		}
		else if (el[j].type == 2) S.erase(el[j].dis);
	}
}

int main() {
	int i;
	while (~scanf("%d%d", &n, &m)){
		for (i = 0; i < n; i++)
			ba[i].get1();
		for (i = 0; i < m; i++)
			mo[i].get2();
		init(n);
		for (i = 0; i < n; i++)
			make(i);
		set<int> ans;
		for (i = 0; i < n; i++)
			ans.insert(find(i));
		printf("%d\n", ans.size() - 1);
	}
	return 0;
}