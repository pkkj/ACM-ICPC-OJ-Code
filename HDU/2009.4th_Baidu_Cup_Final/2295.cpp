// HDU 2295
// The 4th Baidu Cup Final: Radar
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 55
#define INF 1<<29
#define EPS 1e-8
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
};
double sqr(double x) {
	return x * x;
}
double dis(POINT &p1, POINT &p2) {
	return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}
POINT p1[N], p2[N];
double dd[N][N];
// Template of dancing link
int n, m, k, ans;
struct NODE {
	int R, C;
	NODE *u, *d, *l, *r;
};
NODE head, row[N], col[N], all[N * N];
int tot, size[N];
void link(int r, int c) {
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
	for (i = 0; i < m; i++) {
		col[i].C = i;
		col[i].u = col[i].d = &col[i];
		col[i].l = &head;
		col[i].r = head.r;
		col[i].l->r = &col[i];
		col[i].r->l = &col[i];
	}
	for (i = 0; i < n; i++) {
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
 
int h() {
	int ans = 0;
	NODE *i, *j, *k;
	bool hash[N]= {0};
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
		if (x+1 >= ans) return 0;
	}
	return 0;
}
 
// End of dancing link
int check(double R) {
	int i, j;
	bool v[N] = { 0 };
	R *= R;
	// Build the dancing link map
	init();
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			if (dd[i][j] < R + EPS) link(i, j), v[j] = 1;
	for (i = 0; i < m; i++)
		if (!v[i]) return INF;
	ans = k + 1;
	for (i = 0; i < n; i++) {
		row[i].l->r = row[i].r;
		row[i].r->l = row[i].l;
	}
	dfs(0);
	return ans;
}
double solve() {
	int i, j;
	double l = 0, r = 0, mid;
	scanf("%d%d%d", &m, &n, &k);
	for (i = 0; i < m; i++)
		p2[i].get();
	for (i = 0; i < n; i++)
		p1[i].get();
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			dd[i][j] = dis(p1[i], p2[j]);
			if (dd[i][j] > r) r = dd[i][j];
		}
 
	while (l + 1e-7 < r) {
		mid = (l + r) / 2.0;
		int ret = check(mid);
		if (ret > k) l = mid;
		else r = mid;
	}
	return l;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%.6lf\n", solve());
}
