// 1998 Northeastern Europe: Fence
// ACM-ICPC Live Archive 5660

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = 3.141592653589793238462643383;
const int N = 100 + 5;

struct POINT {
	double x, y;
};
POINT poly[N];

double getAngle(int i1, int i2) {
	double a = atan2(poly[i1].x, poly[i1].y) - atan2(poly[i2].x, poly[i2].y);
	if (a > PI) a -= 2 * PI;
	if (a < -PI) a += 2 * PI;
	return a;
}

void solve() {
	double k, h;
	int n;
	scanf("%lf%lf%d", &k, &h, &n);

	for (int i = 0; i < n; i++)
		scanf("%lf%lf", &poly[i].x, &poly[i].y);
	poly[n] = poly[0];

	double sum = 0, mina = 0, maxa = 0;
	for (int i = 0; i < n; i++){
		sum += getAngle(i, i + 1);
		mina = min(sum, mina);
		maxa = max(sum, maxa);
	}

	printf("%.2lf\n", k * h *  min(2 * PI, maxa - mina));
}

int main(){
	int T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca) printf("\n");
		solve();
	}
	return 0;
}
