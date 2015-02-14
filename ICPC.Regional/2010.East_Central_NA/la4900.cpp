// CII 4900
// 2010 East Central NA: Cut It Out!

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
#define N 45
#define EPS 1e-2
bool eq(double a, double b) {
	return a - b > 0 ? a - b < EPS : b - a < EPS;
}
double dis(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
 
struct PAIR {
	int a, b;
	PAIR() {
	}
	PAIR(int A, int B) :
		a(A), b(B) {
	}
};
struct TRI {
	double edge[3], cosang[3];
	TRI() {
	}
	TRI(double e0, double e1, double e2) {
		edge[0] = e0, edge[1] = e1, edge[2] = e2;
	}
	void read() {
		double x1, y1, x2, y2, x3, y3;
		scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
 
		edge[0] = dis(x1, y1, x2, y2);
		edge[1] = dis(x2, y2, x3, y3);
		edge[2] = dis(x3, y3, x1, y1);
 
		for (int i = 0; i < 3; i++) {
			double a = edge[(i + 1) % 3], b = edge[(i + 2) % 3], c = edge[i];
			cosang[i] = (a * a + b * b - c * c) / 2.0 / a / b;
		}
	}
};
 
bool tri_eq(TRI &a, TRI &b) {
	if (eq(a.edge[0], b.edge[0])) {
		if (eq(a.edge[1], b.edge[1]) && eq(a.edge[2], b.edge[2])) return true;
		if (eq(a.edge[1], b.edge[2]) && eq(a.edge[2], b.edge[1])) return true;
	}
	if (eq(a.edge[0], b.edge[1])) {
		if (eq(a.edge[1], b.edge[0]) && eq(a.edge[2], b.edge[2])) return true;
		if (eq(a.edge[1], b.edge[2]) && eq(a.edge[2], b.edge[0])) return true;
	}
	if (eq(a.edge[0], b.edge[2])) {
		if (eq(a.edge[1], b.edge[0]) && eq(a.edge[2], b.edge[1])) return true;
		if (eq(a.edge[1], b.edge[1]) && eq(a.edge[2], b.edge[0])) return true;
	}
	return false;
}
 
int n, idx[N];
TRI hole[N], tri[N];
vector<PAIR> pa[N];
int ans[N][2];
bool use[N];
bool cmp(int a, int b){
	return pa[a].size() < pa[b].size();
}
 
bool dfs(int d) {
	if (d == n) {
		for (int i = 0; i < n; i++)
			printf("Hole %d: %d, %d\n", i + 1, ans[i][0] + 1, ans[i][1] + 1);
		return true;
	}
	int dep = idx[d];
	for (int i = 0; i < (int) pa[dep].size(); i++) {
		if (use[pa[dep][i].a] || use[pa[dep][i].b]) continue;
		use[pa[dep][i].a] = use[pa[dep][i].b] = true;
		ans[dep][0] = pa[dep][i].a, ans[dep][1] = pa[dep][i].b;
		if (dfs(d + 1)) return true;
		use[pa[dep][i].a] = use[pa[dep][i].b] = false;
	}
	return false;
}
 
void solve() {
 
	int i, j, k, u, v;
	for (i = 0; i < n; i++) {
		hole[i].read();
		idx[i] = i;
		pa[i].clear();
	}
	for (i = 0; i < n * 2; i++)
		tri[i].read();
 
	for (i = 0; i < n; i++) { // the hole
		for (j = 0; j < n * 2; j++) { // the triangles
			for (k = j + 1; k < 2 * n; k++) { // another triangle
				for (u = 0; u < 3; u++) { // the angle in hole
					for (v = 0; v < 3; v++) { // the angel in triangle
						if (!eq(hole[i].cosang[u], tri[j].cosang[v])) continue;
						if (eq(hole[i].edge[(u + 1) % 3], tri[j].edge[(v + 1) % 3])) {
							double e1, e2, e3;
							e1 = hole[i].edge[(u + 2) % 3] - tri[j].edge[(v + 2) % 3];
							e2 = hole[i].edge[u];
							e3 = tri[j].edge[v];
							TRI t = TRI(e1, e2, e3);
							if (tri_eq(t, tri[k])) {
								pa[i].push_back(PAIR(j, k));
								goto FIND;
							}
						}
 
						if (eq(hole[i].edge[(u + 2) % 3], tri[j].edge[(v + 2) % 3])) {
							double e1, e2, e3;
							e1 = hole[i].edge[(u + 1) % 3] - tri[j].edge[(v + 1) % 3];
							e2 = hole[i].edge[u];
							e3 = tri[j].edge[v];
							TRI t = TRI(e1, e2, e3);
							if (tri_eq(t, tri[k])) {
								pa[i].push_back(PAIR(j, k));
								goto FIND;
							}
						}
					}
 
				}
				FIND: ;
			}
		}
	}
	memset(use, 0, sizeof(use));
	sort(idx, idx + n, cmp);
	dfs(0);
 
}
 
int main() {
	int T = 0;
	while (scanf("%d", &n) && n) {
		if(T)
			printf("\n");
		printf("Case %d:\n", ++T);
		solve();
	}
	return 0;
 
}
