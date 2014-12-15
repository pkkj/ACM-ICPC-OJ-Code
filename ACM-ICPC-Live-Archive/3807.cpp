// CII 3807 
// World Final 2006: Marble Game
// BFS
#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
#define SZ 4
#define N (1<<18)
int n, m, w;
struct ST {
	int p[SZ][SZ];
	bool operator<(const ST &s) const {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (p[i][j] != s.p[i][j]) return p[i][j] < s.p[i][j];
		return 0;
	}
	bool operator==(const ST &s) const {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (p[i][j] != s.p[i][j]) return 0;
		return 1;
	}
};
bool wall[SZ][SZ][SZ][SZ];
 
ST Q[N];
set<ST> S;
void solve() {
	ST src, dest;
	int i, j, k, x, y, qh, qe, inq, next, step;
	memset(wall, 0, sizeof(wall));
	memset(src.p, 0, sizeof(src.p));
	memset(dest.p, 0, sizeof(dest.p));
	for (i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		src.p[x][y] = i + 1;
	}
	for (i = 0; i < m; i++) {
		scanf("%d%d", &x, &y);
		src.p[x][y] = -i - 1;
	}
	for (i = 0; i < w; i++) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		wall[x1][y1][x2][y2] = 1;
		wall[x2][y2][x1][y1] = 1;
	}
	qh = qe = step = 0;
	Q[qe++] = src;
	inq = 1;
	S.clear();
	S.insert(src);
	while (qh < qe) {
		ST st, nst;
		next = 0;
		while (inq--) {
			bool ok;
			st = Q[qh++];
			if (st == dest) {
				printf("%d moves\n", step);
				return;
			}
			// Lift left
			nst = st, ok = 1;
			for (i = 0; i < n && ok; i++)
				for (j = n - 2; j >= 0 && ok; j--) {
					if (nst.p[i][j] <= 0) continue;
					for (k = j; k < n - 1; k++) {
						if (wall[i][k][i][k + 1] || nst.p[i][k + 1] > 0) break;
						if (nst.p[i][k + 1] == 0) swap(nst.p[i][k], nst.p[i][k + 1]);
						else {
							if (nst.p[i][k] == -nst.p[i][k + 1]) nst.p[i][k] = nst.p[i][k + 1] = 0;
							else ok = 0;
							break;
						}
					}
				}
			if (ok && S.find(nst) == S.end()) {
				Q[qe++] = nst;
				S.insert(nst);
				next++;
			}
 
			// Lift right
			nst = st, ok = 1;
			for (i = 0; i < n && ok; i++)
				for (j = 1; j < n && ok; j++) {
					if (nst.p[i][j] <= 0) continue;
					for (k = j; k > 0; k--) {
						if (wall[i][k][i][k - 1] || nst.p[i][k - 1] > 0) break;
						if (nst.p[i][k - 1] == 0) swap(nst.p[i][k], nst.p[i][k - 1]);
						else {
							if (nst.p[i][k] == -nst.p[i][k - 1]) nst.p[i][k] = nst.p[i][k - 1] = 0;
							else ok = 0;
							break;
						}
					}
				}
			if (ok && S.find(nst) == S.end()) {
				Q[qe++] = nst;
				S.insert(nst);
				next++;
			}
 
			// Lift north
			nst = st, ok = 1;
			for (i = n - 2; i >= 0 && ok; i--)
				for (j = 0; j < n && ok; j++) {
					if (nst.p[i][j] <= 0) continue;
					for (k = i; k < n - 1; k++) {
						if (wall[k][j][k + 1][j] || nst.p[k + 1][j] > 0) break;
						if (nst.p[k + 1][j] == 0) swap(nst.p[k][j], nst.p[k + 1][j]);
						else {
							if (nst.p[k][j] == -nst.p[k + 1][j]) nst.p[k][j] = nst.p[k + 1][j] = 0;
							else ok = 0;
							break;
						}
					}
				}
			if (ok && S.find(nst) == S.end()) {
				Q[qe++] = nst;
				S.insert(nst);
				next++;
			}
 
			// Lift south
			nst = st, ok = 1;
			for (i = 1; i < n && ok; i++)
				for (j = 0; j < n && ok; j++) {
					if (nst.p[i][j] <= 0) continue;
					for (k = i; k > 0; k--) {
						if (wall[k][j][k - 1][j] || nst.p[k - 1][j] > 0) break;
						if (nst.p[k - 1][j] == 0) swap(nst.p[k][j], nst.p[k - 1][j]);
						else {
							if (nst.p[k][j] == -nst.p[k - 1][j]) nst.p[k][j] = nst.p[k - 1][j] = 0;
							else ok = 0;
							break;
						}
					}
				}
			if (ok && S.find(nst) == S.end()) {
				Q[qe++] = nst;
				S.insert(nst);
				next++;
			}
		}
		inq = next, step++;
	}
	printf("impossible\n");
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d", &n, &m, &w) && n) {
		printf("Case %d: ", ca++);
		solve();
		printf("\n");
	}
	return 0;
}
