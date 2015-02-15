// 2008 Harbin: Carrying Out A Task
// ACM-ICPC Live Archive 4319

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 25
int n, m, d, act, limit;
//act:可以加速的次数
//limit:最小要经过多少次漩涡
char map[N][N];
 
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };
short acst[N][N][4]; //标记一个格子的一个方向的行走状态.0:只能正常行走,1:可以加速,也可以正常行走.2:必须加速进入漩涡.
struct POINT {
	int x, y, d;
	POINT() {
	}
	POINT(int x, int y, int d) :
		x(x), y(y), d(d) {
	}
	bool operator<(const POINT &p) const {
		return d > p.d;
	}
};
POINT ps, pe;
struct NODE {
	int x, y, op, dam, ac, ca;
	NODE() {
	}
	NODE(int x, int y, int op, int dam, int ac, int ca) :
		x(x), y(y), op(op), dam(dam), ac(ac), ca(ca) {
	}
	bool operator<(const NODE &p) const {
		if (dam != p.dam) return dam > p.dam;
		if(ca != p.ca) return ca > p.ca;
		return op > p.op;
	}
};
 
int getlowerbound() {
	bool v[N][N];
	priority_queue<POINT> Q;
	memset(v, 0, sizeof(v));
	Q.push(ps);
	while (!Q.empty()) {
		POINT top = Q.top();
		Q.pop();
		if (v[top.x][top.y]) continue;
		if (top.x == pe.x && top.y == pe.y) return top.d;
		v[top.x][top.y] = 1;
		for (int i = 0; i < 4; i++) {
			int nx = top.x + dx[i], ny = top.y + dy[i], nd = top.d;
			if (map[nx][ny] == '#' || v[nx][ny]) continue;
			if (map[nx][ny] == '*') nd++;
			Q.push(POINT(nx, ny, nd));
		}
	}
	return -1;
}
 
int accelearate(int x, int y, int dir) {
	if (map[x + dx[dir]][y + dy[dir]] == '*') return 2;
	for (int i = 1; i <= d; i++)
		if (map[x + i * dx[dir]][y + i * dy[dir]] == '*' || map[x + i * dx[dir]][y + i * dy[dir]] == '#') return 0;
	return 1;
}
void getokac() {
	int i, j, k;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++) {
			if (map[i][j] == '#' || map[i][j] == 'E') continue;
			for (k = 0; k < 4; k++)
				acst[i][j][k] = accelearate(i, j, k);
		}
}
bool v[N][N][100];
int find() {
	priority_queue<NODE> Q;
	memset(v, 0, sizeof(v));
	Q.push(NODE(ps.x, ps.y, 0, 0, 0, 0));
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (v[top.x][top.y][top.ac]) continue;
		if (top.x == pe.x && top.y == pe.y) return top.op;
		v[top.x][top.y][top.ac] = 1;
		for (int i = 0; i < 4; i++) {
			int nx, ny, nac, ndam;
			// Accelerate
			if (acst[top.x][top.y][i] == 1) {
				nx = top.x + d * dx[i], ny = top.y + d * dy[i], nac = top.ac + 1;
				if (!v[nx][ny][nac] && nac <= act) Q.push(NODE(nx, ny, top.op + 1, top.dam, nac, top.ca + d));
			}
			// Meet eddy
			if (acst[top.x][top.y][i] == 2) {
				nx = top.x + dx[i], ny = top.y + dy[i], nac = top.ac + 1, ndam = top.dam + 1;
				if (!v[nx][ny][nac] && nac <= act && ndam <= limit) Q.push(NODE(nx, ny, top.op + 1, ndam, nac, top.ca + 1));
			}
			// Normal advance
			if (acst[top.x][top.y][i] != 2) {
				nx = top.x + dx[i], ny = top.y + dy[i];
				if (map[nx][ny] != '#' && !v[nx][ny][top.ac])
				Q.push(NODE(nx, ny, top.op + 1, top.dam, top.ac, top.ca + 1));
			}
		}
	}
	return -1;
}
void solve() {
	int i, j;
	memset(map, '#', sizeof(map));
	scanf("%d%d\n", &n, &m);
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			map[i][j] = getchar();
			if (map[i][j] == 'S') ps = POINT(i, j, 0);
			else if (map[i][j] == 'E') pe = POINT(i, j, 0);
		}
		getchar();
	}
	scanf("%d%d%d", &d, &i, &j);
	act = i / j;
	//求出最小的进入漩涡次数,用来卡dijkstra时扩展的下界.顺便剔除不可能到达的情况
	limit = getlowerbound();
	if (limit == -1 || limit != -1 && limit > act) {
		printf("can not reach!\n");
		return;
	}
	getokac();
	printf("%d\n", find());
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}