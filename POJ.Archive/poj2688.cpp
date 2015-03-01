// 2005 Japan Domestic: Cleaning Robot
// POJ 2688
#include <cstdio>
#include <cstring>
#define N 21
struct POINT{
	int r, c;
};

char map[N][N];
POINT plist[N], Q[N * N + 1];
int W, H, pp, g[N][N], best, mark[N];
int dx[4] = { 0, -1, 0, 1 }, dy[4] = { 1, 0, -1, 0 };

inline bool operator==(const POINT &a, const POINT &b) {
	return a.c == b.c && a.r == b.r;
}

inline bool operator!=(const POINT &a, const POINT &b) {
	return !(a.c == b.c && a.r == b.r);
}

void getmap() {
	char ch;
	pp = 1;
	for (int i = 0; i < H; i++) {
		getchar();
		for (int j = 0; j < W; j++) {
			ch = getchar();
			map[i][j] = ch;
			if (ch == '*') {
				plist[pp].r = i, plist[pp].c = j;
				pp++;
			} else if (ch == 'o')
				plist[0].r = i, plist[0].c = j;
		}
	}
}

int bfs(POINT a, POINT b) {
	POINT tp, np;
	int step[N][N], qh = 0, qt = 0;
	memset(step, 0, sizeof(step));
	step[a.r][a.c] = 1;
	Q[qt++] = a;
	while (qh < qt) {
		tp = Q[qh++];
		for (int i = 0; i < 4; i++) {
			np.c = tp.c + dx[i], np.r = tp.r + dy[i];
			if (np.c < 0 || np.r < 0 || np.r >= H || np.c >= W)
				continue;
			if (map[np.r][np.c] == 'x' || step[np.r][np.c])
				continue;
			step[np.r][np.c] = step[tp.r][tp.c] + 1;
			if (np == b)
				return step[np.r][np.c] - 1;
			Q[qt++] = np;
		}
	}
	return -1;
}

int create_map() {
	memset(g, 0, sizeof(g));
	for (int i = 0; i < pp; i++)
		for (int j = 0; j < pp; j++) {
			if (i == j)
				continue;
			int v = bfs(plist[i], plist[j]);
			if (v == -1)
				return 0;
			g[i][j] = v;
		}
	return 1;
}

void dfs(int t, int n, int pathlen) {
	if (n >= pp)
		if (pathlen < best) {
			best = pathlen;
			return;
		}
	for (int i = 1; i < pp; i++) {
		if (mark[i] || g[t][i] <= 0)
			continue;
		if (pathlen + g[t][i] >= best)
			continue;
		mark[i] = 1;
		dfs(i, n + 1, pathlen + g[t][i]);
		mark[i] = 0;
	}
}

void solve() {
	getmap();
	if (!create_map()) {
		printf("-1\n");
		return;
	}
	memset(mark, 0, sizeof(mark));
	best = (1 << 30);
	mark[0] = 1;
	dfs(0, 1, 0);
	printf("%d\n", best);
}
int main() {
	while (scanf("%d%d", &W, &H) && W)
		solve();
	return 0;
}
