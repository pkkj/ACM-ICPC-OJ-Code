// 2005 World Finals: Simplified GSM Network
// ACM-ICPC Live Archive 3270

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 55
#define C 300
#define EPS 1e-8
#define PI 3.14159265358979323846
#define INF 100000
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	POINT operator /(const double & v) {
		return POINT(x / v, y / v);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
	bool operator <(const POINT &p) {
		if (sgn(x - p.x)) return x < p.x;
		return y < p.y;
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
 
inline double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int scross(POINT &o, POINT &a, POINT &b) {
	return sgn(cross(o, a, b));
}
POINT rotate(const POINT &p, double a) {
	POINT ret;
	ret.x = p.x * cos(a) - p.y * sin(a);
	ret.y = p.x * sin(a) + p.y * cos(a);
	return ret;
}
 
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &cp) {
	double u = cross(a, b, c), v = cross(b, a, d);
	if (sgn(u + v)) {
		cp = (c * v + d * u) / (u + v);
		return 1;
	}
	return 0;
}
 
int dis[C][C];
int nb, nc, Q, nr;
POINT bts[N], city[N];
bool uniseg(POINT &a, POINT &b, POINT c, POINT d) {
	POINT r1, r2;
	if (d < c) swap(c, d);
	if (c < a) swap(a, c), swap(b, d);
	if (sgn(a.x - b.x)) {
		if (b.x < c.x) return 0;
		if (d.x < b.x) r1 = c, r2 = d;
		else r1 = c, r2 = b;
	} else {
		if (b.y < c.y) return 0;
		if (d.y < b.y) r1 = c, r2 = d;
		else r1 = c, r2 = b;
	}
	a = r1, b = r2;
	return 1;
}
int getdis(int x, int y) {
	int i, j, ans = 0;
	for (i = 1; i <= nb; i++) {
		bool ok = 1;
		POINT s1 = city[x], s2 = city[y], mid;
		if (s2 < s1) swap(s1, s2);
		for (j = 1; j <= nb && ok; j++) {
			if (i == j) continue;
			POINT f, it;
			f = mid = (bts[i] + bts[j]) / 2;
			f = f - bts[i];
			f = rotate(f, PI / 2.0);
			f = f + mid;
			bool ping = line_inter(city[x], city[y], mid, f, it);
			if (!ping) {
				if (scross(mid, f, bts[i]) != scross(mid, f, city[x])) ok = 0;
			} else {
				if (scross(mid, it, city[x]) == scross(mid, it, city[y])) {
					if (scross(mid, it, city[x]) != scross(mid, it, bts[i])) ok = 0;
				} else {
					if (scross(mid, it, city[x]) == scross(mid, it, bts[i])) ok = uniseg(s1, s2, it, city[x]);
					else ok = uniseg(s1, s2, it, city[y]);
				}
			}
		}
		if (ok) ans++;
	}
	return ans - 1;
}
int dist[C];
bool vis[C];
int dij(int x, int y) {
	int i, j;
	for (i = 1; i <= nc; i++)
		dist[i] = dis[x][i];
	memset(vis, 0, sizeof(vis));
	vis[x] = 1;
	for (i = 1; i <= nc; i++) {
		int next = -1, best = INF;
		for (j = 1; j <= nc; j++)
			if (!vis[j] && dist[j] < best) next = j, best = dist[j];
		if (next == -1) break;
		vis[next] = 1;
		for (j = 1; j <= nc; j++) {
			if (vis[j] || dis[next][j] == INF) continue;
			if (dist[next] + dis[next][j] < dist[j]) dist[j] = dist[next] + dis[next][j];
		}
	}
	return dist[y];
}
void solve() {
	int i, j, x, y;
	for (i = 1; i <= nb; i++)
		bts[i].get();
	for (i = 1; i <= nc; i++)
		city[i].get();
	for (i = 1; i <= nc; i++)
		for (j = 1; j <= nc; j++)
			dis[i][j] = INF;
	for (i = 1; i <= nr; i++) {
		scanf("%d%d", &x, &y);
		dis[x][y] = dis[y][x] = getdis(x, y);
	}
	while (Q--) {
		scanf("%d%d", &x, &y);
		int ans = dij(x, y);
		if (ans == INF) printf("Impossible\n");
		else printf("%d\n", ans);
	}
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d%d", &nb, &nc, &nr, &Q) && Q) {
		printf("Case %d:\n", ca++);
		solve();
	}
	return 0;
}