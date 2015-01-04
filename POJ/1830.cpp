// POJ 1830 开关问题
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 33
int mm[N][N];
 
int gauss(int n) {
	int i, j, k, row, col;
	for (k = col = 0; k < n && col < n; k++, col++) {
		row = k;
		for (i = k + 1; i < n; i++)
			if (mm[i][col]) {
				row = i;
				break;
			}
		if (k != row) for (i = k; i <= n; i++)
			swap(mm[k][i], mm[row][i]);
		if (mm[k][col] == 0) {
			k--;
			continue;
		}
		for (i = k + 1; i < n; i++)
			if (mm[i][col]) for (j = col; j <= n; j++)
				mm[i][j] ^= mm[k][j];
	}
	for (i = k; i < n; i++)
		if (mm[i][n]) return -1;
	return n - k;
}
void solve() {
	int beg[N], end[N], i, a, b, n;
	memset(mm, 0, sizeof(mm));
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", beg + i);
	for (i = 0; i < n; i++)
		scanf("%d", end + i);
	for (i = 0; i < n; i++)
		mm[i][n] = beg[i] ^ end[i], mm[i][i] = 1;
	while (scanf("%d%d", &a, &b) && (a + b))
		mm[b - 1][a - 1] = 1;
	int ans = gauss(n);
	if (ans == -1) printf("Oh,it's impossible~!!\n");
	else printf("%d\n", 1 << ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
