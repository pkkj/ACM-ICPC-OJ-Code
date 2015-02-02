// 2008 Beijing: Timer
// ACM-ICPC Live Archive 4330
#include <cstdio>
#include <cmath>
#define PI 3.141592653589793
double H, R, V;
double v(double h) {
	double k = R - h;
	double ans =  H * R * R * acos(k / R) - 2  * k * H * sqrt(R * R - k * k) + k * k * k * H  * log((R + sqrt(R * R - k * k)) / k)/ R;
	return ans / 3.0;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		double l, r, mid;
		scanf("%lf%lf%lf", &H, &R, &V);
		R /= 2.0;
		l = 0, r = R;
		while (r - l >= 1e-6) {
			mid = (l + r) / 2.0;
			if (v(mid) > V) r = mid;
			else l = mid;
		}
		printf("%.5lf\n", 2 * R - (l + r)/2.0);
	}
}
