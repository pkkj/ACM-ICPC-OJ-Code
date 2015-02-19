// 2008 Southeastern Europe: Quick Answer
// ACM-ICPC Live Archive 4188

#include <cstdio>
#include <cstring>
#define N 30005
 
int fa[N], rank[N], root[N];
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
	int n;
	while (scanf("%d\n", &n) != EOF) {
		int p = n + 1, a, b;
		int n1, n2;
		char op;
		n1 = n2 = 0;
		init_set(n);
		while (1) {
			scanf("%c", &op);
			if (op == 'e') {
				printf("%d , %d\n", n1, n2);
				break;
			} else if (op == 'c') {
				scanf("%d%d\n", &a, &b);
				union_set(root[a], root[b]);
			} else if (op == 'd') {
				scanf("%d\n", &a);
				root[a] = p++;
				rank[root[a]] = 0;
				fa[root[a]] = root[a];
			} else if (op == 'q') {
				scanf("%d%d\n", &a, &b);
				a = root[a], b = root[b];
				if (find_root(a) == find_root(b)) {/*printf("Yes\n");*/n1++;}
				else {/*printf("No\n");*/n2++;}
			}
		}
 
	}
	return 0;
}