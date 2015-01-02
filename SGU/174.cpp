// SGU 177 Walls
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
#define N 400005
 
struct POINT {
	int x, y;
	bool operator <(const POINT &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
	void get() {
		scanf("%d%d", &x, &y);
	}
};
 
// Union set
int fa[N];
void setinit(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i;
}
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
 
void uniset(int x, int y) {
	fa[x] = y;
}
int id = 0;
map<POINT, int> ll;
int main() {
	int n, i1, i2, ans = 1;
	POINT p1, p2;
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	setinit(n * 2);
	while (n--) {
		p1.get(), p2.get();
		if (ans == 1) {
			ll[p1] = id++, ll[p2] = id++;
			uniset(0, 1);
		} else {
			if (ll.find(p1) != ll.end()) i1 = ll[p1];
			else {
				i1 = id;
				ll[p1] = id++;
			}
			if (ll.find(p2) != ll.end()) i2 = ll[p2];
			else {
				i2 = id;
				ll[p2] = id++;
			}
			i1 = find(i1), i2 = find(i2);
			if (i1 == i2) {
				printf("%d\n", ans);
				return 0;
			} else uniset(i1, i2);
		}
		ans++;
	}
	printf("0\n");
	return 0;
}
