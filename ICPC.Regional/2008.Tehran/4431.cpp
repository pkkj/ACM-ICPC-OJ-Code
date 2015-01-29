// CII 4431
// 2008 Tehran: Fruit Weights
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
#define N 105
#define EPS 1e-8
double g[N][N];
char s1[N], s2[N];
int n;
map<string, int> MAP;
 
void solve() {
	int i, j, k, cnt = 0, a, b, x, y;
	memset(g, 0, sizeof(g));
	MAP.clear();
	for (i = 0; i < n; i++) {
		scanf("%d%s%d%s", &a, s1, &b, s2);
		if (MAP.find(string(s1)) == MAP.end()) MAP[string(s1)] = cnt++;
		if (MAP.find(string(s2)) == MAP.end()) MAP[string(s2)] = cnt++;
		x = MAP[string(s1)], y = MAP[string(s2)];
		g[y][x] = max(g[y][x], (double) a / b);
	}
 
	for (i = 0; i < cnt; i++)
		g[i][i] = 1;
	for (k = 0; k < cnt; k++)
		for (i = 0; i < cnt; i++)
			for (j = 0; j < cnt; j++)
				if (g[i][k] > 0 && g[k][j] > 0) g[i][j] = max(g[i][j], g[i][k] * g[k][j]);
 
	scanf("%d%s%d%s", &a, s1, &b, s2);
	x = MAP[string(s1)], y = MAP[string(s2)];
 
	for (i = 0; i < cnt; i++)
		if (g[i][i] > 1) {
			puts("INCONSISTENT");
			return;
		}
	if (g[y][x] >= (double) a / b - EPS && g[x][y] >= (double) b / a - EPS) puts("==");
	else if (g[y][x] >= (double) a / b - EPS) puts("<=");
	else if (g[x][y] >= (double) b / a - EPS) puts(">=");
	else puts("UNAVAILABLE");
 
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
