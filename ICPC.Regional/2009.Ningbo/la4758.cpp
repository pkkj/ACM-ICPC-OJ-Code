// 2009 Ningbo: Poster
// ACM-ICPC Live Archive 4758
// HDU 3265
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 50005
struct NODE {
	int l, r, len, cover;
};
NODE T[N * 10];
struct EVENT {
#define IN 1
#define OUT -1
	int x, y1, y2, type;
	EVENT() {
	}
	EVENT(int x, int y1, int y2, int type) :
			x(x), y1(y1), y2(y2), type(type) {
	}
	bool operator <(const EVENT &e) const {
		return x < e.x;
	}
};
EVENT E[N * 10];
int n;
void build(int p, int l, int r) {
	T[p].l = l, T[p].r = r, T[p].len = 0, T[p].cover = 0;
	if (r - l == 1) {
		T[p * 2].len = T[p * 2].cover = T[p * 2 + 1].len = T[p * 2 + 1].cover = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(p * 2, l, mid);
	build(p * 2 + 1, mid, r);
}
void update(int p) {
	if (T[p].cover > 0)
		T[p].len = T[p].r - T[p].l;
	else
		T[p].len = T[p * 2].len + T[p * 2 + 1].len;
}
void change(int p, int l, int r, int ch) {
	if (l >= T[p].r || r <= T[p].l)
		return;
	if (l <= T[p].l && T[p].r <= r)
		T[p].cover += ch;
	else {
		change(p * 2, l, r, ch);
		change(p * 2 + 1, l, r, ch);
	}
	update(p);
}

void solve() {
	int i, cnt = 0, maxy = 0;
	LL ans = 0;
	for (i = 0; i < n; i++) {
		int x1, y1, x2, y2, x3, y3, x4, y4;
		scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		maxy = max(maxy, y2);
		if (x1 != x3 && y1 != y2)
			E[cnt++] = EVENT(x1, y1, y2, IN), E[cnt++] = EVENT(x3, y1, y2, OUT);
		if (x3 != x4 && y1 != y3)
			E[cnt++] = EVENT(x3, y1, y3, IN), E[cnt++] = EVENT(x4, y1, y3, OUT);
		if (x3 != x4 && y2 != y4)
			E[cnt++] = EVENT(x3, y4, y2, IN), E[cnt++] = EVENT(x4, y4, y2, OUT);
		if (x4 != x2 && y1 != y2)
			E[cnt++] = EVENT(x4, y1, y2, IN), E[cnt++] = EVENT(x2, y1, y2, OUT);
	}
	sort(E, E + cnt);
	build(1, 0, maxy);
	change(1, E[0].y1, E[0].y2, E[0].type);

	for (i = 1; i < cnt; i++) {
		LL dx = E[i].x - E[i - 1].x;
		ans += dx * T[1].len;
		change(1, E[i].y1, E[i].y2, E[i].type);
	}
	printf("%lld\n", ans);
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
	return 0;
}
