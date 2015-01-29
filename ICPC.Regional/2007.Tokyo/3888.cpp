// 2007 Tokyo: The Morning after Halloween
// ACM-ICPC Live Archive 3888
// POJ 3523 
#include <cstdio>
#include <cstring>
#define N 16
char map[N][N];
short v[N][N][N][N][N][N];
struct POINT {
	short x, y;
	bool operator==(const POINT &p) const {
		return p.x == x && p.y == y;
	}
};
struct NODE {
	POINT p[3];
};
NODE gss, gse;
short dx[] = { 1, 0, -1, 0, 0 };
short dy[] = { 0, -1, 0, 1, 0 };
int m, n, gh;
inline bool checkok(POINT &p) {
	if (p.x < 0 || p.y < 0 || p.x >= n || p.y >= m) return false;
	if (map[p.x][p.y] == '#') return false;
	return true;
}
void init() {
	for (int a = 0; a < n; a++)
		for (int b = 0; b < m; b++)
			for (int c = 0; c < n; c++)
				for (int d = 0; d < m; d++)
					for (int e = 0; e < n; e++)
						for (int f = 0; f < m; f++)
							v[a][b][c][d][e][f] = 0;
	memset(gss.p, 0, sizeof(gss.p));
	memset(gse.p, 0, sizeof(gse.p));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char ch = getchar();
			if (ch >= 'a' && ch <= 'c') gss.p[ch - 'a'].x = i, gss.p[ch - 'a'].y = j;
			if (ch >= 'A' && ch <= 'C') gse.p[ch - 'A'].x = i, gse.p[ch - 'A'].y = j;
			map[i][j] = ch;
		}
		getchar();
	}
}
 
NODE Q1[800000];
NODE Q2[800000];
int qh[2], qe[2], step;
int expand(int dir, NODE &next) {
	int k = v[next.p[0].x][next.p[0].y][next.p[1].x][next.p[1].y][next.p[2].x][next.p[2].y];
	if (dir == 0) {
		if (k < 0) return step - k - 1;
		if (k == 0) {
			v[next.p[0].x][next.p[0].y][next.p[1].x][next.p[1].y][next.p[2].x][next.p[2].y] = step + 1;
			Q1[qe[0]++] = next;
		}
	} else {
		if (k > 0) return step + k - 1;
		if (k == 0) {
			v[next.p[0].x][next.p[0].y][next.p[1].x][next.p[1].y][next.p[2].x][next.p[2].y] = -step - 1;
			Q2[qe[1]++] = next;
		}
	}
	return 0;
}
 
inline int search(NODE *Q, int dir) {
	int sstep, i, j, k;
	if (dir == 1) sstep = -step;
	else sstep = step;
	while (qh[dir] < qe[dir]
			&& v[Q[qh[dir]].p[0].x][Q[qh[dir]].p[0].y][Q[qh[dir]].p[1].x][Q[qh[dir]].p[1].y][Q[qh[dir]].p[2].x][Q[qh[dir]].p[2].y] == sstep) {
		NODE h = Q[qh[dir]];
		qh[dir]++;
		for (i = 0; i < 5; i++) {
			NODE next = h;
			next.p[0].x += dx[i], next.p[0].y += dy[i];
			if (!checkok(next.p[0])) continue;
			if (gh == 1) {
				int ret = expand(dir, next);
				if (ret) return ret;
				continue;
			}
			for (j = 0; j < 5; j++) {
				next.p[1] = h.p[1];
				next.p[1].x += dx[j], next.p[1].y += dy[j];
				if (!checkok(next.p[1])) continue;
				if (next.p[1] == next.p[0]) continue;
				if (next.p[1] == h.p[0] && h.p[1] == next.p[0]) continue;
				if (gh == 2) {
					int ret = expand(dir, next);
					if (ret) return ret;
					continue;
				}
				for (k = 0; k < 5; k++) {
					next.p[2] = h.p[2];
					next.p[2].x += dx[k], next.p[2].y += dy[k];
					if (!checkok(next.p[2])) continue;
					if (next.p[2] == next.p[0] || next.p[2] == next.p[1]) continue;
					if (next.p[2] == h.p[0] && h.p[2] == next.p[0]) continue;
					if (next.p[2] == h.p[1] && h.p[2] == next.p[1]) continue;
					int ret = expand(dir, next);
					if (ret) return ret;
				}
			}
		}
	}
	return 0;
}
int dbfs() {
	v[gss.p[0].x][gss.p[0].y][gss.p[1].x][gss.p[1].y][gss.p[2].x][gss.p[2].y] = 1;
	v[gse.p[0].x][gse.p[0].y][gse.p[1].x][gse.p[1].y][gse.p[2].x][gse.p[2].y] = -1;
	qh[0] = qh[1] = 0, qe[0] = qe[1] = 1;
	step = 1;
	Q1[0] = gss, Q2[0] = gse;
	while (qh[0] < qe[0] && qh[1] < qe[1]) {
		int ret = search(Q1, 0);
		if (ret) return ret;
		ret = search(Q2, 1);
		if (ret) return ret;
		step++;
	}
	return -1;
}
int main() {
	while (scanf("%d%d%d\n", &m, &n, &gh) && n) {
		init();
		printf("%d\n", dbfs());
	}
	return 0;
}