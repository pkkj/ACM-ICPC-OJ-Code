// CII 4617
// 2009 Northwestern Europe: Simple Polygon
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 2005
struct POINT {
	double x, y;
	int id;
	void get(int i) {
		scanf("%lf%lf", &x, &y);
		id = i;
	}
	bool operator <(const POINT &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};
 
inline double cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
 
POINT pl[N], ch[N];
bool vis[N];
int n;
void solve() {
	int n, i, top;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		pl[i].get(i);
	sort(pl, pl + n);
	ch[0] = pl[0];
	top = 0;
	for (int i = 1; i < n; i++) {
		while (top >= 1 && cross(ch[top - 1], pl[i], ch[top]) > 0)
			--top;
		ch[++top] = pl[i];
	}
	memset(vis, 0, sizeof(vis));
	for (i = 0; i <= top; i++) {
		printf("%d ", ch[i].id);
		vis[ch[i].id] = 1;
	}
	for (i = n - 1; i >= 0; i--)
		if (!vis[pl[i].id]) printf("%d ", pl[i].id);
	printf("\n");
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
