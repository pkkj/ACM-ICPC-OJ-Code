// 2009 World Finals: A Careful Approach
// ACM-ICPC Live Archive 4445

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 10
int n, b[N], e[N];
bool check(double t) {
	int i, idx[N];
	for (i = 0; i < n; i++)
		idx[i] = i;
	do {
		int ok = 1;
		double cur = b[idx[0]];
		for (i = 1; i < n && ok; i++) {
			cur += t;
			if(cur < b[idx[i]])
				cur = b[idx[i]];
			if(cur > e[idx[i]])
				ok = 0;
		}
		if(ok)return 1;
	} while (next_permutation(idx, idx + n));
	return 0;
}
void solve() {
	int i, ans;
	for (i = 0; i < n; i++) {
		scanf("%d%d", &b[i], &e[i]);
		b[i] *= 60, e[i] *= 60;
	}
	double l, r, mid;
	l = 0, r = 1441 * 60;
	while (l + 0.05 < r) {
		mid = (l + r) / 2.0;
		if (check(mid)) l = mid;
		else r = mid;
	}
	ans = (int) (mid + 0.5);
	printf("%d:%02d\n", ans / 60, ans % 60);
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
