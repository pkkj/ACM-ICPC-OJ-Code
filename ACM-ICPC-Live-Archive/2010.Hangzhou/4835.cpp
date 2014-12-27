// CII 4835
// 2010 Hangzhou: To Be an Dream Architect

#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1005
using namespace std;
struct POINT {
	short x, y, z;
	POINT() {
	}
	POINT(int x, int y, int z) :
		x(x), y(y), z(z) {
	}
	bool operator<(const POINT &pt) const {
		if (x != pt.x) return x < pt.x;
		if (y != pt.y) return y < pt.y;
		return z < pt.z;
	}
	bool operator!=(const POINT &pt) const {
		return x != pt.x || y != pt.y || z != pt.z;
	}
};
POINT plist[N * N];
char cmd[1000];
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, sz = 0, ans = 0, i;
		scanf("%d%d", &n, &m);
		while (m--) {
			scanf("%s", cmd);
			int len = strlen(cmd), i1, i2;
			char c1, c2;
			for (i = 0; i < len; i++) {
				if (cmd[i] == ',') {
					cmd[i] = 0;
					break;
				}
			}
			sscanf(cmd + 2, "%d", &i1);
			sscanf(cmd + i + 3, "%d", &i2);
			if (i1 < 1 || i1 > n || i2 < 1 || i2 > n) continue;
			c1 = cmd[0], c2 = cmd[i + 1];
			if (c1 == 'X' && c2 == 'Y') {
				for (i = 1; i <= n; i++)
					plist[sz++] = POINT(i1, i2, i);
			}
			if (c2 == 'X' && c1 == 'Y') {
				for (i = 1; i <= n; i++)
					plist[sz++] = POINT(i2, i1, i);
			}
			if (c1 == 'X' && c2 == 'Z') {
				for (i = 1; i <= n; i++)
					plist[sz++] = POINT(i1, i, i2);
			}
			if (c2 == 'X' && c1 == 'Z') {
				for (i = 1; i <= n; i++)
					plist[sz++] = POINT(i2, i, i1);
			}
			if (c1 == 'Y' && c2 == 'Z') {
				for (i = 1; i <= n; i++)
					plist[sz++] = POINT(i, i1, i2);
			}
			if (c2 == 'Y' && c1 == 'Z') {
				for (i = 1; i <= n; i++)
					plist[sz++] = POINT(i, i2, i1);
			}
		}
		sort(plist, plist + sz);
		for (i = 1; i < sz; i++)
			if (plist[i] != plist[i - 1]) ans++;
		printf("%d\n", ans + 1);
	}
	return 0;
}
