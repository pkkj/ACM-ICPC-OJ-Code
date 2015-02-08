// 2006 Beijing: Animal Run
// ACM-ICPC Live Archive 3661
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 1005
int n, m;
int xie[N][N], heng[N][N], shu[N][N];
struct NODE {
	int x, y, b, w;
	NODE(int x, int y, int b, int w) :
		x(x), y(y), b(b), w(w) {
	}
	NODE() {
	}
	bool operator <(const NODE &n) const {
		return w > n.w;
	}
};
int dist[N][N][2];
void relax(int x, int y, int b, int w, priority_queue<NODE> &Q) {
	if (dist[x][y][b] > w || dist[x][y][b] == -1) {
		dist[x][y][b] = w;
		Q.push(NODE(x, y, b, w));
	}
}
int solve() {
	int i, j;
	n--, m--;
	for (i = 1; i <= n + 1; i++)
		for (j = 1; j <= m; j++)
			scanf("%d", &heng[i][j]);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m + 1; j++)
			scanf("%d", &shu[i][j]);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			scanf("%d", &xie[i][j]);
	priority_queue<NODE> Q;
	memset(dist, -1, sizeof(dist));
	for (i = 1; i <= m; i++) {
		Q.push(NODE(n, i, 1, heng[n + 1][i]));
		dist[n][i][1] = heng[n + 1][i];
	}
	for (i = 1; i <= n; i++) {
		Q.push(NODE(i, 1, 1, shu[i][1]));
		dist[i][1][1] = shu[i][1];
	}
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (top.x < 1 || top.y > m) return top.w;
		int cx = top.x, cy = top.y, cb = top.b;
		if (top.w > dist[cx][cy][cb]) continue;
		if (cb) {
			relax(cx, cy, 0, xie[cx][cy] + top.w, Q);
			if (cy - 1 >= 1) relax(cx, cy - 1, 0, shu[cx][cy] + top.w, Q);
			if (cx + 1 <= n) relax(cx + 1, cy, 0, heng[cx + 1][cy] + top.w, Q);
		} else {
			relax(cx, cy, 1, xie[cx][cy] + top.w, Q);
			relax(cx - 1, cy, 1, heng[cx][cy] + top.w, Q);
			relax(cx, cy + 1, 1, shu[cx][cy + 1] + top.w, Q);
		}
	}
	return -1;
}
int main() {
	int ca = 1;
	while (scanf("%d%d", &n, &m) && n)
		printf("Case %d: Minimum = %d\n", ca++, solve());
	return 0;
}