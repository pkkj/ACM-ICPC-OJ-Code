// CII 3404
// 2005 Tokyo: Atomic Car Race
#include <cstdio>
#include <cstring>
using namespace std;
#define N 10005
double v, e, f, b;
int dis[N];
double opt[N],need_time[N];
int r, n;
void calc_time() {
	int i;
	double t;
	need_time[0] = 0;
	for (i = 0; i <= dis[n]+1; i++) {
		if (i >= r)
			t = 1.0 / (v - e * (i - r));
		else
			t= 1.0 / (v - f * (r - i));
		need_time[i+1] = need_time[i] + t;
	}
}

int main() {
	int i, j;
	while (scanf("%d", &n) && n) {
		double min, tmp;
		dis[0] = 0;
		for (i = 1; i <= n; i++)
			scanf("%d", &dis[i]);
		scanf("%lf", &b);
		scanf("%d%lf%lf%lf", &r, &v, &e, &f);
		calc_time();
		opt[0] = 0.0;
		for (i = 1; i <= n; i++) {
			min = 99999999;
			for (j = 0; j < i; j++) {
				if ((tmp = opt[j] + need_time[dis[i] - dis[j]]) < min)
					min = tmp;
			}
			opt[i] = min + b;
		}
		printf("%.4lf\n", opt[n] - b);
	}
	return 0;
}

