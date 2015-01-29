// CII 4298
// 2008 Southwestern Europe: Postal Charges
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 13
int T;
struct POINT {
	double x, y, d1;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
vector<POINT> G[N][N];
int cnt1[N][N], cnt2[N][N];
double dis(POINT &a, POINT &b) {
	return fabs(a.x - b.x) + fabs(a.y - b.y);
}
 
double ndis(POINT &zh, POINT &b) {
	return zh.x - b.x + zh.y - b.y;
}
void solve() {
	int i, j, a, b, n, m, i2, j2, k;
	double npath = 0.0, sumdis = 0.0;
	n = m = 0;
	POINT pt;
	memset(G, 0, sizeof(G));
	memset(cnt1, 0, sizeof(cnt1));
	memset(cnt2, 0, sizeof(cnt2));
 
	for (i = 0; i < T; i++) {
		pt.get();
		pt.x += 1.0, pt.y += 1.0;
		a = (int) (pt.x), b = (int) (pt.y);
		n = max(a, n);
		m = max(b, m);
		G[a][b].push_back(pt);
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			cnt1[i][j] = cnt1[i][j - 1] + cnt1[i - 1][j] - cnt1[i - 1][j - 1] + G[i][j].size();
 
	for (i = n; i > 0; i--)
		for (j = m; j > 0; j--)
			cnt2[i][j] = cnt2[i + 1][j] + cnt2[i][j + 1] - cnt2[i + 1][j + 1] + G[i][j].size();
 
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++)
			for (k = 0; k < G[i][j].size(); k++)
				G[i][j][k].d1 = ndis(G[i][j][0], G[i][j][k]);
	}
 
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			for (i2 = i + 1; i2 <= n; i2++)
				for (j2 = j + 1; j2 <= m; j2++) {
					if (G[i][j].size() == 0 || G[i2][j2].size() == 0) continue;
					sumdis += dis(G[i][j][0], G[i2][j2][0]) * G[i][j].size() * G[i2][j2].size();
					npath += G[i][j].size() * G[i2][j2].size();
				}
 
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			for (k = 1; k < G[i][j].size(); k++) {
				sumdis += cnt2[i + 1][j + 1] * G[i][j][k].d1;
				sumdis -= cnt1[i - 1][j - 1] * G[i][j][k].d1;
			}
	printf("%.8lf\n", sumdis / npath);
}
int main() {
	while (scanf("%d", &T) != EOF)
		solve();
	return 0;
}
