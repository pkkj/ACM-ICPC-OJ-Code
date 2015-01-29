// CII 4118 
// 2008 World Finals: Air Conditioning Machinery
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;
#define N 25
int nx, ny, nz, sx, sy, sz, sd, ex, ey, ez, ed;
map<string, int> DIR;
int dx[] = { 0, 0, 0, 0, -1, 1 };
int dy[] = { 0, 0, -1, 1, 0, 0 };
int dz[] = { -1, 1, 0, 0, 0, 0 };
int getdir(int x, int y, int z) {
	if (x == 1) return 5;
	if (x == -1) return 4;
	if (y == 1) return 3;
	if (y == -1) return 2;
	if (z == 1) return 1;
	/*if (z == -1) */return 0;
}
int DEP;
bool oc[N][N][N];
bool dfs(int use, int x, int y, int z, int dir) {
	int tmp[4][3], sz;
	if (DEP == use) {
		if (x == ex && y == ey && z == ez && dir == ed) return 1;
		return 0;
	}
	int i, j, k, cx, cy, cz, cd, l1, l2, t;
	for (i = 0; i < 6; i++) {
		if (i == dir || i == (dir ^ 1)) continue;
		for (t = 0; t < 2; t++) {
			int ok = 1;
			cx = x, cy = y, cz = z, cd = i, sz = 0;
			if (t == 0) l1 = 2, l2 = 2;
			else l1 = 3, l2 = 1;
			for (j = 1; j <= l1; j++) {
				cx += dx[dir], cy += dy[dir], cz += dz[dir];
				if (oc[cx][cy][cz] || cx < 1 || cy < 1 || cz < 1 || cx > nx || cy > ny || cz > nz) {
					ok = 0;
					for (k = 0; k < sz; k++)
						oc[tmp[k][0]][tmp[k][1]][tmp[k][2]] = 0;
					break;
				} else {
					oc[cx][cy][cz] = 1;
					tmp[sz][0] = cx, tmp[sz][1] = cy, tmp[sz][2] = cz;
					sz++;
				}
			}
			if (ok) {
				for (j = 1; j <= l2; j++) {
					cx += dx[i], cy += dy[i], cz += dz[i];
					if (oc[cx][cy][cz] || cx < 1 || cy < 1 || cz < 1 || cx > nx || cy > ny || cz > nz) {
						ok = 0;
						for (k = 0; k < sz; k++)
							oc[tmp[k][0]][tmp[k][1]][tmp[k][2]] = 0;
						break;
					} else {
						oc[cx][cy][cz] = 1;
						tmp[sz][0] = cx, tmp[sz][1] = cy, tmp[sz][2] = cz;
						sz++;
					}
				}
				if (ok) {
					if (dfs(use + 1, cx, cy, cz, cd)) return 1;
					else {
						for (k = 0; k < sz; k++)
							oc[tmp[k][0]][tmp[k][1]][tmp[k][2]] = 0;
					}
				}
			}
		}
	}
	return 0;
}
void solve() {
	char s[5];
	scanf("%d%d", &ny, &nz);
	scanf("%d%d%d%s", &sx, &sy, &sz, s);
	sd = DIR[string(s)];
	scanf("%d%d%d%s", &ex, &ey, &ez, s);
	ed = DIR[string(s)];
	sx -= dx[sd], sy -= dy[sd], sz -= dz[sd];
	for (DEP = 1; DEP <= 6; DEP++)
		memset(oc, 0, sizeof(oc));
		if (dfs(0, sx, sy, sz, sd)) {
			printf("%d\n", DEP);
			return;
		}
	printf("Impossible\n");
}
int main() {
	int ca = 1;
	DIR["-z"] = 0, DIR["+z"] = 1;
	DIR["-y"] = 2, DIR["+y"] = 3;
	DIR["-x"] = 4, DIR["+x"] = 5;
	while (scanf("%d", &nx) && nx) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
