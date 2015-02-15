// 2008 Chengdu Preliminary: Stars
// HDU 2428

#include<cstdio>
#include<map>
#include<algorithm>
#define M 50001
using namespace std;
map<int, int> m[M];

struct POINT {
	int x, y;
	POINT(int x, int y) :
			x(x), y(y) {
	}
	POINT() :
			x(0), y(0) {
	}
};
POINT q[M];

int main() {
	int n, T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < M; i++)
			m[i].clear();
		for (int i = 0; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			m[a + 10001][b] = 1;
			q[i] = POINT(a + 10001, b);
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int x1 = q[i].x, y1 = q[i].y;
				int x2 = q[j].x, y2 = q[j].y;
				int x3 = x1, y3 = y2, x4 = x2, y4 = y1;
				if (y2 - y1 != x2 - x1)
					continue;
				if (m[x3].find(y3) != m[x3].end() && m[x4].find(y4) != m[x4].end())
					ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
