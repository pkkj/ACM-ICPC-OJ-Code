// 2009 World Finals: The Ministers' Major Mess
// ACM-ICPC Live Archive 4452

#include <cstdio>
#include <cstring>
#define N 1005
#define M 300001
int n, m;
struct EDGE {
	int b, next;
};
EDGE E[M];
int GA[N], GD[N], tot, pos[N];
int color[N], v[N], block[N], pp;
inline void addedge(int *g, int s, int t) {
	EDGE x = { t, *(g + s) };
	E[tot] = x;
	*(g + s) = tot++;
}
inline void add(int s, int t) {
	addedge(GA, s, t), addedge(GD, t, s);
}
 
void dfs1(int x) {
	v[x] = 1;
	for (int i = GA[x]; i != -1; i = E[i].next)
		if (!v[E[i].b]) dfs1(E[i].b);
	pos[pp++] = x;
}
 
void dfs2(int x, int id) {
	v[x] = 0, block[x] = id;
	for (int i = GD[x]; i != -1; i = E[i].next)
		if (v[E[i].b]) dfs2(E[i].b, id);
}
 
bool sat() {
	int i;
	memset(v, 0, sizeof(v));
	pp = 0;
	for (i = 0; i < n * 2; i++)
		if (!v[i]) dfs1(i);
 
	for (i = n * 2 - 1; i >= 0; i--)
		if (v[pos[i]]) dfs2(pos[i], pos[i]);
 
	for (i = 0; i < n * 2; i += 2)
		if (block[i] == block[i + 1]) {
			return 0;
		}
	return 1;
}
 
void solve() {
	int i, j, k, x, y, b[4];
	char ss[4];
	memset(GA, -1, sizeof(GA));
	memset(GD, -1, sizeof(GD));
	tot = 0;
	for (i = 0; i < m; i++) {
		scanf("%d", &k);
		for (j = 0; j < k; j++) {
			scanf("%d%s", &b[j], ss);
			b[j] = (b[j] - 1) * 2;
			if (ss[0] == 'y') b[j]++;
		}
		if (k <= 2) {
			for (j = 0; j < k; j++) {
				add(b[j] ^ 1, b[j]);
			}
		} else {
			for (x = 0; x < k; x++) {
				for (y = 0; y < k; y++) {
					if (x == y) continue;
					add(b[x] ^ 1, b[y]);
				}
			}
		}
	}
	if (!sat()) {
		printf("impossible\n");
		return;
	}
	for (i = 0; i < n * 2; i += 2) {
		bool bn, by;
		add(i, i + 1);
		by = sat();
		GA[i] = E[GA[i]].next;
		GD[i + 1] = E[GD[i + 1]].next;
		tot-=2;
 
		add(i + 1, i);
		bn = sat();
		GA[i + 1] = E[GA[i + 1]].next;
		GD[i] = E[GD[i]].next;
		tot-=2;
		if (bn && by) putchar('?');
		else if (bn) putchar('n');
		else putchar('y');
	}
	printf("\n");
}
 
int main() {
	int ca = 1;
	while (scanf("%d%d", &n, &m) && n) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
