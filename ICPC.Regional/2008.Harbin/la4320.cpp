// 2008 Harbin: Degree Sequence of Graph G
// ACM-ICPC Live Archive 4320

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1005
int deg[N];
bool cmp(const int &a, const int &b) {
	return a > b;
}
int solve() {
	int n, i, t;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", deg + i);
	sort(deg, deg + n, cmp);
	for (t = 0; t < n; t++) {
		for (i = 1; i < n && deg[0]; i++)
			if (deg[i] > 0) deg[i]--, deg[0]--;
		if (deg[0]) return 0;
		sort(deg, deg + n - t, cmp);
	}
	return 1;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		puts(solve() ? "yes" : "no");
	return 0;
}