// 2006 Northeastern Europe: Graveyard
// ACM-ICPC Live Archive 3708

#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

#define PI 3.1415926536
struct POINT {
	double c;
	int f;
	POINT() {
	}
	POINT(double c, int f) :
			c(c), f(f) {
	}
	bool operator<(const POINT &x) const {
		return c < x.c;
	}
};


int n, m;
double solve() {
	double CR, d1, d2;
	vector<POINT> pl;
	CR = 10000;
	if (n == m)
		return 0.0;

	d1 = CR / n;
	d2 = CR / (m + n);
	for (int i = 1; i < n; i++)
		pl.push_back(POINT(d1 * i, 0));
	for (int i = 1; i < m + n; i++)
		pl.push_back(POINT(d2 * i, 1));
	sort(pl.begin(), pl.end());

	double ans = 0;
	for (size_t i = 0; i < pl.size(); i++)
		if (pl[i].f == 0) {
			double up, dn;
			up = pl[i + 1].c - pl[i].c;
			dn = pl[i].c - pl[i - 1].c;
			if (dn < up && pl[i - 1].f == 1) {
				ans += dn;
			} else {
				ans += up;
				pl[i + 1].f = 2;

			}
		}

	return ans;
}

int main(){
	while(~scanf("%d%d", &n, &m))
		printf("%.5lf\n", solve());
	return 0;
}
