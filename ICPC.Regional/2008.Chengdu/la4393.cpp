// 2008 Chengdu: Box
// ACM-ICPC Live Archive 4393
// HDU 2475
#include <cstdio>

#define N 50005
struct SPLAY {
	SPLAY *l, *r, *fa;
};
SPLAY T[N * 2];
int n;
SPLAY* rl(SPLAY *p) {
	SPLAY *q = p->l;
	p->l = q->r;
	q->r = p;
	q->fa = p->fa;
	p->fa = q;
	if (p->l)
		p->l->fa = p;
	return q;
}
SPLAY* rr(SPLAY *p) {
	SPLAY *q = p->r;
	p->r = q->l;
	q->l = p;
	q->fa = p->fa;
	p->fa = q;
	if (p->r)
		p->r->fa = p;
	return q;
}
void splay(SPLAY *p) {
	if (!p)
		return;
	while (p->fa) {
		SPLAY *q = p->fa;
		SPLAY *r = q->fa;
		if (!q->fa) {
			if (q->l == p)
				rl(q);
			else
				rr(q);
			return;
		}
		if (p == q->l) {
			if (q == r->l)
				p = r->l = rl(q);
			else
				p = r->r = rl(q);
		} else if (p == q->r) {
			if (q == r->l)
				p = r->l = rr(q);
			else
				p = r->r = rr(q);
		}
	}
}

void add(int x, int fa) {
	if (!fa)
		return;
	splay(&T[fa]);
	splay(&T[x + n]);
	T[x + n].r = T[fa].r;
	T[x + n].r->fa = &T[x + n];

	T[fa].r = &T[x + n];
	T[x + n].fa = &T[fa];
}

void cut(int x) {
	splay(&T[x]);
	SPLAY *p = T[x].l;
	splay(&T[x + n]);
	SPLAY *q = T[x + n].r;
	T[x].l = T[x + n].r = NULL;
	if (p) {
		p->fa = NULL;
		while (p->r)
			p = p->r;
		p->r = q;
	}
	if (q)
		q->fa = p;
}

int find(int x) {
	splay(&T[x]);
	SPLAY *p = &T[x];
	while (p->l)
		p = p->l;
	return p - T;

}
bool intree(int x, int y) {
	if (!y)
		return false;
	SPLAY *p, *q;
	splay(&T[x]);
	p = T[x].l;
	splay(&T[x + n]);
	q = T[x + n].r;
	T[x].l = T[x + n].r = NULL;
	if (p)
		p->fa = NULL;
	if (q)
		q->fa = NULL;
	y = find(y);
	splay(&T[x]);
	splay(&T[x + n]);
	splay(p);
	splay(q);

	T[x].l = p;
	if (p) p->fa = &T[x];

	T[x + n].r = q;
	if (q) q->fa = &T[x + n];
	return x == y;
}

void init() {
	int i, fa;
	for (i = 1; i <= n; i++) {
		T[i].fa = T[i].l = T[i + n].l = T[i + n].r = NULL;
		T[i].r = T + (i + n);
		T[i + n].fa = T + i;
	}
	for (i = 1; i <= n; i++) {
		scanf("%d", &fa);
		add(i, fa);
	}
}

void solve() {
	int Q, x, y;
	char s[15];
	init();
	scanf("%d", &Q);
	while (Q--) {
		scanf("%s", s);
		if (s[0] == 'M') {
			scanf("%d%d", &x, &y);
			if (!intree(x, y)) {
				cut(x);
				add(x, y);
			}
		} else {
			scanf("%d", &x);
			printf("%d\n", find(x));
		}
	}
}
int main() {
	int be = 1;
	while (scanf("%d", &n) == 1) {
		if (!be)
			printf("\n");
		else
			be = 0;
		solve();
	}
	return 0;
}
