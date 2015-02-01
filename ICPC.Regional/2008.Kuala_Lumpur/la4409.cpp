// 2008 Kuala Lumpur: Ironman Race in Treeland
// ACM-ICPC Live Archive 4409
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 30005
struct NODE {
	int cost, len;
	NODE() {
	}
	NODE(int cost, int len) :
		cost(cost), len(len) {
	}
	bool operator <(const NODE &n) const {
		if (cost == n.cost) return len > n.len;
		return cost < n.cost;
	}
};
struct EDGE {
	int b, c, l, next;
};
int G[N], tot, m;
EDGE E[N * 2];
void addedge(int a, int b, int cost, int len) {
	EDGE e = { b, cost, len, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
 
// DFS
int ans, best, subtreesum;
int soncnt[N];
bool V[N];
void findroot(int x, int fa, int &root) {
	int i, j, maxson = 0;
	soncnt[x] = 1;
	for (j = G[x]; ~j; j = E[j].next) {
		i = E[j].b;
		if (i == fa || V[i]) continue;
		findroot(i, x, root);
		if (soncnt[i] > maxson) maxson = soncnt[i];
		soncnt[x] += soncnt[i];
	}
	if (subtreesum - soncnt[x] > maxson) maxson = subtreesum - soncnt[x];
	if (maxson < best) root = x, best = maxson;
}
int getsonsum(int x, int fa) {
	int i, j, ans = 1;
	for (j = G[x]; ~j; j = E[j].next) {
		i = E[j].b;
		if (i == fa || V[i]) continue;
		ans += getsonsum(i, x);
	}
	return ans;
}
NODE path[N];
int begin, end;
void findpath(int x, int fa, int cost, int len) {
	int i, j;
	for (j = G[x]; ~j; j = E[j].next) {
		i = E[j].b;
		if (i == fa || V[i]) continue;
		if (cost + E[j].c <= m) {
			path[end++] = NODE(cost + E[j].c, len + E[j].l);
			findpath(i, x, cost + E[j].c, len + E[j].l);
		}
	}
}
 
void del(int s, int &t) {
	int i, k;
	if (s == t) return;
	k = s;
	path[k] = path[s];
	for (i = k = s + 1; i < t; i++) {
		if (path[i].cost == path[k].cost) continue;
		if (path[i].len <= path[k-1].len) continue;
		path[k++] = path[i];
	}
	t = k;
}
void dfs(int x, int fa) {
	int i, j, root;
	for (j = G[x]; ~j; j = E[j].next) {
		i = E[j].b;
		if (i == fa || V[i]) continue;
		best = N;
		subtreesum = getsonsum(i, x);
		findroot(i, x, root);
		V[root] = 1;
		dfs(root, x);
		V[root] = 0;
	}
	begin = end = 0;
	for (j = G[x]; ~j; j = E[j].next) {
		i = E[j].b;
		if (i == fa || V[i]) continue;
		if (E[j].c <= m) {
			path[end++] = NODE(E[j].c, E[j].l);
			findpath(i, x, E[j].c, E[j].l);
		}
		if (begin > 0) {
			sort(path + begin, path + end);
			del(begin, end);
			int p1, p2;
			for (p1 = 0, p2 = end - 1; p1 < begin; p1++) {
				while (p2 >= begin && path[p1].cost + path[p2].cost > m)
					p2--;
				if (p2 >= begin) ans = max(ans, path[p1].len + path[p2].len);
			}
		}
		sort(path, path + end);
		del(0, end);
		begin = end;
	}
}
//
int solve() {
	int n, a, b, cost, len, i;
	tot = 0;
	memset(G, -1, sizeof(G));
	scanf("%d%d", &n, &m);
	for (i = 0; i < n - 1; i++) {
		scanf("%d%d%d%d", &a, &b, &cost, &len);
		addedge(a, b, cost, len);
		addedge(b, a, cost, len);
	}
	int root;
	ans = 0;
	memset(V, 0, sizeof(V));
	best = N, subtreesum = n;
	findroot(1, -1, root);
	V[root] = 1;
	dfs(root, 0);
	return ans;
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--)
		printf("Case %d: %d\n", ca++, solve());
	return 0;
}