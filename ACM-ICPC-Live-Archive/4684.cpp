// CII 4684
// 2009 Amritapuri: Love for Pizza
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
#define N 200005
struct NODE {
	int l, r;
	long long mmax, lmax, rmax, sum;
};
 
NODE T[N * 3];
long long seq[N];
long long max(long long x, long long y, long long z) {
	return max(x, max(y, z));
}
void update(int p) {
	T[p].sum = T[p * 2].sum + T[p * 2 + 1].sum;
	T[p].mmax = max(T[p * 2].mmax, T[p * 2 + 1].mmax, T[p * 2].rmax + T[p * 2 + 1].lmax);
	T[p].lmax = max(T[p * 2].lmax, T[p * 2].sum + T[p * 2 + 1].lmax);
	T[p].rmax = max(T[p * 2 + 1].rmax, T[p * 2 + 1].sum + T[p * 2].rmax);
}
 
NODE query(int p, int l, int r) {
	NODE ans, al, ar;
	int mid = (T[p].l + T[p].r) >> 1;
	if (l <= T[p].l && T[p].r <= r) return T[p];
	if (r <= mid) return query(p * 2, l, r);
	if (l >= mid + 1) return query(p * 2 + 1, l, r);
	al = query(p * 2, l, mid), ar = query(p * 2 + 1, mid + 1, r);
	ans.sum = al.sum + ar.sum;
	ans.mmax = max(al.mmax, ar.mmax, al.rmax + ar.lmax);
	ans.lmax = max(al.lmax, al.sum + ar.lmax);
	ans.rmax = max(ar.rmax, ar.sum + al.rmax);
	return ans;
}
void build(int p, int l, int r) {
	T[p].l = l, T[p].r = r;
	if (l == r) T[p].lmax = T[p].mmax = T[p].rmax = T[p].sum = seq[l];
	else {
		int mid = (l + r) >> 1;
		build(p * 2, l, mid);
		build(p * 2 + 1, mid + 1, r);
		update(p);
	}
}
struct POINT {
	long long v;
	double a;
	bool operator <(const POINT &p) const {
		return a < p.a;
	}
	void get() {
		int x, y;
		scanf("%lld%d%d", &v, &x, &y);
		a = atan2((double) y, double(x));
	}
};
 
POINT pl[N];
int main() {
	int n, i, T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (i = 1; i <= n; i++)
			pl[i].get();
		sort(pl + 1, pl + n + 1);
		int cnt = 0;
		for (i = 1; i <= n; i++) {
			if (i == 1 || fabs(pl[i].a - pl[i - 1].a) > 1e-8) seq[++cnt] = pl[i].v;
			else seq[cnt] += pl[i].v;
		}
		for (i = cnt + 1; i <= cnt + cnt; i++)
			seq[i] = seq[i - cnt];
		n = cnt;
		build(1, 1, 2 * n);
		long long ans = 0;
		for (i = 1; i <= n; i++)
			ans = max(ans, query(1, i, n + i - 1).mmax);
		printf("%lld\n", ans);
	}
	return 0;
}
