// 2008 Chengdu Preliminary: Travel
// HDU 2433

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
 
#define N 105
#define M 6001
 
struct EDGE {
	short b, next, id;
};
int G[N], sum[N], tot;
EDGE ET[M];
bool vv[N][M];
void addedge(int a, int b, int id) {
	EDGE x = { b, G[a], id };
	ET[tot] = x;
	G[a] = tot++;
}
 
void init() {
	tot = 0;
	memset(G, -1, sizeof(G));
}
 
int n, m;
void bfs(int s) {
	queue<int> Q;
	bool v[N];
	int  x, rp, np, d = 0, i, j;
	memset(v, 0, sizeof(v));
	memset(vv[s], 0, sizeof(vv[s]));
	Q.push(s), v[s] = 1, rp = 1,sum[s] = 0;
	while (!Q.empty()) {
		np = 0;
		while (rp--) {
			x = Q.front();
			Q.pop();
			sum[s] += d;
			for (j = G[x]; j != -1; j = ET[j].next) {
				i = ET[j].b;
				if (!v[i]) {
					Q.push(i);
					v[i] = 1, vv[s][ET[j].id] = 1, np++;
				}
			}
		}
		rp = np, d++;
	}
}
 
int bfs2(int s, int del) {
	queue<int> Q;
	bool v[N];
	int x, rp, np, d = 0, i, j, ans = 0, cnt = 1;
	memset(v, 0, sizeof(v));
	Q.push(s), v[s] = 1, rp = 1;
	while (!Q.empty()) {
		np = 0;
		while (rp--) {
			x = Q.front();
			Q.pop();
			ans += d;
			for (j = G[x]; j != -1; j = ET[j].next) {
				if (ET[j].id == del) continue;
				i = ET[j].b;
				if (!v[i]) {
					Q.push(i);
					v[i] = 1, np++, cnt++;
				}
			}
 
		}
		rp = np, d++;
	}
	if (cnt != n) return -1;
	return ans;
}
 
void solve() {
	int i, j, a, b;
	init();
	for (i = 0; i < m; i++) {
		scanf("%d%d", &a, &b);
		addedge(a, b, i);
		addedge(b, a, i);
	}
	for (i = 1; i <= n; i++)
		bfs(i);
	for (i = 0; i < 2 * m; i += 2) {
		int del = i / 2, ans = 0, t;
		for (j = 1; j <= n; j++) {
			if (vv[j][del] == 0) ans += sum[j];
			else {
				t = bfs2(j, del);
				if (t == -1) {
					ans = -1;
					break;
				}
				ans += t;
			}
		}
		if (ans == -1) printf("INF\n");
		else printf("%d\n", ans);
	}
}
int main() {
	while (~scanf("%d%d", &n, &m))
		solve();
	return 0;
}