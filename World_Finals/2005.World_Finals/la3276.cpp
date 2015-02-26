// 2005 World Finals: The Great Wall Game
// ACM-ICPC Live Archive 3276

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 16
#define INF 10000
int nx, ny, w[N][N], lx[N], ly[N];
int fx[N], fy[N];
int matx[N], maty[N];
int path(int u) {
	int v;
	fx[u] = 1;
	for (v = 1; v <= ny; v++) {
		if (lx[u] + ly[v] == w[u][v] && fy[v] < 0) {
			fy[v] = 1;
			if (maty[v] < 0 || path(maty[v])) {
				matx[u] = v, maty[v] = u;
				return 1;
			}
		}
	}
	return 0;
}
int KM() {
	int ans = 0, p, i, j, k;
	memset(ly, 0, sizeof(ly));
	for (i = 1; i <= nx; i++) {
		lx[i] = 0x7fffffff + 1;
		for (j = 1; j <= ny; j++)
			if (w[i][j] > lx[i]) lx[i] = w[i][j];
	}
	memset(matx, -1, sizeof(matx));
	memset(maty, -1, sizeof(maty));
	for (i = 1; i <= nx; i++) {
		memset(fx, -1, sizeof(fx));
		memset(fy, -1, sizeof(fy));
		if (!path(i)) {
			i--;
			p = 0x7fffffff;
			for (k = 1; k <= nx; k++) {
				if (fx[k] > 0) {
					for (j = 1; j <= ny; j++) {
						if (fy[j] < 0 && lx[k] + ly[j] - w[k][j] < p) p = lx[k] + ly[j] - w[k][j];
					}
				}
			}
			for (j = 1; j <= ny; j++)
				ly[j] += (fy[j] < 0 ? 0 : p);
			for (j = 1; j <= nx; j++)
				lx[j] -= (fx[j] < 0 ? 0 : p);
		}
	}
	for (i = 1; i <= ny; i++) {
		if (maty[i] == -1) continue;
		ans += w[maty[i]][i];
	}
	return ans;
}
 
struct POINT {
	int x, y;
	void get() {
		scanf("%d%d", &x, &y);
	}
	POINT() {
	}
	POINT(int x, int y) :
		x(x), y(y) {
	}
};
int dis(POINT a, POINT b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}
int n;
POINT st[N], wa[N];
void make() {
	for (int x = 1; x <= n; x++)
		for (int y = 1; y <= n; y++)
			w[x][y] = -dis(wa[x], st[y]);
}
 
int solve() {
	int ans = INF, i, j;
	for (i = 1; i <= n; i++)
		st[i].get();
	nx = ny = n;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++)
			wa[j] = POINT(i, j);
		make();
		ans = min(ans, -KM());
		for (j = 1; j <= n; j++)
			wa[j] = POINT(j, i);
		make();
		ans = min(ans, -KM());
	}
	for (i = 1; i <= n; i++)
		wa[i] = POINT(i, i);
	make();
	ans = min(ans, -KM());
 
	for (i = 1; i <= n; i++)
		wa[i] = POINT(i, n + 1 - i);
	make();
	ans = min(ans, -KM());
	return ans;
}
 
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n)
		printf("Board %d: %d moves required.\n\n", ca++, solve());
	return 0;
}