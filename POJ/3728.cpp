// POJ 3728
// POJ Monthly Contest – 2009.04.05: The merchant
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 50005
struct ASK {
	int x, y;
};
struct EDGE {
	int y, next, id;
};
int ma[N], mi[N], op1[N], op2[N], G[N], Q[N], fa[N], ans[N], tot;
bool v[N];
EDGE pool[N * 4];
ASK query[N];
vector<int> toans[N];//新的回答位置，设置在LCA之中
void add(int G[], int x, int y, int id = -1) {
	pool[tot].next = G[x], pool[tot].y = y, pool[tot].id = id;
	G[x] = tot++;
}
//并查集上面的路径压缩
void findroot(int x) {
	if (fa[x] != x) {
		findroot(fa[x]);
		op1[x] = max(max(op1[x], op1[fa[x]]), ma[fa[x]] - mi[x]);
		op2[x] = max(max(op2[x], op2[fa[x]]), ma[x] - mi[fa[x]]);
		ma[x] = max(ma[x], ma[fa[x]]);
		mi[x] = min(mi[x], mi[fa[x]]);
	}
	fa[x] = fa[fa[x]];
}
void answer(int i) {
	int x = query[i].x, y = query[i].y;
	findroot(x);
	findroot(y);
	ans[i] = max(op1[x], op2[y]);
	ans[i] = max(ans[i], ma[y] - mi[x]);
}
void dfs(int x, int pre) {
	int i, j;
	v[x] = 1;
	for (i = Q[x]; i != -1; i = pool[i].next) {
		j = pool[i].y;
		if (v[j]) {
			findroot(j);
			toans[fa[j]].push_back(pool[i].id);
		}
	}
	for (i = G[x]; i != -1; i = pool[i].next)
		if (pre != pool[i].y) dfs(pool[i].y, x);
 
	for (i = 0; i < (int) toans[x].size(); i++)
		answer(toans[x][i]);
	fa[x] = pre;
}
int main() {
	int i, x, y, n, nq;
	//freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &ma[i]);
		mi[i] = ma[i], fa[i] = i;
	}
	memset(op1, 0, sizeof(op1));
	memset(op2, 0, sizeof(op2));
	memset(G, -1, sizeof(G));
	memset(Q, -1, sizeof(Q));
	memset(ans, 0, sizeof(ans));
	tot = 0;
	for (i = 0; i < n - 1; i++) {
		scanf("%d%d", &x, &y);
		add(G, x, y);
		add(G, y, x);
	}
	scanf("%d", &nq);
	for (i = 0; i < nq; i++) {
		scanf("%d%d", &x, &y);
		query[i].x = x, query[i].y = y;
		//将询问也使用类似“图”的方法用链表保存起来
		add(Q, x, y, i);
		add(Q, y, x, i);
	}
	memset(v, 0, sizeof(v));
	dfs(1, 0);
	for (i = 0; i < nq; i++)
		printf("%d\n", ans[i]);
	return 0;
}
