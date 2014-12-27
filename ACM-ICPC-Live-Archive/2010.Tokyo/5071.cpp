// CII 5071
// 2010 Tokyo: The Two Men of the Japanese Alps
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define N 106
#define INF 1e50
#define EPS 1e-8
struct POINT {
	double x, y;
	int id, nh;
};
double dis(POINT &a, POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int n, pcnt;
POINT pt[N], npt[N * N];
double h[N], gap[N * N];
int match[N][N];
// THE GRAPH
double dist[N][N][N];
bool v[N][N][N];
struct NODE {
	int a, b, h;
	double w;
	NODE() {
	}
	NODE(int a, int b, int h, double w) :
		a(a), b(b), h(h), w(w) {
	}
	bool operator <(const NODE &n) const {
		return w > n.w;
	}
};
// END
POINT intersect(POINT &p1, POINT &p2, double h) {
	POINT ret;
	ret.x = (h - p1.y) / (p2.y - p1.y) * (p2.x - p1.x) + p1.x;
	ret.y = h;
	return ret;
}
void expand(int nl, int nr, double nw, priority_queue<NODE> &Q) {
	int na = npt[nl].id, nb = npt[nr].id, nh = npt[nl].nh;
	if (dist[na][nb][nh] > nw) {
		dist[na][nb][nh] = nw;
		Q.push(NODE(na, nb, nh, nw));
	}
}
void solve() {
	int i, j, k, hcnt;
 
	for (i = 0; i < n; i++) {
		scanf("%lf%lf", &pt[i].x, &pt[i].y);
		h[i] = pt[i].y;
	}
	sort(h, h + n);
	hcnt = unique(h, h + n) - h;
	pcnt = 0;
	for (i = 0; i < n - 1; i++) {
		npt[pcnt] = pt[i];
		npt[pcnt].nh = lower_bound(h, h + hcnt, npt[pcnt].y) - h;
		npt[pcnt++].id = i;
		if (pt[i].y < pt[i + 1].y) {// up
			for (j = 0; j < hcnt; j++) {
				if (pt[i].y < h[j] && h[j] < pt[i + 1].y) {
					npt[pcnt] = intersect(pt[i], pt[i + 1], h[j]);
					npt[pcnt].nh = lower_bound(h, h + hcnt, npt[pcnt].y) - h;
					npt[pcnt++].id = i;
				}
			}
		} else {// down
			for (j = hcnt - 1; j >= 0; j--) {
				if (pt[i + 1].y < h[j] && h[j] < pt[i].y) {
					npt[pcnt] = intersect(pt[i], pt[i + 1], h[j]);
					npt[pcnt].nh = lower_bound(h, h + hcnt, npt[pcnt].y) - h;
					npt[pcnt++].id = i;
				}
			}
		}
	}
	npt[pcnt] = pt[n - 1];
	npt[pcnt].nh = lower_bound(h, h + hcnt, npt[pcnt].y) - h;
	npt[pcnt++].id = n - 1;
 
	for (i = 0; i < pcnt - 1; i++)
		gap[i] = dis(npt[i], npt[i + 1]);
	for (i = 0; i < pcnt; i++)
		match[npt[i].id][npt[i].nh] = i;
 
	priority_queue<NODE> Q;
	memset(v, 0, sizeof(v));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < hcnt; k++)
				dist[i][j][k] = INF;
 
	dist[0][n - 1][0] = 0;
	Q.push(NODE(0, n - 1, 0, 0));
	while (!Q.empty()) {
		NODE top = Q.top();
		Q.pop();
		if (v[top.a][top.b][top.h]) continue;
		v[top.a][top.b][top.h] = true;
		int i = match[top.a][top.h], j = match[top.b][top.h], nl, nr;
		if (i == j) {
			printf("%lf\n", top.w);
			return;
		}
 
		// -> <-
		nl = i + 1, nr = j - 1;
		if (npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[i] + gap[j - 1], Q);
		// -> ->
		nl = i + 1, nr = j + 1;
		if (j < pcnt - 1 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[i] + gap[j], Q);
 
		// <- <-
		nl = i - 1, nr = j - 1;
		if (i > 0 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[i - 1] + gap[j - 1], Q);
 
		// <- ->
		nl = i - 1, nr = j + 1;
		if (i > 0 && j < pcnt - 1 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[i - 1] + gap[j], Q);
 
		// -> S
		nl = i + 1, nr = j;
		if (i < pcnt - 1 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[i], Q);
 
		// <- S
		nl = i - 1, nr = j;
		if (i > 0 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[i - 1], Q);
 
		// S <-
		nl = i, nr = j - 1;
		if (j > 0 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w +  gap[j-1], Q);
 
		// S ->
		nl = i, nr = j + 1;
		if (j < pcnt - 1 && npt[nl].nh == npt[nr].nh)
			expand(nl, nr, top.w + gap[j], Q);
 
	}
 
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
