// 2008 World Finals: Steam Roller
// ACM-ICPC Live Archive 4128

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define SIZE 105
#define N 10105
#define INF 1<<30
struct EDGE {
	int b, d, next;
};
int G[N], tot, heng[SIZE][SIZE], shu[SIZE][SIZE];
EDGE E[N * 8];
int R, C, r1, c1, r2, c2;
void addedge(int a, int b, int d) {
	EDGE e = { b, d, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
struct NODE {
	int next, dis, w, dir;
	bool sd;
	NODE() {
	}
	NODE(int next, int dis, int w, int dir, bool sd) :
		next(next), dis(dis), w(w), dir(dir), sd(sd) {
	}
	bool operator <(const NODE & n) const {
		return dis > n.dis;
	}
};
int dis[2][4][N];
int getdir(int s, int t) {
	if (t - s == C) return 0;
	if (s - t == C) return 2;
	if (t - s == 1) return 1;
	return 3;
}
int dij() {
	int i, begin, end, ans = INF;
	priority_queue<NODE> Q;
	memset(dis, -1, sizeof(dis));
	begin = (r1 - 1) * C + (c1 - 1);
	end = (r2 - 1) * C + (c2 - 1);
	for (i = G[begin]; ~i; i = E[i].next) {
		int ndir = getdir(begin, E[i].b);
		Q.push(NODE(E[i].b, 0, E[i].d, ndir, 0));
		dis[0][ndir][E[i].b] = 0;
	}
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (top.next == end)
			ans = min(ans, top.dis + top.w * 2);
		for (i = G[top.next]; ~i; i = E[i].next) {
			int ndis = top.w + top.dis, ndir = getdir(top.next, E[i].b);
			bool nsd = ndir == top.dir;
			if (top.sd == false) ndis += top.w;
			else if (top.dir != ndir) ndis += top.w;
			if (dis[nsd][ndir][E[i].b] == -1 || ndis < dis[nsd][ndir][E[i].b]) {
				dis[nsd][ndir][E[i].b] = ndis;
				Q.push(NODE(E[i].b, ndis, E[i].d, ndir, nsd));
			}
		}
	}
	return ans;
}
void solve() {
	int i, j, a, b;
	a = b = 0;
	for (i = 0; i < R + R - 1; i++) {
		if (i % 2 == 0) {
			for (j = 0; j < C - 1; j++)
				scanf("%d", &heng[a][j]);
			a++;
		}
		else {
			for (j = 0; j < C; j++)
				scanf("%d", &shu[b][j]);
			b++;
		}
	}
	tot = 0;
	memset(G, -1, sizeof(G));
	for (i = 0; i < R; i++) {
		for (j = 0; j < C - 1; j++) {
			a = i * C + j;
			b = i * C + j + 1;
			if (heng[i][j]) addedge(a, b, heng[i][j]), addedge(b, a, heng[i][j]);
		}
	}
	for (i = 0; i < R - 1; i++) {
		for (j = 0; j < C; j++) {
			a = i * C + j;
			b = (i + 1) * C + j;
			if (shu[i][j]) addedge(a, b, shu[i][j]), addedge(b, a, shu[i][j]);
		}
	}
	int ans = dij();
	if (ans != INF) printf("%d\n", ans);
	else printf("Impossible\n");
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2) && R + C) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}