// 1998 Northeastern Europe: Gangsters
// ACM-ICPC Live Archive 5665

#include <cstdio>
#include <cmath>
#include <cstdlib>

#define N 105
struct GANE {
	int t, p, s;
};

int cmp(const void* a, const void* b) {
	return ((GANE*) a)->t - ((GANE*) b)->t;
}

void solve() {
	int n, t, k, i, j, g[N], ans = 0;
	GANE list[N];
	scanf("%d%d%d", &n, &k, &t);
	for (i = 0; i < n; i++)
		scanf("%d", &list[i].t);
	for (i = 0; i < n; i++)
		scanf("%d", &list[i].p);
	for (i = 0; i < n; i++)
		scanf("%d", &list[i].s);
	qsort(list, n, sizeof(list[0]), cmp);

	for (i = 0; i < n; i++) {
		g[i] = -1;
		if (list[i].t >= list[i].s)
			g[i] = 0;
		for (j = 0; j < i; j++)
			if (abs(list[i].s - list[j].s) <= (list[i].t - list[j].t) && g[i] < g[j])
				g[i] = g[j];
		if (g[i] >= 0)
			g[i] += list[i].p;
	}
	for (i = 0; i < n; i++)
		if (g[i] > ans)
			ans = g[i];
	printf("%d\n", ans);
}

int main(){
	int T;
	scanf("%d", &T);
	for(int ca = 0; ca < T;ca++){
		if(ca) printf("\n");
		solve();
	}
}
