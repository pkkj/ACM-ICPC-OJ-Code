// 2008 Nordic: Aspen Avenue
// UVA 11555
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define N 2005
 
double pos[N];
double dp[N][N];
double sqr(double x) {
	return x * x;
}
double dis(double x1, double y1, double x2, double y2) {
	return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
}
int main() {
	int n, i, j;
	double w, l;
	while (scanf("%d%lf%lf", &n, &l, &w) != EOF) {
		double dy = l / (n / 2 - 1);
		for (i = 1; i <= n; i++)
			scanf("%lf", &pos[i]);
		sort(pos + 1, pos + 1 + n);
		dp[0][0] = 0;
		for (i = 1; i <= n / 2; i++) {
			double x1, y1, x2, y2;
			x1 = 0, y1 = pos[i];
			x2 = w, y2 = dy * (i - 1);
			dp[i][0] = dp[i - 1][0] + dis(x1, y1, x2, y2);
			x2 = 0, y2 = dy * (i - 1);
			dp[i][i] = dp[i - 1][i - 1] + dis(x1, y1, x2, y2);
		}
		for (i = 2; i <= n; i++) {
			for (j = 1; j < min(i, n / 2 + 1); j++) {
				double a1, a2, x1, y1, x2, y2;
				x1 = 0, y1 = pos[i];
				x2 = w, y2 = dy * (i - j - 1);
				a1 = dp[i - 1][j] + dis(x1, y1, x2, y2);
				x2 = 0, y2 = dy * (j - 1);
				a2 = dp[i - 1][j - 1] + dis(x1, y1, x2, y2);
				dp[i][j] = min(a1, a2);
			}
		}
		printf("%.8lf\n", dp[n][n / 2]);
	}
	return 0;
}