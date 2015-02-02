// 2007 Dhaka: Inspector's Dilemma
// ACM-ICPC Live Archive 4059
#include <cstdio>
#include <cstring>
#define N 1005
struct EDGE {
	int b, next;
};
EDGE E[N * N + 10];
int G[N], tot;
 
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	G[a] = tot;
	E[tot++] = e;
}
void init() {
	tot = 0;
	memset(G, -1, sizeof(G));
}
int d[N], n, m, t, name[N], ji[N], sz[N];
void dfs(int x, int id) {
	name[x] = id;
	sz[id]++;
	for (int i = G[x]; ~i; i = E[i].next)
		if (name[E[i].b] == -1) dfs(E[i].b, id);
}
int solve() {
	int ret, a, b, id = 1, i;
	init();
	memset(d, 0, sizeof(d));
	memset(sz, 0, sizeof(sz));
	ret = m;
	if(!m)return 0;
	while (m--) {
		scanf("%d%d", &a, &b);
		addedge(a, b);
		addedge(b, a);
		d[a]++, d[b]++;
	}
	memset(name, -1, sizeof(name));
	for (i = 1; i <= n; i++) {
		if (name[i] == -1) dfs(i, id++);
	}
	memset(ji, 0, sizeof(ji));
	for (i = 1; i <= n; i++) {
		if (d[i] % 2) ji[name[i]]++;
	}
	for (i = 1; i < id; i++) {
		if (ji[i] > 0) ret += (ji[i] - 2) / 2;
		//printf("%d %d\n", ji[i], sz[i]);
		if(sz[i] > 1)
			ret++;
	}
	ret--;
	return ret * t;
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d", &n, &m, &t) && n)
		printf("Case %d: %d\n", ca++, solve());
	return 0;
}