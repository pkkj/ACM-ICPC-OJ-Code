// 2009 Nordic: Speedy Escape
// HDU 3143

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 105
#define M 5005
#define INF 1e40
int n, sp, sb;

struct EDGE {
	int b;
	double w;
	int next;
};
EDGE E[M * 2];
int G[N], tot;
bool ex[N];
double po[N];
void addedge(int a, int b, double w) {
	EDGE e = { b, w, G[a] };
	G[a] = tot;
	E[tot++] = e;
}

struct NODE {
	int next;
	double time;
	NODE() {
	}
	NODE(int next, double time) :
		next(next), time(time) {
	}
	bool operator<(const NODE &n) const {
		return time > n.time;
	}
};
void dij1() {
	int i;
	for (i = 1; i <= n; i++)
		po[i] = INF;
	priority_queue<NODE> Q;
	Q.push(NODE(sp, 0));
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (top.time > po[top.next]) continue;
		po[top.next] = top.time;
		for (i = G[top.next]; ~i; i = E[i].next) {
			int j = E[i].b;
			double need = (double)E[i].w / 160.0;
			if (top.time + need < po[j]) {
				Q.push(NODE(j, top.time + need));
				po[j] = top.time + need;
			}
		}
	}
}
bool vis[N];
bool dfs(int x) {
	vis[x] = 1;
	for (int i = G[x]; ~i; i = E[i].next) {
		int j = E[i].b;
		if (vis[j] || j == sp) continue;
		if (ex[j]) return 1;
		if (dfs(j)) return 1;
	}
	return 0;
}
double cc[N];
bool check(double mid) {
	int i;
	for (i = 1; i <= n; i++)
		cc[i] = INF;
	priority_queue<NODE> Q;
	Q.push(NODE(sb, 0));
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (ex[top.next]) return 1;
		if (top.time > cc[top.next]) continue;
		cc[top.next] = top.time;
		for (i = G[top.next]; ~i; i = E[i].next) {
			int j = E[i].b;
			double need = E[i].w / mid;
			if (top.time + need < cc[j] && top.time + need < po[j]) {
				Q.push(NODE(j, top.time + need));
				cc[j] = top.time + need;
			}
		}
	}
	return 0;
}

int main() {
	int m, i, ne, a, b, w;
	while (~scanf("%d%d%d", &n, &m, &ne)){
		memset(G, -1, sizeof(G));
		memset(ex, 0, sizeof(ex));
		tot = 0;
		while (m--) {
			scanf("%d%d%d", &a, &b, &w);
			addedge(a, b, (double)w / 10.0);
			addedge(b, a, (double)w / 10.0);
		}
		for (i = 0; i < ne; i++) {
			scanf("%d", &a);
			ex[a] = 1;
		}
		scanf("%d%d", &sb, &sp);
		if (!dfs(sb)) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		dij1();
		memset(vis, 0, sizeof(vis));

		double l = 0, r = 2000000;
		while (r - l > 1e-8) {
			double mid = (l + r) / 2.0;
			if (check(mid)) r = mid;
			else l = mid;
		}
		printf("%.7lf\n", l);
	}
	return 0;
}