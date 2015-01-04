// POJ 3732
// PKU Campus 2009 (POJ Monthly Contest – 2009.05.17): Paint Me Less
#include <cstdio>
#include <cstring>
#define N 4
#define M 20
struct OP {
	int x, y, c;
	void print() {
		printf("%d %d %d\n", x + 1, y + 1, c);
	}
	OP() {
	}
	OP(int x, int y, int c) :
		x(x), y(y), c(c) {
	}
};
OP opstack[M];
int depth, n, m;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
int judge(short cc[N][N]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (cc[i][j]) return 0;
	return 1;
}
 
int remain(short cc[N][N]) {
	bool have[M] = { 0 };
	int ans = 0, i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			have[cc[i][j]] = 1;
	for (i = 1; i < M; i++)
		ans += have[i];
	return ans;
}
 
void chcol(short st[N][N], int x, int y, int c) {
	int oc = st[x][y], qs=0, qe=1, Q[M];
	Q[qs]=x * m + y;
	st[x][y] = -1;
	while (qs < qe) {
		int top = Q[qs++];
		//st[top/m][top%m] = -1;
		for (int i = 0; i < 4; i++) {
			int nx = top / m + dx[i], ny = top % m + dy[i];
			if (nx == -1 || ny == -1 || nx == n || ny == m) continue;
			if (st[nx][ny] != oc) continue;
			st[nx][ny] = -1;
			Q[qe++]=nx * m + ny;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (st[i][j] == -1) st[i][j] = c;
}
int dfs(short st[N][N], int bx, int by, int dep) {
	int i, j, k, nc;
	short nst[N][N];
	if (judge(st)) return 1;
	if (dep + remain(st) > depth) return 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			if (i < bx && j < by) continue;
			bool havedo[M] = { 0 };
			for (k = 0; k < 4; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if (nx == -1 || nx == n || ny == -1 || ny == m) continue;
				nc = st[nx][ny];
				if (st[i][j] == nc || havedo[nc]) continue;
				havedo[nc] = 1;
				memcpy(nst, st, sizeof(nst));
				chcol(nst, i, j, nc);
				opstack[dep] = OP(i, j, nc);
				if (dfs(nst, i + 1, j + 1, dep + 1)) return 1;
			}
			nc = 0;
			memcpy(nst, st, sizeof(nst));
			chcol(nst, i, j, nc);
			opstack[dep] = OP(i, j, nc);
			if (dfs(nst, i + 1, j + 1, dep + 1)) return 1;
		}
	return 0;
}
void solve() {
	int i, j;
	short cc[N][N];
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%hd", &cc[i][j]);
	for (depth = remain(cc); depth <= 16; depth++)
		if (dfs(cc, 0, 0, 0)) break;
	printf("%d\n", depth);
	for (i = 0; i < depth; i++)
		opstack[i].print();
}
int main() {
	//freopen("in.txt", "r", stdin);
	while (~scanf("%d%d", &n, &m))
		solve();
	return 0;
}
