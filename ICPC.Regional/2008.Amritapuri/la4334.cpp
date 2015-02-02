// 2008 Amritapuri: Gold Digging
// ACM-ICPC Live Archive 4334
#include <cstdio>
#include <queue>
using namespace std;
#define EPS 1e-10
int n;
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct NODE {
	double sum, po, ok, se, ex;
	bool operator <(const NODE &p) const {
		return se < p.se;
	}
};
 
void solve() {
	priority_queue<NODE> Q;
	while(n--) {
		NODE x;
		scanf("%lf%lf%lf", &x.ok, &x.po, &x.sum);
		x.ok /= 100.0, x.po /= 100.0;
		x.ok = 1 - x.ok;
		x.ex = x.ok * x.po * x.sum;
		x.se = x.ex / (1 - x.ok);
		Q.push(x);
	}
	double k = 1, ans = 0;
	while (!Q.empty()) {
		NODE x;
		x = Q.top();
		Q.pop();
		if (k * x.ex < EPS) break;
		ans += k * x.ex;
		k *= x.ok;
		if (x.po != 1) {
			x.sum *= (1 - x.po);
			x.ex = x.ok * x.po * x.sum;
			x.se = x.ex / (1 - x.ok);
			Q.push(x);
		}
	}
	printf("%.6lf\n", ans);
}
int main() {
	while (scanf("%d", &n) && n != -1)
		solve();
	return 0;
}