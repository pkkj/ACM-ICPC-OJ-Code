// 2007 Nouthwestern Europe: Escape from Enemy Territory
// ACM-ICPC Live Archive 3975
#include <cstdio>
#include <queue>
#include <cstring>
#define N 1005
using namespace std;

int d[N][N], d1[N][N];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int n, m;

struct POINT{
	int x, y;
};
void init_arr(int d[][N]) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			d[i][j] = -1;
}
int main() {
	int T, nb, x1, y1, x2, y2, i;

	scanf("%d", &T);
	while (T--) {
		queue<POINT> q;
		scanf("%d%d%d", &nb, &n, &m);
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		init_arr(d);
		for (i = 0; i < nb; i++) {
			POINT p;
			scanf("%d%d", &p.x, &p.y);
			d[p.x][p.y] = 0;
			q.push(p);
		}
		while (!q.empty()) {
			POINT p = q.front();
			q.pop();
			for (i = 0; i < 4; i++) {
				POINT np;
				np.x = p.x + dx[i], np.y = p.y + dy[i];
				if (np.x < 0 || np.x >= n || np.y < 0 || np.y >= m)
					continue;
				if (d[np.x][np.y] != -1)
					continue;
				d[np.x][np.y] = d[p.x][p.y] + 1;
				q.push(np);
			}
		}
		int lo = -1, hi = min(d[x1][y1], d[x2][y2]), ans, mid;
		while (lo != hi) {
			POINT sp;
			sp.x = x1, sp.y = y1;
			q.push(sp);
			mid = (lo + hi + 1) / 2;
			init_arr(d1);
			d1[x1][y1] = 0;
			while (!q.empty()) {
				POINT p = q.front();
				q.pop();
				for (i = 0; i < 4; i++) {
					POINT np;
					np.x = p.x + dx[i], np.y = p.y + dy[i];
					if (np.x < 0 || np.x >= n || np.y < 0 || np.y >= m)
						continue;
					if (d1[np.x][np.y] != -1 || d[np.x][np.y] < mid)
						continue;
					d1[np.x][np.y] = d1[p.x][p.y] + 1;
					q.push(np);
				}
			}
			if (d1[x2][y2] != -1)
				lo = mid, ans = d1[x2][y2];
			else
				hi = mid - 1;
		}
		printf("%d %d\n", lo, ans);

	}
	return 0;
}
