// POJ 3301
// Waterloo Local Contest, 2007.7.14: Texas Trip
#define N 31
#define M 300
#define PI 3.14159265358979323846
struct POINT {
	double x, y;
};
int n;
POINT pl[N];
 
double rotate(double x) {
	int i;
	double cosv = cos(x);
	double sinv = sin(x);
	double npx, npy;
	double ans, maxy = -1000000, miny = 1000000, maxx = -1000000, minx = 10000000;
	for (i = 0; i < n; i++) {
		double px, py;
		px = pl[i].x, py = pl[i].y;
		npx = px * cosv - py * sinv;
		npy = px * sinv + py * cosv;
		maxy = max(maxy, npy);
		miny = min(miny, npy);
		maxx = max(maxx, npx);
		minx = min(minx, npx);
	}
	ans = max((maxy - miny), (maxx - minx));
	return ans * ans;
}
void read() {
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%lf%lf", &pl[i].x, &pl[i].y);
}
void solve() {
	double ans = 10000000, ta, base = 0, scale = 1;
	int besti = 0, i, rot;
	read();
	for (rot = 0; rot < 10; rot++) {
		besti = 0;
		for (i = 0; i < M; i++) {
			double step = base + scale * i * PI / 2 / M;//只需要转90度就可以判断
			ta = rotate(step);
			if (ta < ans) {
				ans = ta, besti = i;
			}
		}
		base += scale * (besti - 1) * PI / 2 / M;
		scale = scale / M * 2;
	}
	printf("%.2lf\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
