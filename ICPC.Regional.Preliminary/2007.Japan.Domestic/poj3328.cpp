// 2007 Japan Domestic: Cliff Climbing
// POJ 3228
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define N 100
#define RIGHT 1
#define LEFT 0
#define INF 1<<30

struct NODE {
	int x, y, flag, cost;
	NODE() {}
	NODE(int X, int Y, int F, int C) :
		x(X), y(Y), flag(F), cost(C) {
	}
};
bool operator <(const NODE &a, const NODE &b) {
	return a.cost > b.cost;
}

char map[N][N];
int m, n, dist[N][N][2];
bool visit[N][N][2];
priority_queue<NODE> Q;

bool outside(int x, int y) {
	return x > n || y > m || x < 1 || y < 1;
}

int dx[2][9] = { { 2, 1, 1, 0, 0, 0, -1, -1, -2 }, { 2, 1, 1, 0, 0, 0, -1, -1, -2 } };
int dy[2][9] = { { -1, -1, -2, -1, -2, -3, -1, -2, -1 }, { 1, 1, 2, 1, 2, 3, 1, 2, 1 } };

int dij() {
	int i, ddis;
	while (!Q.empty()) {
		NODE t = Q.top(), nt;
		Q.pop();
		if (map[t.x][t.y] == 'T') return t.cost;
		visit[t.x][t.y][t.flag] = 1;

		for (i = 0; i < 9; i++) {
			nt = t;
			nt.flag = !nt.flag;
			nt.x += dx[nt.flag][i], nt.y += dy[nt.flag][i];
			if (visit[nt.x][nt.y][nt.flag] || map[nt.x][nt.y] == 'X' || outside(nt.x, nt.y)) continue;
			ddis = map[nt.x][nt.y] == 'T' ? 0 : map[nt.x][nt.y] - '0';
			nt.cost += ddis;
			if (nt.cost < dist[nt.x][nt.y][nt.flag]) {
				dist[nt.x][nt.y][nt.flag] = nt.cost;
				Q.push(nt);
			}
		}
	}
	return -1;
}

void init() {
	int i, j;
	Q = priority_queue<NODE>();
	memset(visit, 0, sizeof(visit));
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			char ch;
			scanf("%c ", &ch);
			map[i][j] = ch;
			if (ch == 'S') {
				Q.push(NODE(i, j, LEFT, 0)), Q.push(NODE(i, j, RIGHT, 0));
				dist[i][j][LEFT] = dist[i][j][RIGHT] = 0;
			}
			else dist[i][j][LEFT] = dist[i][j][RIGHT] = INF;
		}
	}
}

int main() {
	while (scanf("%d%d ", &m, &n) && n + m) {
		init();
		printf("%d\n", dij());
	}
	return 0;
}
