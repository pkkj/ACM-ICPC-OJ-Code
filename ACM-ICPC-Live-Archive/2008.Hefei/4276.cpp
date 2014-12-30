// CII 4276
// 2008 Hefei: Triangles
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 105
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
 
struct BITSET {
	long long s[2];
	BITSET() {
		s[0] = s[1] = 0;
	}
	void setbit(int x) {
		int i, j;
		i = x >> 6, j = x & 63;
		s[i] |= (1LL << j);
	}
	int countone() {
		int ans = 0;
		for (int i = 0; i < 2; i++) {
			long long k = s[i];
			while (k)
				k &= k - 1, ++ans;
		}
		return ans;
	}
	BITSET operator &(const BITSET &b) {
		BITSET ans;
		ans.s[0] = s[0] & b.s[0];
		ans.s[1] = s[1] & b.s[1];
		return ans;
	}
};
 
int cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
POINT pr[N], pg[N], pb[N];
BITSET S[N][N][2];
int R, B, G;
void solve() {
	int i, j, k, ansg = 0, ansr = 0;
	for (i = 0; i < R; i++)
		pr[i].get();
	for (i = 0; i < G; i++)
		pg[i].get();
	for (i = 0; i < B; i++)
		pb[i].get();
 
	memset(S, 0, sizeof(S));
	for (i = 0; i < B; i++)
		for (j = i + 1; j < B; j++) {
			for (k = 0; k < R; k++) {
				if (cross(pb[i], pb[j], pr[k]) < 0) S[i][j][0].setbit(k);
				else S[j][i][0].setbit(k);
			}
			for (k = 0; k < G; k++) {
				if (cross(pb[i], pb[j], pg[k]) < 0) S[i][j][1].setbit(k);
				else S[j][i][1].setbit(k);
			}
		}
	for (i = 0; i < B; i++)
		for (j = i + 1; j < B; j++)
			for (k = j + 1; k < B; k++) {
				BITSET gs, rs;
				if (cross(pb[i], pb[j], pb[k]) < 0) {
					rs = S[i][j][0] & S[j][k][0] & S[k][i][0];
					gs = S[i][j][1] & S[j][k][1] & S[k][i][1];
				} else {
					rs = S[k][j][0] & S[j][i][0] & S[i][k][0];
					gs = S[k][j][1] & S[j][i][1] & S[i][k][1];
				}
				int cg = gs.countone(), cr = rs.countone();
				if (cg > cr) ansg++;
				if (cr > cg) ansr++;
 
			}
	printf("%d %d\n", ansr, ansg);
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d", &R, &G, &B) && R != -1) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
