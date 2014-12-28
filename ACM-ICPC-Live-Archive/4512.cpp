// CII 4512
// 2009 Southwestern Europe: Happy Telephones
#include <cstdio>
#define N 10005
struct RANGE {
	int b, e;
	void get() {
		scanf("%d%d", &b, &e);
		e = b + e;
	}
};
RANGE rl[N];
int main() {
	int i, n, m, a, b;
	while (scanf("%d%d", &n, &m) && n) {
		for (i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			rl[i].get();
		}
		while (m--) {
			int ans = 0;
			RANGE r;
			r.get();
			for (i = 0; i < n; i++) {
				if (r.e <= rl[i].b || r.b >= rl[i].e) continue;
				ans++;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
