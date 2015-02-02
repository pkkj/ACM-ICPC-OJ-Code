// 2008 Hangzhou: Junk-Mail Filter
// ACM-ICPC Live Archive 4360
#include <cstdio>
#include <cstring>
#define N 1000000
#define M 100005
int fa[N], rank[N], root[N];
bool ans[N];
void init_set(int n) {
	for (int i = 0; i <= n; i++)
		root[i] = fa[i] = i, rank[i] = 0;
}
int find_root(int p) {
	if (fa[p] != p) fa[p] = find_root(fa[p]);
	return fa[p];
}
void union_set(int p, int q) {
	int a = find_root(p), b = find_root(q);
	if (a == b) return;
	if (rank[a] > rank[b]) fa[b] = a;
	else if (rank[a] < rank[b]) fa[a] = b;
	else fa[b] = a, rank[a]++;
}
int main() {
	int n, m, T = 0, i;
	while (scanf("%d%d\n", &n, &m) && n) {
		int p = n, a, b;
		char op;
		init_set(n);
		while (m--) {
			scanf("%c", &op);
			if (op == 'M') {
				scanf("%d%d\n", &a, &b);
				union_set(root[a], root[b]);
			} else {
				scanf("%d\n", &a);
				root[a] = p++;
				rank[root[a]] = 0;
				fa[root[a]] = root[a];
			}
		}
		memset(ans, 0, sizeof(ans));
		int cnt = 0;
		for(i = 0; i < n; i++)
		{
			int k = find_root(root[i]);
			if(!ans[k])
				ans[k] = 1,  cnt++;
		}
		printf("Case #%d: %d\n", ++T,cnt );
	}
	return 0;
}