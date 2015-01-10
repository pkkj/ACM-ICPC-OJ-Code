// POJ 3724
// POJ Monthly Contest – 2009.04.05: Find the parameter
#include <cstdio>
#include <cmath>
#define X 0
#define Y 1
#define M 10
double pl[22][2], best;
int n, ans[12], tmp[12];
 
double f(double x) {
	double ans = 0;
	for (int i = 0; i < M; i++)
		ans += exp(tmp[i] * x);
	return ans;
 
}
void dfs(int x) {
	int low, i;
	if (x == M) {
		double tr = 0;
		for (i = 0; i < n && tr < best; i+=10)
			tr += fabs(f(pl[i][X]) - pl[i][Y]);
		if (tr < best) {
			best = tr;
			for (i = 0; i < M; i++)
				ans[i] = tmp[i];
		}
		return;
	}
	if (x == 0) low = 1;
	else low = tmp[x - 1];
	for (i = low; i <= M; i++) {
		tmp[x] = i;
		dfs(x + 1);
	}
 
}
int main() {
	//freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &pl[i][X], &pl[i][Y]);
	best = 1000000000000.0;
	dfs(0);
	for (int i = 0; i < M; i++)
		printf("%d\n", ans[i]);
	return 0;
}
