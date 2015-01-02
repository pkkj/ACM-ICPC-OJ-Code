// SGU 149 Computer Network
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 10005
struct NODE {
	int p, d;
	NODE() {
	}
	NODE(int p, int d) :
		p(p), d(d) {
	}
};
vector<NODE> G[N];
int d1[N], d2[N], d3[N];
int best[N];
void dfs1(int x) {
	int i, p;
	d1[x] = d2[x] = 0;
	for (i = 0; i < (int) G[x].size(); i++) {
		p = G[x][i].p;
		dfs1(p);
		if (d1[x] < d1[p] + G[x][i].d) d1[x] = d1[p] + G[x][i].d, best[x] = p;
	}
	for (i = 0; i < (int) G[x].size(); i++) {
		p = G[x][i].p;
		if (best[x] == p) continue;
		if (d1[p] + G[x][i].d > d2[x]) d2[x] = d1[p] + G[x][i].d;
	}
}
 
void dfs2(int x, int d) {
	int i, p;
	d3[x] = d;
	for (i = 0; i < (int) G[x].size(); i++) {
		p = G[x][i].p;
		if (p == best[x]) dfs2(p, max(d, d2[x]) + G[x][i].d);
		else dfs2(p, max(d, d1[x]) + G[x][i].d);
	}
}
int main() {
	int n, i, x, d;
	scanf("%d", &n);
	for (i = 2; i <= n; i++) {
		scanf("%d%d", &x, &d);
		G[x].push_back(NODE(i, d));
	}
	dfs1(1);
	dfs2(1, 0);
	for (i = 1; i <= n; i++)
		printf("%d\n", max(d1[i], d3[i]));
	return 0;
}
