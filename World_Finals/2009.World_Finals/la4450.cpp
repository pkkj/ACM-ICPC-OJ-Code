// 2009 World Finals: Deer-Proof Fence
// ACM-ICPC Live Archive 4450

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 10
#define PI 3.1415926535897932384626433
#define PRECISION  1e-8
 
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
 
POINT pl[N], p[N];
double mar, coans[1<<N];
int n;
double dp[1 << 10];
 
double sqr(double x) {
	return x * x;
}
int cmpzero(double d) {
	return (fabs(d) < PRECISION) ? 0 : (d > 0 ? 1 : -1);
}
 
double dis(const POINT &a, const POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
double cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
bool cmp_angle(const POINT &p1, const POINT &p2) {
	return cross(p[0], p1, p2) > 0;
}
inline bool farer(const POINT &p1, const POINT &p2) {
	return dis(p1, p[0]) > dis(p2, p[0]);
}
int remove_point(int n) {
	int idx = 1;
	for (int i = 2; i < n; ++i) {
		if (cmpzero(cross(p[0], p[i], p[idx]))) p[++idx] = p[i];
		else if (farer(p[i], p[idx])) p[idx] = p[i];
	}
	return idx + 1;
}
 
double calc(int b) {
	double ans = mar * PI * 2;
	int i, n = 0, top;
	POINT ch[N];
	for (i = 0; i < ::n; i++)
		if ((1 << i) & b) p[n++] = ::pl[i];
 
	if (n == 1) return ans;
	if (n == 2) return dis(p[0], p[1]) * 2 + ans;
	for (int i = 1; i < n; i++)
		if (p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x)) swap(p[i], p[0]);
 
	sort(p + 1, p + n, cmp_angle);
	n = remove_point(n);
	if (n == 1) return ans;
	if (n == 2) return dis(p[0], p[1]) * 2 + ans;
	ch[0] = p[0];
	ch[1] = p[1];
	ch[2] = p[2];
	top = 2;
	for (int i = 3; i < n; ++i) {
		while (!(cross(ch[top - 1], p[i], ch[top]) < 0))
			--top;
		ch[++top] = p[i];
	}
	top++;
	for (i = 0; i < top; i++)
		ans += dis(ch[i], ch[(i + 1) % top]);
	return ans;
}
 
double solve() {
	int i, j, k, cnt;
	cnt = (1 << n) - 1;
	for (i = 0; i < n; i++)
		pl[i].get();
	for(i = 1; i<= cnt; i++)
		coans[i] = calc(i);
	for (i = 1; i <= cnt; i++) {
		dp[i] = 1e30;
		for (j = 1; j <= cnt; j++)
			if ((i | j) == i) {
				k = i - j;
				dp[i] = min(dp[i], dp[k] + coans[j]);
			}
	}
	return dp[cnt];
}
 
int main() {
	int ca = 1;
	while (scanf("%d%lf", &n, &mar) && n)
		printf("Case %d: length = %.2lf\n", ca++, solve());
	return 0;
}
