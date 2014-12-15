// POJ 2928
// 2005 MIT Programming Contest: A City of Skyscrapers
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100005
int a[N], b[N];
int main() {
	//freopen("in.txt", "r", stdin);
	int n, m, c, C, i, j, row, col, maxa = 0, maxb = 0;
	scanf("%d%d%d%d", &n, &m, &c, &C);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		maxa = max(maxa, a[i]);
	}
	for (i = 0; i < m; i++) {
		scanf("%d", &b[i]);
		maxb = max(maxb, b[i]);
	}
	if (maxa != maxb) {
		printf("Impossible\n");
		return 0;
	}
	sort(a, a + n);
	sort(b, b + n);
 
	int ans1, ans2;
	ans1 = ans2 = 0;
 
	// Get the minimum value
	i = 0, j = 0;
	while (i < n && j < m) {
		if (a[i] < b[j]) ans1 += a[i++];
		else if (a[i] > b[j]) ans1 += b[j++];
		else ans1 += a[i++], j++;
	}
	while (i < n)
		ans1 += a[i++];
	while (j < m)
		ans1 += b[j++];
	ans1 *= c;
 
	// Get the maximum value
	row = n, col = m;
	i = 0, j = 0;
	while (i < n && j < m) {
		if (a[i] < b[j]) {
			ans2 += a[i++] * col;
			row--;
		} else {
			ans2 += b[j++] * row;
			col--;
		}
	}
	while (i < n)
		ans2 += a[i++] * col;
	while (j < m)
		ans2 += b[j++] * row;
	ans2 *= C;
 
	printf("Minimum: %d, maximum: %d\n", ans1, ans2);
	return 0;
}
