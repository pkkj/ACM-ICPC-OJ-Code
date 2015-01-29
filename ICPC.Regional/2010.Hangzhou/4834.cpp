// CII 4834
// 2010 Hangzhou: Prison Break
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 16
char map[N][N];
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };
 
#define SWITCH 1
#define ENERGY 2
#define START 3
struct POINT {
	int x, y, type, id;
	POINT() {
	}
	POINT(int x, int y, int type, int id) :
		x(x), y(y), type(type), id(id) {
	}
};
POINT plist[N];
int G[N][N];
int ne, ns, r, c, sz, sx, sy;
 
struct NODE {
	int id, st, value, solve;
	NODE() {
	}
	NODE(int id, int st, int value, int solve) :
		id(id), st(st), value(value), solve(solve) {
	}
	bool operator<(const NODE &nd) const {
		return value > nd.value;
	}
};
int dp[N][(1 << 14) + 1];
int judge(int en) {
	priority_queue<NODE> Q;
	Q.push(NODE(sz - 1, 0, en, 0));
	memset(dp, -1, sizeof(dp));
 
	while (!Q.empty()) {
		NODE cur = Q.top();
		Q.pop();
		if (cur.solve == ns) return 1;
		dp[cur.id][cur.st] = cur.value;
		for (int i = 0; i < sz - 1; i++) {
			if (G[cur.id][i] == -1) continue;
			int nid = i, nst = cur.st, nso = cur.solve, nv = cur.value - G[cur.id][i];
			if (nst & (1 << i) || nv < 0) continue;
			nst |= (1 << i);
			if (plist[i].type == SWITCH) nso++;
			else if (plist[i].type == ENERGY) nv = en;
			if (nv > dp[nid][nst]) Q.push(NODE(nid, nst, nv, nso));
		}
	}
	return 0;
}
void bfs(int id) {
	int dist[N][N];
	queue<int> Q;
	memset(dist, -1, sizeof(dist));
	Q.push(plist[id].x * c + plist[id].y);
	dist[plist[id].x][plist[id].y] = 0;
	while (!Q.empty()) {
		int pos = Q.front();
		Q.pop();
		int cx = pos / c, cy = pos % c;
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i], ny = cy + dy[i], nd = dist[cx][cy] + 1;
			if (nx < 0 || nx >= r || ny < 0 || ny >= c || map[nx][ny] == 'D') continue;
			if (dist[nx][ny] == -1) {
				dist[nx][ny] = nd;
				Q.push(nx * c + ny);
			}
		}
	}
	for (int i = 0; i < sz; i++)
		G[id][i] = dist[plist[i].x][plist[i].y];
}
 
int solve() {
	int i, j,sx,sy;
	sz = ne = ns = 0;
	for (i = 0; i < r; i++) {
		scanf("%s", map[i]);
		for (j = 0; j < c; j++) {
			if (map[i][j] == 'F') sx = i, sy = j;
			if (map[i][j] == 'G') plist[sz++] = POINT(i, j, ENERGY, ne++);
			if (map[i][j] == 'Y') plist[sz++] = POINT(i, j, SWITCH, ns++);
		}
	}
	if (ns == 0) return 0;
	for (i = 0; i < sz; i++)
		if (plist[i].type == ENERGY) plist[i].id += ns;
	plist[sz++] = POINT(sx, sy, START, 0);
	for (i = 0; i < sz; i++)
		bfs(i);
	int left = 1, right = 1000, ans = -1;
	if (!judge(right)) return -1;
	while (left < right) {
		int mid = (left + right) / 2;
		if (judge(mid)) {
			right = mid;
			ans = mid;
		} else left = mid + 1;
	}
	return ans;
}
int main() {
	while (scanf("%d%d", &r, &c) && r)
		printf("%d\n", solve());
	return 0;
}
