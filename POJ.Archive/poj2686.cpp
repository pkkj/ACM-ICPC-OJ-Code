// 2005 Japan Domestic: Traveling by Stagecoach
// POJ 2686
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
#define M 100000
#define NC 40
#define NT 10
#define NS 258
#define INF 1e20
struct ITEM {
	int next, st;
	double cost;
	ITEM(int next, int st, double cost) :
		next(next), st(st), cost(cost) {
	}
	ITEM() {
	}
};
bool operator <(const ITEM& a, const ITEM& b) {
	return a.cost > b.cost;
}
struct NODE {
	int b, d;
	NODE(int b, int d) :
		b(b), d(d) {
	}
	NODE() {
	}
};
int n, m, p, s, t;
int tic[NT];
vector<NODE> G[NC];
int input() {
	scanf("%d%d%d%d%d", &m, &n, &p, &s, &t);
	if (n + m + p + s + t == 0) return 0;
	for (int i = 1; i <= n; i++)
		G[i].clear();
	for (int i = 0; i < m; i++)
		scanf("%d", &tic[i]);
	for (int i = 0; i < p; i++) {
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		G[a].push_back(NODE(b, w));
		G[b].push_back(NODE(a, w));
	}
	return 1;
}
bool vis[NC][NS];
double dis[NC][NS];
priority_queue<ITEM> H;
double solve() {
	int tst = 1 << m, l;
	int i, j, x, next, k;
	while(!H.empty())
		H.pop();
	memset(vis, 0, sizeof(vis));
	for (i = 1; i <= n; i++)
		for (j = 0; j <= tst; j++)
			dis[i][j] = INF;
	H.push(ITEM(s, 0, 0.0));
	dis[s][0] = 0;
	while (!H.empty()) {
		ITEM cur = H.top();
		H.pop();
		double td;
		x = cur.next, k = cur.st;
		if (x == t) return dis[x][k];
		if (cur.cost > dis[x][k]) continue;
		if (vis[x][k]) continue;
		vis[x][k] = 1;
 
		for (i = 0; i < G[x].size(); i++) {
			l = 1, next = G[x][i].b;
			for (j = 0; j < m; j++, l = l << 1) {
				if ((k | l) == k) continue;	// Verify the status
 
				if (vis[next][k | l]) continue;	// If this ticket is used, just skip it.
				td = cur.cost + 1.0 * G[x][i].d / tic[j];
				if (td < dis[next][k | l]) {
					dis[next][k | l] = td;
					H.push(ITEM(next, k | l, td));
				}
			}
		}
	}
	return -1;
}
int main() {
	double ans;
	while (input()) {
		ans = solve();
		if (ans == -1) printf("Impossible\n");
		else printf("%lf\n", ans);
	}
	return 0;
}


