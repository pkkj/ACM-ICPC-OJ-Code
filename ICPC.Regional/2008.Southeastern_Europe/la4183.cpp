// 2008 Southeastern Europe: Stock Exchange
// ACM-ICPC Live Archive 4183

#include <cstdio>
#include <cstring>
#define N 100002
int B[N], f[N], a[N];
int n;
void solve() {
	int i, mid, right, left, num, blen, max = 0;
	for (i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	blen = 1;
	B[1] = a[1];
	for (i = 1; i <= n; i++) {
		num = a[i], left = 1, right = blen;
		while (left <= right) {
			mid = (left + right) / 2;
			if (B[mid] < num) left = mid + 1;
			else right = mid - 1;
		}
		f[i] = left;
		B[left] = num;
		if (blen < left) blen = left;
		if (max < f[i]) max = f[i];
	}
	printf("%d\n", max);
}
 
int main() {
	while (scanf("%d", &n) != EOF)
		solve();
	return 0;
}