// HDU 2289
// The 4th Baidu Cup Final: Cup
#include <cstdio>
#include <cmath>
double R, r, H, v1, th;
#define PI 3.14159265358979323846
double getv(double h) {
	double rr;
	double ans;
	rr = (th + h) * r / th;
	ans = PI * rr * rr * (h + th) / 3.0 - v1;
	return ans;
}
 
void solve() {
	double left, right, mid, V, ans;
	scanf("%lf%lf%lf%lf", &r, &R, &H, &V);
	if (r == R) {
		ans = V / (r * r * PI);
		if(ans > H)
			ans = H;
		printf("%.6lf\n", ans);
		return;
	}
	left = 0, right = H;
	th = r * H / (R - r);
	v1 = PI * r * r * th / 3.0;
	while (right - left > 1e-8) {
		mid = (left + right) / 2.0;
		double co = getv(mid);
		if(fabs(co - V) < 1e-7)
		{
			printf("%.6lf\n", mid);
			return;
		}
		if (co > V) right = mid;
		else left = mid;
	}
	printf("%.6lf\n", right);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
