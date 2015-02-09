// 2005 Southwestern Europe: Black Box
// ACM-ICPC Live Archive 3509
#include <cstdio>
#include <cstring>
#include <vector>
#define N 10
using namespace std;

struct ITEM {
	int in, out;
};
vector<ITEM> experiment;
struct POINT {
	int x, y;
	POINT() { }
	POINT(int x, int y) : x(x), y(y) { }
};

struct SHOT {
	POINT st;
	int dx, dy;
};
POINT tmpSolution[N], solution[N];
int nsolve;
bool board[N][N];
SHOT getgatepos(int id) {
	SHOT ret;
	if (id >= 0 && id <= 7) ret.dx = 0, ret.dy = 1, ret.st = POINT(id, 0);
	else if (id >= 8 && id <= 15) ret.dx = -1, ret.dy = 0, ret.st = POINT(7, id - 8);
	else if (id >= 16 && id <= 23) ret.dx = 0, ret.dy = -1, ret.st = POINT(23 - id, 7);
	else if (id >= 24 && id <= 31) ret.dx = 1, ret.dy = 0, ret.st = POINT(0, 31 - id);
	return ret;
}
int outside(int x, int y) {
	return x < 0 || x > 7 || y < 0 || y > 7;
}
int shoot(SHOT &sh) {
	int cx, cy, nx, ny, dx, dy;
	cx = sh.st.x, cy = sh.st.y;
	dx = sh.dx, dy = sh.dy;
	while (1) {
		nx = cx + dx, ny = cy + dy;
		if (outside(nx, ny)) break;
		if (board[nx][ny]) return -1; // Light is absorbed

		// Light is deviated by atoms
		if (dx == 0) {
			if (!outside(nx + 1, ny) && board[nx + 1][ny]) {
				dx = -1, dy = 0;
				continue;
			}
			if (!outside(nx - 1, ny) && board[nx - 1][ny]) {
				dx = 1, dy = 0;
				continue;
			}
		}
		if (dy == 0) {
			if (!outside(nx, ny + 1) && board[nx][ny + 1]) {
				dx = 0, dy = -1;
				continue;
			}
			if (!outside(nx, ny - 1) && board[nx][ny - 1]) {
				dx = 0, dy = 1;
				continue;
			}
		}
		// Light goes straight ahead
		cx = nx, cy = ny;
	}
	if (cx == 0 && cy == 0) {
		if (dx == 0) return 0;
		else return 31;
	}
	if (cx == 0 && cy == 7) {
		if (dx == 0) return 23;
		else return 24;
	}
	if (cx == 7 && cy == 0) {
		if (dx == 0) return 7;
		else return 8;
	}
	if (cx == 7 && cy == 7) {
		if (dx == 0) return 16;
		else return 15;
	}
	if (cy == 0) return cx;
	if (cy == 7) return 23 - cx;
	if (cx == 0) return 31 - cy;
	return cy + 8;

}

int check() {
	memset(board, 0, sizeof(board));
	for (int i = 0; i < 5; i++)
		board[tmpSolution[i].x][tmpSolution[i].y] = 1;
	for (int i = 0; i < (int)experiment.size(); i++) {
		SHOT st = getgatepos(experiment[i].in);
		if (shoot(st) != experiment[i].out) return 0;
	}
	return 1;
}

void print() {
	char g[N][N];
	memset(g, '-', sizeof(g));
	for (int i = 0; i < 5; i++)
		g[solution[i].x][solution[i].y] = '+';
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
			putchar(g[i][j]);
		putchar('\n');
		
	}
}
void dfs(int dep, int bx, int by) {
	if (nsolve > 1) return;
	if (dep == 5) {
		if (check()) {
			nsolve++;
			for (int i = 0; i < 5; i++)
				solution[i] = tmpSolution[i];
		}
		return;
	}
	for (int i = bx; i <= 6; i++) {
		for (int j = i == bx ? by : 1; j <= 6; j++) {
			int ok = 1;
			for (int k = 0; k < dep && ok; k++)
				if (tmpSolution[k].x == i && tmpSolution[k].y == j) ok = 0;
			if (ok) {
				tmpSolution[dep].x = i, tmpSolution[dep].y = j;
				dfs(dep + 1, i, j);
			}
		}
	}
}

int main() {
	int n, i, T, begin = true;
	scanf("%d", &T);
	while (T--){
		if (begin) begin = false;
		else printf("\n");
		scanf("%d", &n);
		experiment.resize(n);
		for (i = 0; i < n; i++)
			scanf("%d%d", &experiment[i].in, &experiment[i].out);
		nsolve = 0;
		dfs(0, 1, 1);
		if (nsolve > 1 || nsolve == 0) printf("NO\n");
		else print();
	}
	return 0;
}
