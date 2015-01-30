// 2008 Hefei Preliminary: 	Network
// POJ 3694
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define N 100005
#define M 2000005
#define WHITE 0
#define BLACK 1
#define GRAY 2

int n, m, root, tot, nblock;
int C[N], D[N], low[N], pre[N], father[N], nbridge;

stack<int> S;
vector<int> block[N];

struct EDGE {
	int b, next;
};

EDGE ET[M];
int NT[N], sum;
int fa[N], setRank[N];
void initSet(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i, setRank[i] = 0;
}
int findRoot(int p) {
	if (fa[p] != p) fa[p] = findRoot(fa[p]);
	return fa[p];
}
void unionSet(int p, int q) {
	if (p == q) return;
	int a = findRoot(p), b = findRoot(q);
	if (a == b) return;
	if (setRank[a] > setRank[b]) fa[b] = a;
	else if (setRank[a] < setRank[b]) fa[a] = b;
	else fa[b] = a, setRank[a]++;
}

void addedge(int a, int b) {
	EDGE x = { b, NT[a] };
	ET[tot] = x;
	NT[a] = tot++;
}
void dfs_block(int k, int father, int deep) {
	int tot, i;
	C[k] = GRAY, D[k] = deep, low[k] = deep, tot = 0;
	S.push(k);
	for (int j = NT[k]; j != -1; j = ET[j].next) {
		i = ET[j].b;
		if (i != father && C[i] == GRAY) low[k] = min(low[k], D[i]);
		if (C[i] == WHITE) {
			dfs_block(i, k, deep + 1);
			tot++, low[k] = min(low[k], low[i]);
			// Find a bridge
			if (low[i] > D[k]) {
				nbridge++;
				while (!S.empty() && S.top() != i) {
					block[nblock].push_back(S.top());
					S.pop();
				}
				block[nblock].push_back(S.top());
				S.pop();
				nblock++;
			}
		}
	}
	if (k == 1) {
		while (!S.empty()) {
			block[nblock].push_back(S.top());
			S.pop();
		}
		nblock++;
	}
	C[k] = BLACK;
}

void dfslevel(int x, int fa) {
	int i, j;
	father[x] = fa;
	C[x] = 1;
	for (j = NT[x]; j != -1; j = ET[j].next) {
		i = pre[findRoot(ET[j].b)];
		if (!C[i]) dfslevel(i, x);
	}
}
int r1[N], r2[N];
int lca(int pp1, int pp2) {
	int p1 = pre[findRoot(pp1)], p2 = pre[findRoot(pp2)], i1, i2, finish;
	r1[0] = -1, r2[0] = -2;
	i1 = 1, i2 = 1, finish = 0;
	while (!finish) {
		r1[i1++] = p1;
		p1 = father[p1];
		if (p1 == -1) finish = 1;
		else p1 = pre[findRoot(p1)];
	}
	finish = 0;
	while (!finish) {
		r2[i2++] = p2;
		p2 = father[p2];
		if (p2 == -1) finish = 1;
		else p2 = pre[findRoot(p2)];
	}
	while (r1[i1 - 1] == r2[i2 - 1])
		i1--, i2--;
	return r1[i1];
}

int mergepoint(int p, int rt) {
	int troot = pre[findRoot(rt)], ce = 0, prep;
	p = pre[findRoot(p)];
	while (p != rt) {
		prep = p;
		p = pre[findRoot(father[p])];
		father[prep] = father[rt];
		unionSet(prep, p);
		ce++;
	}
	pre[findRoot(rt)] = troot;
	return ce;
}
int solve() {
	int i, j;
	memset(NT, -1, sizeof(NT));
	memset(C, 0, sizeof(C));
	memset(block, 0, sizeof(block));
	nblock = tot = nbridge = 0;
	for (i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		addedge(a, b), addedge(b, a);
	}
	root = 1;
	dfs_block(1, 0, 1);
	initSet(n);
	for (i = 0; i < nblock; i++) {
		for (j = 1; j < block[i].size(); j++)
			unionSet(block[i][j], block[i][0]);
		pre[findRoot(block[i][0])] = block[i][0];
	}
	for (i = 1; i <= n; i++) {
		if (pre[findRoot(i)] == i) continue;
		for (j = NT[i]; j != -1; j = ET[j].next)
			addedge(pre[findRoot(ET[j].b)], pre[findRoot(i)]), addedge(pre[findRoot(i)], pre[findRoot(ET[j].b)]);
	}
	memset(C, 0, sizeof(C));
	dfslevel(pre[findRoot(1)], -1);
	int q, a, b;
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d", &a, &b);
		if (findRoot(a) == findRoot(b))
		{
			printf("%d\n", nbridge);
			continue;
		}
		int ll = lca(a, b);
		int save = 0;
		save += mergepoint(a, ll);
		save += mergepoint(b, ll);
		nbridge -= save;
		printf("%d\n", nbridge);
	}
	return 0;
}

int main() {
	int T = 0;
	while (scanf("%d%d", &n, &m) && n) {
		printf("Case %d:\n", ++T);
		solve();
		printf("\n");
	}
	return 0;
}
