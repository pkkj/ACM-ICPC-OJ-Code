// CII 4206
// 2008 Dhaka: Magic Ring
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define NP 25
#define INF 1<<29
#define EPS 1e-8
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	POINT operator *(double k) {
		return POINT(x * k, y * k);
	}
	POINT operator /(double k) {
		return POINT(x / k, y / k);
	}
	void print() {
		printf("%.3lf %.3lf\n", x, y);
	}
};
POINT operator-(const POINT &p1, const POINT &p2) {
	return POINT((p1.x - p2.x), (p1.y - p2.y));
}
POINT operator+(const POINT &p1, const POINT &p2) {
	return POINT((p1.x + p2.x), (p1.y + p2.y));
}
POINT rotate(const POINT &p, double ca, double sa) {
	POINT ret;
	ret.x = p.x * ca - p.y * sa;
	ret.y = p.x * sa + p.y * ca;
	return ret;
}
double sqr(double x) {
	return x * x;
}
double dis(POINT &p1, POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
void twocircle(POINT &p1, POINT &p2, double R, POINT &a1, POINT &a2) {
	double d1, d2, ca, sa, k;
	POINT mid;
	d1 = dis(p1, p2) / 2;
	d2 = sqrt(R * R - d1 * d1);
	ca = d1 / R;
	sa = d2 / R;
	mid = p2 - p1;
	k = mid.abs();
	mid = mid * R;
	mid = mid / k;
	a1 = rotate(mid, ca, sa);
	a2 = rotate(mid, ca, -sa);
	a1 = a1 + p1;
	a2 = a2 + p1;
}
POINT pl[NP], p2[NP * NP];
int n, k;
 
// Template of dancing link
#define N 25*25
int nn, mm, ans;
struct NODE {
	int R, C;
	NODE *u, *d, *l, *r;
};
NODE head, row[N], col[N], all[N * N];
int tot, size[N];
inline void link(int r, int c) {
	size[c]++;
	NODE *t = &all[tot++];
	t->C = c, t->R = r;
	t->l = &row[r];
	t->r = row[r].r;
	t->l->r = t;
	t->r->l = t;
 
	t->u = &col[c];
	t->d = col[c].d;
	t->d->u = t;
	t->u->d = t;
 
}
 
void init() {
	int i;
	tot = 0;
	memset(size, 0, sizeof(size));
	head.l = head.r = head.d = head.u = &head;
	for (i = 0; i < mm; i++) {
		col[i].C = i;
		col[i].u = col[i].d = &col[i];
		col[i].l = &head;
		col[i].r = head.r;
		col[i].l->r = &col[i];
		col[i].r->l = &col[i];
	}
	for (i = 0; i < nn; i++) {
		row[i].R = i;
		row[i].l = row[i].r = &row[i];
		row[i].u = &head;
		row[i].d = head.d;
		row[i].u->d = &row[i];
		row[i].d->u = &row[i];
	}
}
 
void cover(NODE *p) {
	for (NODE *i = p->d; i != p; i = i->d) {
		i->r->l = i->l;
		i->l->r = i->r;
	}
}
void uncover(NODE *p) {
	for (NODE *i = p->u; i != p; i = i->u) {
		i->r->l = i;
		i->l->r = i;
	}
}
bool hash[N];
int h() {
	int ans = 0;
	NODE *i, *j, *k;
	memset(hash, 0, sizeof(hash));
	for (i = head.r; i != &head; i = i->r) {
		if (hash[i->C]) continue;
		hash[i->C] = 1;
		ans++;
		for (j = i->d; j != i; j = j->d) {
			for (k = j->r; k != j; k = k->r)
				hash[k->C] = 1;
		}
	}
	return ans;
}
int dfs(int x) {
	if (x >= ans || x + h() >= ans) return 0;
	if (head.r == &head) {
		ans = x;
		return 1;
	}
	NODE *i, *j;
	int min = 1 << 29, tc;
	for (i = head.r; i != &head; i = i->r)
		if (size[i->C] < min) min = size[i->C], tc = i->C;
	if (min == 0) return 0;
	for (i = col[tc].d; i != &col[tc]; i = i->d) {
		cover(i);
		for (j = i->r; j != i; j = j->r)
			cover(j);
		if (dfs(x + 1)) return 1;
		for (j = i->l; j != i; j = j->l)
			uncover(j);
		uncover(i);
		if (x + 1 >= ans) return 0;
	}
	return 0;
}
 
// End of dancing link
int check(double R) {
	int i, j, tot = 0;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++) {
			double d = dis(pl[i], pl[j]);
			if(sgn(d)==0)continue;
			if (sgn(d - R * 2) == 0) {
				p2[tot++] = POINT((pl[i].x + pl[j].x) / 2.0, (pl[i].y + pl[j].y) / 2.0);
			} else if (d < R * 2) {
				twocircle(pl[i], pl[j], R, p2[tot], p2[tot + 1]);
				tot += 2;
			}
		}
	for (i = 0; i < n; i++)
		p2[tot++] = pl[i];
	// Build the dancing link map
	nn = tot, mm = n;
	init();
	for (i = 0; i < tot; i++) {
		for (j = 0; j < n; j++) {
			if (dis(p2[i], pl[j]) < R + EPS) {
				link(i, j);
			}
		}
	}
	ans = k + 1;
	for (i = 0; i < nn; i++) {
		row[i].l->r = row[i].r;
		row[i].r->l = row[i].l;
	}
	dfs(0);
	return ans;
}
double solve() {
	int i;
	scanf("%d%d", &n, &k);
	for (i = 0; i < n; i++)
		pl[i].get();
	if (n == 1) return 0;
	double l, r, mid;
	l = 0, r =15000;
	while (l + 1e-4 < r) {
		mid = (l + r) / 2.0;
		int ret = check(mid);
		if (ret > k) l = mid;
		else r = mid;
	}
	return l;
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--)
		printf("Case %d: %.2lf\n", ca++, solve());
}
