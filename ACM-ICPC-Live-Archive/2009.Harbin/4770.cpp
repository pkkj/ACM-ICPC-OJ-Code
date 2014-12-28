// CII 4770
// 2009 Harbin: Offset Recovery
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 3000
#define INF 1e60
int n, m;
double sn[N], sm[N];
struct EVENT {
	double x;
	int id;
	bool operator<(const EVENT &e) const {
		return x < e.x;
	}
	EVENT() {
	}
	EVENT(double x, int id) :
		x(x), id(id) {
	}
};
EVENT E[N * 500];
int pos[N];
double update(double A, double B, double C, double xl, double xr, double &xb) {
	xb = -B / (2.0 * A);
	if (xb > xr) xb = xr;
	if (xb < xl) xb = xl;
	return A * xb * xb + B * xb + C;
}
double solve() {
	int i, j, ne = 0;
	double A, B, C, best, ans, tmp, x;
	for (i = 0; i < n; i++)
		scanf("%lf", &sn[i]);
	for (i = 0; i < m; i++)
		scanf("%lf", &sm[i]);
	for (i = 0; i < n; i++)
		for (j = 1; j < m; j++) {
			double mid = (sm[j] + sm[j - 1]) / 2.0;
			E[ne++] = EVENT(mid - sn[i], i);
		}
	sort(E, E + ne);
	memset(pos, 0, sizeof(pos));
	A = B = C = 0;
	for (i = 0; i < n; i++) {
		A += 1.0;
		B += 2 * (sn[i] - sm[0]);
		C += (sn[i] - sm[0]) * (sn[i] - sm[0]);
	}
	double pre = -INF;
	best = INF;
	for (i = 0; i < ne; i++) {
		tmp = update(A, B, C, pre, E[i].x, x);
		if (tmp < best) best = tmp, ans = x;
		pre = E[i].x;
		pos[E[i].id]++;
		B -= 2 * (sn[E[i].id] - sm[pos[E[i].id] - 1]);
		B += 2 * (sn[E[i].id] - sm[pos[E[i].id]]);
		C -= (sn[E[i].id] - sm[pos[E[i].id] - 1]) * (sn[E[i].id] - sm[pos[E[i].id] - 1]);
		C += (sn[E[i].id] - sm[pos[E[i].id]]) * (sn[E[i].id] - sm[pos[E[i].id]]);
	}
	tmp = update(A, B, C, pre, INF, x);
	if (tmp < best) best = tmp, ans = x;
	return ans;
}
int main() {
	while (~scanf("%d%d", &n, &m))
		printf("%.3lf\n", solve());
	return 0;
}
