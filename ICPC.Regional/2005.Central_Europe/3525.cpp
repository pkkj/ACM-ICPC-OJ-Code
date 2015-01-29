// CII 3525
// 2005 Central Europe: Wild West
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100005
typedef long long ll;
struct POINT {
	int x, y, z;
	bool operator<(const POINT &p) const {
		return z > p.z;
	}
	void get() {
		scanf("%d%d%d", &x, &y, &z);
	}
};
 
// Segment tree
#define M 50000
int tot;
struct NODE {
	int ls, rs, l, r, y, min, max;
	long long s;
};
NODE T[M];
int addnode(int l, int r) {
	tot++;
	T[tot].ls = T[tot].rs = -1;
	T[tot].l = l, T[tot].r = r;
	T[tot].y = T[tot].s = T[tot].max = T[tot].min = 0;
	return tot;
}
void insert(int p, int r, int y) {
	if (r <= T[p].l) return;
	if (y <= T[p].min) return;
	if (T[p].y != -1) {
		if (r >= T[p].r) {
			T[p].y = T[p].max = T[p].min = y;
			T[p].s = y * (T[p].r - T[p].l);
			return;
		} else {
			int mid = (T[p].l + T[p].r) >> 1;
			if (T[p].ls == -1) T[p].ls = addnode(T[p].l, mid);
			if (T[p].rs == -1) T[p].rs = addnode(mid, T[p].r);
			T[T[p].ls].y = T[T[p].ls].max = T[T[p].ls].min = T[p].y;
			T[T[p].ls].s = (ll) T[T[p].ls].y * (T[T[p].ls].r - T[T[p].ls].l);
 
			T[T[p].rs].y = T[T[p].rs].max = T[T[p].rs].min = T[p].y;
			T[T[p].rs].s = (ll) T[T[p].rs].y * (T[T[p].rs].r - T[T[p].rs].l);
 
			T[p].y = -1;
		}
	} else {
		if (y >= T[p].max && r >= T[p].r) {
			T[p].y = T[p].max = T[p].min = y;
			T[p].s = y * (T[p].r - T[p].l);
			return;
		}
	}
	insert(T[p].ls, r, y);
	insert(T[p].rs, r, y);
	T[p].max = T[T[p].ls].max > T[T[p].rs].max ? T[T[p].ls].max : T[T[p].rs].max;
	T[p].min = T[T[p].ls].min < T[T[p].rs].min ? T[T[p].ls].min : T[T[p].rs].min;
	T[p].s = T[T[p].ls].s + T[T[p].rs].s;
 
}
// End of segment tree
int n;
ll m;
POINT pl[N];
int init() {
	scanf("%d%lld", &n, &m);
	if (!(n + m)) return 0;
	for (int i = 0; i < n; i++)
		pl[i].get();
	return 1;
}
 
void solve() {
	int i;
	long long ans = 0, m3;
	sort(pl, pl + n);
	tot = 0;
	addnode(0, m);
	pl[n].z = 0;
	for (i = 0; i < n; i++) {
		insert(1, pl[i].x, pl[i].y);
		ans += (ll) (pl[i].z - pl[i + 1].z) * T[1].s;
	}
	m3 = m * m * m;
	printf("%lld\n", m3 - ans);
}
int main() {
	while (init())
		solve();
}
