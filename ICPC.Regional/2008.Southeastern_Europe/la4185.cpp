// 2008 Southeastern Europe: Perfect Election
// ACM-ICPC Live Archive 4185

#include <cstdio>
#include <cstring>
#define N 2005
struct EDGE {
	int b, next;
};
EDGE ET[4000000];
int GA[N], GD[N], tot, pos[N];
void addedge(int *g, int s, int t) {
	EDGE x = { t, *(g + s) };
	ET[tot] = x;
	*(g + s) = tot++;
}
 
void add(int s, int t) {
	addedge(GA, s, t), addedge(GD, t, s);
}
 
int v[N], block[N], pp, n;

void dfs1(int x) {
	v[x] = 1;
	for (int i = GA[x]; i != -1; i = ET[i].next)
		if (!v[ET[i].b]) dfs1(ET[i].b);
	pos[pp++] = x;
}

int dfs2(int x, int id) {
	v[x] = 0, block[x] = id;
	if (x > n / 2) {
		if (block[x] == block[x - n / 2]) return 0;
	} else if (block[x] == block[x + n / 2]) return 0;
	for (int i = GD[x]; i != -1; i = ET[i].next) {
		if (v[ET[i].b]) if (!dfs2(ET[i].b, id)) return 0;
	}
	return 1;
}
int solve() {
	int i, nblock = 0;
	pp = 1;
	memset(v, 0, sizeof(v));
	memset(block, 0, sizeof(block));
	for (i = 1; i <= n; i++)
		if (!v[i]) dfs1(i);
	for (i = n; i >= 1; i--)
		if (v[pos[i]]) {
			int ret = dfs2(pos[i], pos[i]);
			nblock++;
			if (!ret) return 0;
		}
	return 1;
}
 
void init() {
	memset(GA, -1, sizeof(GA));
	memset(GD, -1, sizeof(GD));
	tot = 0;
}
void sample() {
	int m;
	init();
	scanf("%d", &m);
	while (m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > 0 && b > 0) {
			add(n + a, b);
			add(n + b, a);
		} else if (a < 0 && b < 0) {
			a = -a, b = -b;
			add(a, b + n);
			add(b, a + n);
		} else if (a > 0 && b < 0) {
			b=-b;
			add(a + n, b + n);
			add(b, a);
		} else if (a < 0 && b > 0) {
			a = -a;
			add(a, b);
			add(b + n, a + n);
		}
	}
	n *= 2;
	if (solve()) printf("1\n");
	else printf("0\n");
}
 
int main() {
	while (scanf("%d", &n) != EOF)
		sample();
	return 0;
}