// 2001 Taejon: Square Destroyer
// ACM-ICPC Live Archive 2328
// POJ 1084
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
 
// G
vector<int> V[6][60];
int total[6];
void init(int n) {
	int i, j, k, tot = 0, len;
	int Z = (n * 2 + 1);
	for (len = 1; len <= n; len++) {
		for (i = 1; i <= n - len + 1; i++) {
			for (j = 1; j <= n - len + 1; j++) {
				int p = (i - 1) * Z + j;
				for (k = 1; k <= len; k++) {
					V[n][tot].push_back(p);
					if (k < len) p++;
				}
				p += n + 1;
				for (k = 1; k <= len; k++) {
					V[n][tot].push_back(p);
					if (k < len) p += Z;
				}
				p += n;
				for (k = 1; k <= len; k++) {
					V[n][tot].push_back(p);
					if (k < len) p--;
				}
				p -= n + 1;
				for (k = 1; k <= len; k++) {
					V[n][tot].push_back(p);
					if (k < len) p -= Z;
				}
				tot++;
			}
		}
	}
	total[n] = tot;
}
 
// Dancing Link
#define N 80
int n, m, ans;
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
void dfs(int x) {
	if (x >= ans || x + h() >= ans) return;
	if (head.r == &head) {
		ans = x;
		return;
	}
	NODE *i, *j;
	int min = 1 << 29, tc;
	for (i = head.r; i != &head; i = i->r)
		if (size[i->C] < min) min = size[i->C], tc = i->C;
	if (min == 1 << 29) return;
	for (i = col[tc].d; i != &col[tc]; i = i->d) {
		cover(i);
		for (j = i->r; j != i; j = j->r)
			cover(j);
		dfs(x + 1);
		for (j = i->l; j != i; j = j->l)
			uncover(j);
		uncover(i);
		if (x + 1 >= ans) return;
	}
}
// End of dancing link
void solve() {
	int size, n, i, j, x, id = 0, reid = 0;
	bool del[80] = { 0 }, ok[80];
	int nid[80], nreid[N];
	scanf("%d%d", &size, &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		del[x] = 1;
	}
 
	for (i = 1; i <= size * (size + 1) * 2; i++)
		if (!del[i]) nid[i] = id++;
 
	for (i = 0; i < total[size]; i++) {
		ok[i] = 1;
		for (j = 0; j < (int) V[size][i].size() && ok[i]; j++) {
			if (del[V[size][i][j]]) ok[i] = 0;
		}
		if (ok[i]) {
			nreid[i] = reid++;
		}
	}
	::n = id, ::m = reid;
	init();
	for (i = 0; i < total[size]; i++) {
		if (!ok[i]) continue;
		for (j = 0; j < (int) V[size][i].size(); j++) {
			link(nid[V[size][i][j]], nreid[i]);
		}
	}
	for (i = 0; i < ::n; i++) {
		row[i].l->r = row[i].r;
		row[i].r->l = row[i].l;
	}
	ans = ::n;
	dfs(0);
	printf("%d\n", ans);
 
}
int main() {
	int T, i;
	for (i = 1; i <= 5; i++)
		init(i);
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}