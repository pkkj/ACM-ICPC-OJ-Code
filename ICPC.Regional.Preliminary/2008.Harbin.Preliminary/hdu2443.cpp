// 2008 Harbin Preliminary: Counter Strike
// HDU 2443

#include <cstdio>
#define N 100005
__int64 a[N], b[N], change;
void merge(int l, int m, int r) {
	int i = 0, j, ba, bb, ea, eb;
	ba = l, ea = m, bb = m + 1, eb = r;
	while (ba <= ea && bb <= eb) {
		if (a[ba] <= a[bb])
			b[i++] = a[ba++];
		else {
			b[i++] = a[bb++];
			change += ea - ba + 1;
		}
	}
	for (; ba <= ea; ba++)
		b[i++] = a[ba];
	for (; bb <= eb; bb++)
		b[i++] = a[bb];
	for (j = 0; j < i; j++)
		a[l + j] = b[j];
}
void mergesort(int l, int r) {
	if (r > l) {
		int mid = (l + r) / 2;
		mergesort(l, mid);
		mergesort(mid + 1, r);
		merge(l, mid, r);
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int i, n, x;
		scanf("%d%d", &n, &x);
		a[n] = 0;
		for (i = 0; i < n; i++)
			scanf("%I64d", a + i);
		for (i = n - 1; i >= 0; i--)
			a[i] = a[i] + a[i + 1] - x;
		change = 0;
		mergesort(0, n);
		printf("%I64d\n", change);
	}
	return 0;
}
