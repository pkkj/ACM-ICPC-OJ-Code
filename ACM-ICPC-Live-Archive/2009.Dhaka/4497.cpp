// CII 4497
// 2009 Dhaka: Games of Block
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define SIZE 4
 
// Hash table
struct HASHNODE {
	int st, id, next;
};
#define MOD 70000
HASHNODE HE[MOD];
int HG[MOD], htot, id;
void hinit() {
	htot = 0, id = 0;
	memset(HG, -1, sizeof(HG));
}
int insert(int x) {
	int i, p = x % MOD;
	for (i = HG[p]; ~i; i = HE[i].next)
		if (HE[i].st == x) return HE[i].id;
	HASHNODE e = { x, id, HG[p] };
	HG[p] = htot;
	HE[htot++] = e;
	return id++;
}
int find(int x) {
	int i, p = x % MOD;
	for (i = HG[p]; ~i; i = HE[i].next)
		if (HE[i].st == x) return HE[i].id;
	return -1;
}
// End of Hash table
 
int hash(int a[SIZE][SIZE]) {
	int ans = 0;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			ans = ans * 3 + a[i][j];
	return ans;
}
// The graph
#define N 20000
struct EDGE {
	int b, next;
};
int G[N], tot;
EDGE E[N * 5];
void ginit() {
	memset(G, -1, sizeof(G));
	tot = 0;
}
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	G[a] = tot;
	E[tot++] = e;
 
}
// End of the graph
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
 
int g[SIZE][SIZE];
void bfs(int x, int y, bool vis[SIZE][SIZE]) {
	int qh = 0, qe = 0, i, j, col = g[x][y];
	pair<int, int> Q[20];
	Q[qe++] = make_pair(x, y);
	vis[x][y] = 1, g[x][y] = 0;
	while (qh < qe) {
		int x = Q[qh].first, y = Q[qh].second;
		qh++;
		for (i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx == SIZE || ny == SIZE) continue;
			if (vis[nx][ny] || g[nx][ny] != col) continue;
			vis[nx][ny] = 1, g[nx][ny] = 0;
			Q[qe++] = make_pair(nx, ny);
		}
	}
	for (i = SIZE - 2; i >= 0; i--) {
		for (j = 0; j < SIZE; j++) {
			int p = i;
			while (p + 1 < SIZE && !g[p + 1][j]) {
				g[p + 1][j] = g[p][j];
				g[p++][j] = 0;
			}
		}
	}
 
}
 
void dfs(int x) {
	int i, j, newst, newid;
	int cur[SIZE][SIZE];
	bool vis[SIZE][SIZE];
	memcpy(cur, g, sizeof(g));
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			if (vis[i][j] || cur[i][j] == 0) continue;
			memcpy(g, cur, sizeof(cur));
			bfs(i, j, vis);
			newst = hash(g);
			newid = find(newst);
			bool todfs = 0;
			if (newid == -1) {
				newid = insert(newst);
				todfs = 1;
			}
			addedge(x, newid);
			if (todfs) dfs(newid);
		}
}
// DP in a DAG
int sg[N], step[N];
int dp(int x) {
	int i, win = 0;
	if (sg[x] != -1) return sg[x];
	for (i = G[x]; ~i; i = E[i].next) {
		if (dp(E[i].b) == 0) win = 1;
	}
 
	if (win) {
		int best = N;
		for (i = G[x]; ~i; i = E[i].next)
			if (sg[E[i].b] == 0) best = min(best, step[E[i].b]);
		step[x] = best + 1;
	} else {
		int best = 0;
		for (i = G[x]; ~i; i = E[i].next)
			best = max(best, step[E[i].b]);
		step[x] = best + 1;
	}
	return sg[x] = win;
}
// End of DP in a DAG
void solve() {
	int i, j;
	int beginst, beginid;
	char s[SIZE + 1];
	hinit();
	insert(0);
	for (i = 0; i < SIZE; i++) {
		scanf("%s", s);
		for (j = 0; j < SIZE; j++)
			g[i][j] = (s[j] == 'B') + 1;
	}
	ginit();
	beginst = hash(g);
	beginid = insert(beginst);
	memset(sg, -1, sizeof(sg));
	sg[0] = step[0] = 0;
	dfs(beginid);
	if (dp(beginid)) printf("win %d\n", step[beginid]);
	else printf("loss %d\n", step[beginid]);
}
int main() {
	int T, ca = 1;
	scanf("%d", &T);
	while (T--) {
		printf("Case %d: ", ca++);
		solve();
	}
}
