// CII 4611
// 2009 Northwestern Europe: Divisible Subsequences
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define N 50005
 
map<int, int> MAP;
void solve() {
	int n, d, x, s = 0, i;
	long long ans = 0;
	scanf("%lld%d", &d, &n);
	MAP.clear();
	MAP[0] = 1;
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		s = (s + x) % d;
		if (MAP.find(s) != MAP.end()) MAP[s]++;
		else MAP[s] = 1;
	}
	map<int, int>::iterator it;
	for (it = MAP.begin(); it != MAP.end(); it++) {
		long long x = it->second - 1;
		ans += (x * x + x) / 2;
	}
	printf("%lld\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
