// 2005 World Finals: Crossing Streets
// ACM-ICPC Live Archive 3274

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 1010
bool G[N][N];
int dis[N][N];
struct ROAD {
	int x1, y1, x2, y2;
	void get() {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x2 < x1) swap(x1, x2);
		if (y2 < y1) swap(y1, y2);
	}
};
ROAD rl[N];
int xx[N], yy[N], n;
struct POINT {
	POINT() {
	}
	POINT(int x, int y, int d) :
		x(x), y(y), d(d) {
	}
	int x, y, d;
	bool operator <(const POINT &p) const {
		return d > p.d;
	}
};
 
int dx[] = { 0, -1, 0, 1 };
int dy[] = { 1, 0, -1, 0 };
void solve() {
	int i, j, xz = 0, yz = 0, sx, sy, ex, ey, nx, ny;
	memset(G, 0, sizeof(G));
	for (i = 0; i < n; i++) {
		rl[i].get();
		xx[xz++] = rl[i].x1, yy[yz++] = rl[i].y1;
		xx[xz++] = rl[i].x2, yy[yz++] = rl[i].y2;
	}
	scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
	xx[xz++] = sx, yy[yz++] = sy;
	xx[xz++] = ex, yy[yz++] = ey;
	sort(xx, xx + xz);
	sort(yy, yy + yz);
	nx = unique(xx, xx + xz) - xx;
	ny = unique(yy, yy + yz) - yy;
	for (i = 0; i < n; i++) {
		int x1 = lower_bound(xx, xx + nx, rl[i].x1) - xx + 1;
		int x2 = lower_bound(xx, xx + nx, rl[i].x2) - xx + 1;
		int y1 = lower_bound(yy, yy + ny, rl[i].y1) - yy + 1;
		int y2 = lower_bound(yy, yy + ny, rl[i].y2) - yy + 1;
		if (x1 == x2) {
			for (j = y1 * 2; j <= y2 * 2; j++)
				G[x1 * 2][j] = 1;
		} else {
			for (j = x1 * 2; j <= x2 * 2; j++)
				G[j][y1 * 2] = 1;
		}
	}
	sx = lower_bound(xx, xx + nx, sx) - xx + 1;
	ex = lower_bound(xx, xx + nx, ex) - xx + 1;
	sy = lower_bound(yy, yy + ny, sy) - yy + 1;
	ey = lower_bound(yy, yy + ny, ey) - yy + 1;
	sx *= 2, sy *= 2, ex *= 2, ey *= 2;
	memset(dis, -1, sizeof(dis));
	dis[sx][sy] = 0;
	priority_queue<POINT> Q;
	Q.push(POINT(sx, sy, 0));
	int sz = (n + 2) * 2 + 3;
	while (!Q.empty()) {
		POINT top = Q.top();
		Q.pop();
		if (top.x == ex && top.y == ey) {
			printf("Peter has to cross %d streets\n", top.d);
			break;
		}
		for (i = 0; i < 4; i++) {
			int nx = top.x + dx[i], ny = top.y + dy[i];
			int nd = top.d + G[nx][ny];
			if (nx < 0 || ny < 0 || nx > sz || ny > sz) continue;
			if (dis[nx][ny] == -1 || nd < dis[nx][ny]) {
				dis[nx][ny] = nd;
				Q.push(POINT(nx, ny, nd));
			}
		}
	}
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n) {
		printf("City %d\n", ca++);
		solve();
	}
	return 0;
}