// 2009 World Finals: Struts and Springs
// ACM-ICPC Live Archive 4453

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 105
int ca, n, Q, w, h;
 
struct WINDOW {
	long long x, y, w, h, s[6];
	long long hh[3], vv[3];
	vector<int> sons;
	void get() {
		scanf("%d%d%d%d", &x, &y, &w, &h);
		for (int i = 0; i < 6; i++)
			scanf("%d", &s[i]);
		if (s[0] == 0 && s[4] == 0 && s[5] == 0) s[5] = 1;
		if (s[1] == 0 && s[2] == 0 && s[3] == 0) s[2] = 1;
		sons.clear();
	}
	void print(int i) {
		printf("    Window %d, x = %lld, y = %lld, width = %lld, height = %lld\n", i, x, y, w, h);
	}
};
long long between(long long a, long long b, long long c) {
	return a <= b && b <= c;
}
WINDOW win[N], root, win2[N];
void buildre(WINDOW fa, WINDOW &so) {
	long long x = so.x - fa.x, y = so.y - fa.y;
	so.hh[0] = x, so.hh[1] = so.w;
	so.hh[2] = fa.w - so.w - x;
	so.vv[0] = y, so.vv[1] = so.h;
	so.vv[2] = fa.h - so.h - y;
}
void build() {
	int i, j;
	for (i = 0; i < n; i++) {
		int fa = -1, mm = 1 << 30;
		for (j = 0; j < n; j++) {
			if (i == j) continue;
			if (between(win[j].x, win[i].x, win[j].x + win[j].w) && between(win[j].y, win[i].y, win[j].y + win[j].h)) {
				if (win[j].w < mm) fa = j, mm = win[j].w;
			}
		}
		if (fa == -1) {
			root.sons.push_back(i);
			buildre(root, win[i]);
		} else {
			win[fa].sons.push_back(i);
			buildre(win[fa], win[i]);
		}
	}
}
 
void dfs(int id, long long x, long long y, long long dw, long long dh) {
	int i;
	long long len = win[id].hh[0] + win[id].hh[1] + win[id].hh[2];
	if (!win[id].s[4]) len -= win[id].hh[0];
	if (!win[id].s[0]) len -= win[id].hh[1];
	if (!win[id].s[5]) len -= win[id].hh[2];
 
	if (win[id].s[4]) win[id].hh[0] = win[id].hh[0] * dw / len + win[id].hh[0];
	if (win[id].s[0]) win[id].hh[1] = win[id].hh[1] * dw / len + win[id].hh[1];
	if (win[id].s[5]) win[id].hh[2] = win[id].hh[2] * dw / len + win[id].hh[2];
 
	len = win[id].vv[0] + win[id].vv[1] + win[id].vv[2];
	if (!win[id].s[2]) len -= win[id].vv[0];
	if (!win[id].s[1]) len -= win[id].vv[1];
	if (!win[id].s[3]) len -= win[id].vv[2];
 
	if (win[id].s[2]) win[id].vv[0] = win[id].vv[0] * dh / len + win[id].vv[0];
	if (win[id].s[1]) win[id].vv[1] = win[id].vv[1] * dh / len + win[id].vv[1];
	if (win[id].s[3]) win[id].vv[2] = win[id].vv[2] * dh / len + win[id].vv[2];
 
	win[id].x = x + win[id].hh[0];
	win[id].y = y + win[id].vv[0];
	win[id].w = win[id].hh[1];
	win[id].h = win[id].vv[1];
 
	// Continue dfs
	for (i = 0; i < (int) win[id].sons.size(); i++)
		dfs(win[id].sons[i], win[id].x, win[id].y, win[id].w - win2[id].w, win[id].h - win2[id].h);
}
void solve() {
	int i, qc = 1;
	WINDOW nr;
	for (i = 0; i < n; i++)
		win[i].get();
	root.sons.clear();
	root.x = root.y = 0;
	build();
	nr = root;
	memcpy(win2, win, sizeof(win));
	while (Q--) {
		scanf("%lld%lld", &root.w, &root.h);
		printf("Case %d, resize operation %d:\n", ca, qc++);
		memcpy(win, win2, sizeof(win));
		for (i = 0; i < (int) root.sons.size(); i++)
			dfs(root.sons[i], 0, 0, root.w - nr.w, root.h - nr.h);
		for (i = 0; i < n; i++)
			win[i].print(i + 1);
	}
}
int main() {
	ca = 1;
	while (scanf("%d%d%d%d", &n, &Q, &root.w, &root.h) && (n + Q)) {
		solve();
		ca++;
	}
	return 0;
}
