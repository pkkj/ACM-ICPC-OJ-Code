// 2007 Dhaka: Magnetic Train Tracks
// ACM-ICPC Live Archive 4064
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define PI 3.141592653589793238
#define N 1300
int n;
struct POINT {
	int x, y;
	void get() {
		scanf("%d%d", &x, &y);
	}
};
POINT pl[N];
int idx[N];
double ang[N];
bool cmp(int x, int y) {
	return ang[x] < ang[y];
}
int next(int x) {
	x++;
	if (x == n) x = 1;
	return x;
}
double getang(int a, int b) {
	double d = ang[a] - ang[b];
	if (d > 2 * PI) d -= 2 * PI;
	if (d <= 0) d += 2 * PI;
	return d;
}
 
int solve() {
	int i, ivot, ans = 0;
	for (i = 0; i < n; i++)
		pl[i].get();
	if (n <= 2) return 0;
	for (ivot = 0; ivot < n; ivot++) {
		swap(pl[ivot], pl[0]);
		for (i = 1; i < n; i++) {
			idx[i] = i;
			ang[i] = atan2((double) (pl[i].y - pl[0].y), (double) (pl[i].x - pl[0].x));
		}
		sort(idx + 1, idx + n, cmp);
		int a = next(1), b = next(1);
		for (i = 1; i < n; i++) {
			if (i == a) a = next(a);
			if (i == b) b = next(b);
			while (getang(idx[a], idx[i]) < PI / 2 - 1e-8)
				a = next(a);
			while (getang(idx[b], idx[i]) < PI)
				b = next(b);
			if (b < a) ans += b + n - a - 1;
			else ans += b - a;
		}
		swap(pl[ivot], pl[0]);
	}
	return n * (n - 1) * (n - 2) / 6 - ans;
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n)
		printf("Scenario %d:\nThere are %d sites for making valid tracks\n", ca++, solve());
	return 0;
}