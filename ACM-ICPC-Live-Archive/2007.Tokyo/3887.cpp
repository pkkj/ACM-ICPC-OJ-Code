#include <cstdio>
// 2007 Tokyo: Slim Span
// ACM-ICPC Live Archive 3887
// POJ 3522
#include <algorithm>
#include <vector>
using namespace std;
#define N 105
struct EDGE {
	int a, b, w;
};

int cmp(const EDGE &a, const EDGE &b) {
	return a.w < b.w;
}
int n, m;
int fa[N], rank[N];
void init_set() {
	int i;
	for (i = 0; i <= n; i++) {
		fa[i] = i;
		rank[i] = 0;
	}
}
int find_root(int p) {
	if (fa[p] != p)
		fa[p] = find_root(fa[p]);
	return fa[p];
}
void union_set(int p, int q) {
	int a = find_root(p), b = find_root(q);
	if (rank[a] > rank[b])
		fa[b] = a;
	else if (rank[a] < rank[b])
		fa[a] = b;
	else {
		fa[b] = a;
		rank[a]++;
	}
}

void solve() {
	int i, j, ans = 100000000, linked;
	vector<EDGE> elist;
	elist.resize(m);
	for (i = 0; i < m; i++)
		scanf("%d%d%d", &elist[i].a, &elist[i].b, &elist[i].w);
	sort(elist.begin(), elist.end(), cmp);
	for (i = 0; i < m; i++) {
		int tmp = -1, base = elist[i].w;
		linked = 1;
		init_set();
		for (j = i; j < m; j++) {
			if (find_root(elist[j].a) != find_root(elist[j].b)) {
				union_set(elist[j].a, elist[j].b);
				linked++;
			}
			if (linked == n) {
				tmp = elist[j].w - base;
				break;
			}
		}
		if(tmp == -1)
			break;
		if (tmp != -1 && tmp < ans)
			ans = tmp;
	}
	printf("%d\n", (ans == 100000000) ? -1 : ans);
}
int main() {
	while (scanf("%d%d", &n, &m) && n)
		solve();
	return 0;
}
