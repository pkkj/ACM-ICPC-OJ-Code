// 2007 Tokyo: Geometric Map
// ACM-ICPC Live Archive 3886
// POJ 3521
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
#define N 205
#define INF 1e20
struct POINT {
	int x, y;
	void get() {
		scanf("%d%d", &x, &y);
	}
	void print() {
		printf("%d %d\n", x, y);
	}
	POINT() {
	}
	POINT(int x, int y) :
		x(x), y(y) {
	}
	bool operator <(const POINT &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	bool operator ==(const POINT &p) const {
		return p.x == x && p.y == y;
	}
};
struct FPOINT {
	double x, y;
	FPOINT() {
	}
	FPOINT(double x, double y) :
		x(x), y(y) {
	}
	FPOINT(POINT p) {
		x = (double) p.x;
		y = (double) p.y;
	}
	FPOINT operator +(const FPOINT & b) {
		return FPOINT(x + b.x, y + b.y);
	}
	FPOINT operator /(const double & v) {
		return FPOINT(x / v, y / v);
	}
	FPOINT operator *(const double & v) {
		return FPOINT(x * v, y * v);
	}
	bool operator ==(const POINT &p) const {
		return p.x == x && p.y == y;
	}
};
struct LINE {
	POINT a, b;
	bool sign;
	void get() {
		sign = 0;
		a.get();
		b.get();
	}
};
inline int cross(POINT &p, POINT &p1, POINT &p2) {
	return (p1.x - p.x) * (p2.y - p.y) - (p2.x - p.x) * (p1.y - p.y);
}
inline int dotdet(POINT &p, POINT &p1, POINT &p2) {
	return (p1.x - p.x) * (p2.x - p.x) + (p1.y - p.y) * (p2.y - p.y);
}
 
////////////////////////////
int line_inter(POINT &a, POINT &b, POINT &c, POINT &d, FPOINT &cp) {
	if (a == c || a == d) {
		cp = a;
		return 1;
	}
	if (b == c || b == d) {
		cp = b;
		return 1;
	}
	double u = cross(a, b, c), v = cross(b, a, d);
	FPOINT fc = FPOINT(c), fd = FPOINT(d);
	if (u + v) {
		cp = (fc * v + fd * u) / (double) (u + v);
		return 1;
	}
	return -1;
}
bool seg_intersect(POINT &a, POINT &b, POINT &c, POINT &d, FPOINT &pt) {
	int ret = line_inter(a, b, c, d, pt);
	if (ret == -1) return 0;
	if (pt.x < min(a.x, b.x) || pt.x > max(a.x, b.x)) return 0;
	if (pt.y < min(a.y, b.y) || pt.y > max(a.y, b.y)) return 0;
	if (pt.x < min(c.x, d.x) || pt.x > max(c.x, d.x)) return 0;
	if (pt.y < min(c.y, d.y) || pt.y > max(c.y, d.y)) return 0;
	return 1;
}
bool seg_intersect(LINE &u, LINE &v, FPOINT &pt) {
	return seg_intersect(u.a, u.b, v.a, v.b, pt);
}
double dis(POINT &a, POINT &b) {
	return sqrt((double) (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int in_line(POINT &a, POINT &b, POINT &p) {
	if (cross(p, a, b)) return 0;
	if (p.x < min(a.x, b.x) || p.x > max(a.x, b.x)) return 0;
	if (p.y < min(a.y, b.y) || p.y > max(a.y, b.y)) return 0;
	return 1;
}
int n, tot, s, t;
LINE ll[N];
set<POINT> S;
POINT pl[N * N];
double G[N + N][N + N];
void build() {
	POINT begin, end;
	int i, j, k;
	begin.get();
	end.get();
	for (i = 0; i < n; i++)
		ll[i].get();
	for (i = 0; i < n; i++) {
		int ta = 0, tb = 0;
		for (j = 0; j < n; j++) {
			if (i == j) continue;
			if (in_line(ll[j].a, ll[j].b, ll[i].a)) ta = 1;
			if (in_line(ll[j].a, ll[j].b, ll[i].b)) tb = 1;
		}
		if (!(ta && tb)) ll[i].sign = 1;
	}
	S.clear();
	S.insert(begin);
	S.insert(end);
	for (i = 0; i < n; i++) {
		if (ll[i].sign) continue;
		for (j = i + 1; j < n; j++) {
			if (ll[j].sign) continue;
			FPOINT pt;
			if (seg_intersect(ll[i], ll[j], pt)) {
				POINT pp = POINT((int) pt.x, (int) pt.y);
				if (S.find(pp) == S.end()) S.insert(pp);
			}
		}
	}
	tot = 0;
	for (set<POINT>::iterator it = S.begin(); it != S.end(); it++) {
		pl[tot] = *it;
		if (pl[tot] == begin) s = tot;
		if (pl[tot] == end) t = tot;
		tot++;
	}
	for (i = 0; i <= tot; i++) {
		for (j = 0; j <= tot; j++)
			G[i][j] = INF;
		G[i][i] = 0;
	}
	for (i = 0; i < tot; i++) {
		for (j = i + 1; j < tot; j++) {
			int ok = 0, ss = 1;
			for (k = 0; k < tot && ss; k++)
				if (i != k && j != k && in_line(pl[i], pl[j], pl[k])) ss = 0;
			if (!ss) continue;
 
			for (k = 0; k < n && !ok; k++) {
				if (ll[k].sign) continue;
				if (in_line(ll[k].a, ll[k].b, pl[i]) && in_line(ll[k].a, ll[k].b, pl[j])) ok = 1;
			}
			if (ok) {
				int al, dir = -2, ndir;
				for (k = 0; k < n; k++) {
					if (!ll[k].sign) continue;
					if (in_line(pl[i], pl[j], ll[k].a))
						al = dotdet(ll[k].a, ll[k].b, pl[i]);
					else if (in_line(pl[i], pl[j], ll[k].b))
						al = dotdet(ll[k].b, ll[k].a, pl[i]);
					else continue;
					if (al > 0) ndir = 1;
					else if (al == 0) ndir = 0;
					else if (al < 0) ndir = -1;
					if (dir == -2) dir = ndir;
					else {
						if (ndir != dir) {
							dir = 0;
							break;
						}
					}
				}
				if (dir == 1) G[i][j] = dis(pl[i], pl[j]);
				else if (dir == -1) G[j][i] = dis(pl[i], pl[j]);
				else if (dir == -2) G[i][j] = G[j][i] = dis(pl[i], pl[j]);
			}
		}
	}
}
 
// Shortest path
double dist[N + N];
int pre[N + N];
bool vis[N + N];
void dij() {
	int i, w, v;
	memset(vis, 0, sizeof(vis));
	for (i = 0; i < tot; i++) {
		dist[i] = G[s][i];
		pre[i] = s;
	}
	dist[s] = 0, vis[s] = 1;
	for (i = 0; i < tot; i++) {
		double mmin = INF;
		for (w = 0; w < tot; w++)
			if (!vis[w]) if (dist[w] < mmin) v = w, mmin = dist[w];
		if (mmin == INF) break;
		vis[v] = 1;
		for (w = 0; w < tot; w++)
			if (!vis[w] && mmin + G[v][w] < dist[w]) {
				dist[w] = mmin + G[v][w];
				pre[w] = v;
			}
	}
}
POINT ans[N + N];
void solve() {
	int j = 0;
	build();
	dij();
	if (!vis[t]) {
		printf("-1\n");
		return;
	}
	int i = t;
	while (i != s) {
		ans[j++] = pl[i];
		i = pre[i];
	}
	ans[j++] = pl[i];
	for (i = j - 1; i >= 0; i--)
		ans[i].print();
	printf("0\n");
 
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}