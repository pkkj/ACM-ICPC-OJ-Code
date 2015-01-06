// CII 3528
// 2005 Central Europe: The Warehouse
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
#define N 8
int n;
struct NODE {
	short int map[N][N];
	int x, y;
	bool operator <(const NODE &p) const {
		int i, j;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (map[i][j] != p.map[i][j]) return map[i][j] < p.map[i][j];
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};
 
short dx[] = { 0, 1, -1, 0 };
short dy[] = { 1, 0, 0, -1 };
 
NODE start;
set<NODE> S;
short chmap[200];
void setmap() {
	chmap['.'] = 0, chmap['1'] = 1, chmap['2'] = 2, chmap['3'] = 3;
	chmap['4'] = 4, chmap['E'] = 5;
}
inline bool checkdown(const NODE &nn, int dir) {
	int x = nn.x, y = nn.y, i, cnt = nn.map[nn.x][nn.y];
	if (nn.map[x][y] == 1 || nn.map[x][y] == 5) return false;
	for (i = 0; i < cnt; i++) {
		x += dx[dir], y += dy[dir];
		if (x == -1 || y == -1 || x == n || y == n) return false;
		if (nn.map[x][y]) return false;
	}
	return true;
}
inline void pulldown(NODE &nn, int dir) {
	int x = nn.x, y = nn.y, i, cnt = nn.map[nn.x][nn.y];
	nn.map[x][y] = 0;
	for (i = 0; i < cnt; i++) {
		x += dx[dir], y += dy[dir];
		nn.map[x][y] = 1;
	}
	nn.x += dx[dir], nn.y += dy[dir];
}
NODE Q[100000];
int bfs() {
	int i, j, step = 0, ins, news, qh = 0, qe = 1;
	char ch;
	start.x--, start.y--;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			start.map[i][j] = chmap[(int) (ch = getchar())];
		getchar();
	}
	S.clear();
	Q[qh] = start;
	S.insert(start);
	ins = 1;
	while (qh < qe) {
		news = 0;
		while (ins--) {
			NODE top = Q[qh++];
			if (top.map[top.x][top.y] == 5) return step;
			for (i = 0; i < 4; i++) {
				NODE next = top;
				next.x += dx[i], next.y += dy[i];
				if (next.x == -1 || next.y == -1 || next.x == n || next.y == n) continue;
				if (next.map[next.x][next.y] != 0) {
					if (S.find(next) == S.end()) {
						Q[qe++] = next;
						S.insert(next);
						news++;
					}
				}
				if (checkdown(top, i)) {
					NODE next = top;
					pulldown(next, i);
					if (S.find(next) == S.end()) {
						Q[qe++] = next;
						S.insert(next);
						news++;
					}
				}
			}
		}
		ins = news;
		step++;
	}
	return -1;
}
int main() {
	setmap();
	while (scanf("%d%d%d\n", &n, &start.x, &start.y) && n) {
		int ret = bfs();
		if (ret == -1) printf("Impossible\n");
		else printf("%d\n", ret);
	}
}
