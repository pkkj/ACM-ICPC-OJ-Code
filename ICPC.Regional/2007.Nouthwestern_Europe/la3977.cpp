// 2007 Northwestern Europe: Summits
// ACM-ICPC Live Archive 3977
// POJ 3503
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
using namespace std;
#define N 505

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int landscape[N][N], vis[N][N], q[N*N], d, n, m;
pair<int, int> points[N*N];

int floodfill(int mark, int x, int y){
	int qh = 0, qe = 0;
	int h = landscape[x][y], ans = 0;
	bool ok = true;
	q[qe++] = x * m + y;

	while (qh < qe){
		int pos = q[qh++];
		x = pos / m, y = pos % m;
		if (vis[x][y] != -1) continue;
		vis[x][y] = mark;
		if (landscape[x][y] == h)
			ans++;
		for (int i = 0; i < 4; i++){
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
			if (landscape[nx][ny] == -1) continue;
			if (landscape[nx][ny] <= h - d) continue;
			if (vis[nx][ny] != -1 && vis[nx][ny] != mark) ok = false;
			if (vis[nx][ny] == -1) q[qe++] = nx * m + ny;
		}
	}
	return ok ? ans : 0;
}

int main(){
	int T;
	scanf("%d", &T);
	while (T--)   {
		int ans = 0, cntPoint = 0;
		scanf("%d%d%d", &n, &m, &d);
		memset(vis, -1, sizeof(vis));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++){
				scanf("%d", &landscape[i][j]);
				points[cntPoint++] = make_pair(landscape[i][j], i*m + j);
			}

		sort(points, points + cntPoint);
		for (int i = cntPoint - 1; i >= 0; i--)
			ans += floodfill(i, points[i].second / m, points[i].second % m);

		printf("%d\n", ans);
	}

	return 0;
}
