// CII 3531
// 2005 Central Europe: Word Rings
#include <cstdio>
#include <cstring>
 
#define INF 1e20
#define N 100001
#define M 27
struct EDGE {
	int a, b;
	double w;
	EDGE() {
	}
	EDGE(int a, int b, double w) :
		a(a), b(b), w(w) {
	}
};
EDGE el[N];
 
int ee[M][M], n, tot;
char s[1005];
double dis[M*M];
int check(double kk) {
	int i, j, f;
	for (i = 1; i < tot; i++)
		dis[i] = 0;
	for (i = 0; i < tot; i++) {
		f = 0;
		for (j = 0; j < n; j++) {
			if (dis[el[j].a] + kk - el[j].w < dis[el[j].b]) {
				dis[el[j].b] = dis[el[j].a] + kk - el[j].w;
				f = 1;
			}
		}
		if (!f) break;
	}
	return f;
}
void solve() {
	int i, x, y, u, v, len;
	double l = INF, r = -INF;
	memset(ee, 0, sizeof(ee));
	tot = 1;
	for (i = 0; i < n; i++) {
		gets(s);
		len = strlen(s);
		x = s[0] - 'a', y = s[1] - 'a';
		if (!ee[x][y]) ee[x][y] = tot++;
		u = ee[x][y];
 
		x = s[len - 2] - 'a', y = s[len - 1] - 'a';
		if (!ee[x][y]) ee[x][y] = tot++;
		v = ee[x][y];
 
		el[i] = EDGE(u, v, (double) len);
		l = l < el[i].w ? l : el[i].w;
		r = r > el[i].w ? r : el[i].w;
	}
	if (!check(0)) {
		printf("No solution.\n");
		return;
	}
	while (r - l > 1e-3) {
		double mid = (l + r) / 2.0;
		if (check(mid)) l = mid;
		else r = mid;
	}
	printf("%.3lf\n", l);
}
int main() {
	while (scanf("%d\n", &n) && n)
		solve();
	return 0;
}
