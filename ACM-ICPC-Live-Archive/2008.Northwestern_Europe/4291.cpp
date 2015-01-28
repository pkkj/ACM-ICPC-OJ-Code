// 2008 Northwestern Europe: Sculpture
// ACM-ICPC Live Archive 4291
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 110
const int N2 = N*N;
struct BLOCK {
	int x1, y1, z1, x2, y2, z2;
	BLOCK() {
	}
	BLOCK(int x1, int y1, int z1, int x2, int y2, int z2) :
		x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2) {
	}
};
BLOCK bl[N];
int xx[N], yy[N], zz[N];
int opp[N][N][N];
int Q[N * N * N];
int dx[] = { 1, -1, 0, 0, 0, 0 };
int dy[] = { 0, 0, 1, -1, 0, 0 };
int dz[] = { 0, 0, 0, 0, 1, -1 };
void solve() {
	int n, i, a, b, c, xtot, ytot, ztot, j, k, d;
	long long vol, area;
	scanf("%d", &n);
	xtot = ytot = ztot = 0;
	for (i = 0; i < n; i++) {
		scanf("%d%d%d", &bl[i].x1, &bl[i].y1, &bl[i].z1);
		scanf("%d%d%d", &a, &b, &c);
		bl[i].x2 = bl[i].x1 + a, bl[i].y2 = bl[i].y1 + b, bl[i].z2 = bl[i].z1 + c;
		xx[xtot++] = bl[i].x1, xx[xtot++] = bl[i].x2;
		yy[ytot++] = bl[i].y1, yy[ytot++] = bl[i].y2;
		zz[ztot++] = bl[i].z1, zz[ztot++] = bl[i].z2;
	}
	xx[xtot++] = -1;
	yy[ytot++] = -1;
	zz[ztot++] = -1;
	sort(xx, xx + xtot);
	sort(yy, yy + ytot);
	sort(zz, zz + ztot);
	xtot = unique(xx, xx + xtot) - xx;
	ytot = unique(yy, yy + ytot) - yy;
	ztot = unique(zz, zz + ztot) - zz;
	for (i = 0; i < n; i++) {
		bl[i].x1 = lower_bound(xx, xx + xtot, bl[i].x1) - xx;
		bl[i].x2 = lower_bound(xx, xx + xtot, bl[i].x2) - xx;
		bl[i].y1 = lower_bound(yy, yy + ytot, bl[i].y1) - yy;
		bl[i].y2 = lower_bound(yy, yy + ytot, bl[i].y2) - yy;
		bl[i].z1 = lower_bound(zz, zz + ztot, bl[i].z1) - zz;
		bl[i].z2 = lower_bound(zz, zz + ztot, bl[i].z2) - zz;
	}
	memset(opp, 0, sizeof(opp));
	for (i = 0; i < n; i++) {
		for (a = bl[i].x1; a < bl[i].x2; a++)
			for (b = bl[i].y1; b < bl[i].y2; b++)
				for (c = bl[i].z1; c < bl[i].z2; c++)
					opp[a][b][c] = 1;
	}
	int qh, qe;
	qh = qe = 0;
	Q[qe++] = 0;
	opp[0][0][0] = -1;
	while (qh < qe) {
		int top = Q[qh++];
		int cx = top / N2, cy = (top / N) % N, cz = top % N;
		for (i = 0; i < 6; i++) {
			int nx = cx + dx[i], ny = cy + dy[i], nz = cz + dz[i];
			if (nx < 0 || ny < 0 || nz < 0 || nx == xtot || ny == ytot || nz == ztot) continue;
			if (!opp[nx][ny][nz]) {
				opp[nx][ny][nz] = -1;
				Q[qe++] = nx * N2 + ny * N + nz;
			}
		}
	}
	vol = area = 0;
	for (i = 1; i < xtot - 1; i++)
		for (j = 1; j < ytot - 1; j++)
			for (k = 1; k < ztot - 1; k++) {
				if (opp[i][j][k] != -1) {
					a = xx[i + 1] - xx[i];
					b = yy[j + 1] - yy[j];
					c = zz[k + 1] - zz[k];
					vol += (long long)a * b * c;
					if (opp[i][j][k]) {
						for (d = 0; d < 6; d++) {
							if (opp[i + dx[d]][j + dy[d]][k + dz[d]] == -1) {
								if (dx[d]) area += b * c;
								else if (dy[d]) area += a * c;
								else if (dz[d]) area += a * b;
							}
						}
					}
				}
			}
	printf("%lld %lld\n", area, vol);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
}