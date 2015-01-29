// 2006 Yokohama: Manhattan Wiring
// POJ 3133
// ACM-ICPC Live Archive 3620
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 9
const int INF = 1 << 20;
const int MAX_STATE = 59049 + 1;
int n, m, g[N][N];
int best[N][N][MAX_STATE];

struct STATE {
	int up[N], left;
	STATE() : left(0) {}

	// Encode the status to a integer. It's used in querying the best array.
	int encode() {
		int code = left;
		for (int i = 0; i < m; i++)
			code = code * 3 + up[i];
		return code;
	}

	// Determine whether the next status is legal. If legal, then generate the new status.
	bool generateNext(int row, int col, int up, int down, int left, int right, STATE &newState) {
		// It's illegal to exceed the boundary.
		if (col == 0 && left || row == 0 && up || col == m - 1 && right || row == n - 1 && down)
			return false;
		// The plug-ins must match
		if (left != this->left || up != this->up[col])
			return false;

		// The only changed plug-in is the left one and up[col] one.
		for (int i = 0; i < m; i++)
			newState.up[i] = this->up[i];
		newState.up[col] = down;
		newState.left = right;
		return true;
	}
};

int calc(int x, int y, STATE &state) {
	if (y == m)
		x++, y = 0;
	if (x == n)
		return 0;

	int key = state.encode();
	if (best[x][y][key] != -1)
		return best[x][y][key];

	STATE newState;
	int ans = INF;

	if (g[x][y] == 0) {
		// Empty cell, we can try all combination : no plug-in or plug-ins with two ends.
		if (state.generateNext(x, y, 0, 0, 0, 0, newState))
			ans = min(ans, calc(x, y + 1, newState));
		for (int t = 1; t < 3; t++) {
			if (state.generateNext(x, y, 0, 0, t, t, newState))
				ans = min(ans, calc(x, y + 1, newState) + 2);
			if (state.generateNext(x, y, t, t, 0, 0, newState))
				ans = min(ans, calc(x, y + 1, newState) + 2);
			if (state.generateNext(x, y, t, 0, t, 0, newState))
				ans = min(ans, calc(x, y + 1, newState) + 2);
			if (state.generateNext(x, y, t, 0, 0, t, newState))
				ans = min(ans, calc(x, y + 1, newState) + 2);
			if (state.generateNext(x, y, 0, t, 0, t, newState))
				ans = min(ans, calc(x, y + 1, newState) + 2);
			if (state.generateNext(x, y, 0, t, t, 0, newState))
				ans = min(ans, calc(x, y + 1, newState) + 2);
		}
	} else if (g[x][y] == 1) {
		if (state.generateNext(x, y, 0, 0, 0, 0, newState))
			ans = min(ans, calc(x, y + 1, newState));
	} else if (g[x][y] >= 2) {
		// The cell which is the endpoint of the polyline. We can only try the plug-ins with one end
		if (state.generateNext(x, y, g[x][y] - 1, 0, 0, 0, newState))
			ans = min(ans, calc(x, y + 1, newState) + 1);
		if (state.generateNext(x, y, 0, g[x][y] - 1, 0, 0, newState))
			ans = min(ans, calc(x, y + 1, newState) + 1);
		if (state.generateNext(x, y, 0, 0, g[x][y] - 1, 0, newState))
			ans = min(ans, calc(x, y + 1, newState) + 1);
		if (state.generateNext(x, y, 0, 0, 0, g[x][y] - 1, newState))
			ans = min(ans, calc(x, y + 1, newState) + 1);
	}
	return best[x][y][key] = ans;
}

int main() {
	while (scanf("%d%d", &n, &m) && n) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);

		STATE s;
		memset(best, -1, sizeof(best));
		memset(s.up, 0, sizeof(s.up));
		int ans = calc(0, 0, s);
		if (ans == INF)
			ans = 0;
		printf("%d\n", ans / 2);

	}
	return 0;
}
