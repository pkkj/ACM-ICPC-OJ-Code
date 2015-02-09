// 2005 Southwestern Europe: Buy or Build
// ACM-ICPC Live Archive 3505
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 1005
int fa[N], rank[N], n, q;
void init_set(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i, ::rank[i] = 0;
}
int find_root(int p) {
	if (fa[p] != p)
		fa[p] = find_root(fa[p]);
	return fa[p];
}
void union_set(int p, int q) {
	int a = find_root(p), b = find_root(q);
	if (::rank[a] > ::rank[b])
		fa[b] = a;
	else if (::rank[a] < ::rank[b])
		fa[a] = b;
	else
		fa[b] = a, ::rank[a]++;
}
struct POINT {
	int x, y;
};

struct NET {
	int cost;
	vector<int> city;
};

struct EDGE {
	int a, b, len;
	EDGE() {
	}
	EDGE(int a, int b, int len) :
		a(a), b(b), len(len) {
	}
	bool operator <(const EDGE &x) const {
		return len < x.len;
	}
};

int dis(const POINT &a, const POINT &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
POINT pl[N];
NET nl[9];
EDGE el[N * N], mst[N];

void getmst(int m) {
	int p = 0, i = 0;
	init_set(n);
	while (p < n - 1) {
		int a, b;
		a = el[i].a, b = el[i].b;
		if (find_root(a) != find_root(b)) {
			union_set(a, b);
			mst[p++] = el[i];
		}
		i++;
	}
}
int curbest;
int checknet(int st) {
	int i, j, ans = 0, linked = 1, a, b;
	init_set(n);
	for (i = 0; i < q; i++) {
		if (st & 1) {
			ans += nl[i].cost;
			if (ans >= curbest)
				return curbest;
			for (j = 1; j < (int)nl[i].city.size(); j++) {
				a = nl[i].city[j - 1], b = nl[i].city[j];
				if (find_root(a) != find_root(b)) {
					union_set(a, b);
					linked++;
				}
			}
		}
		st = st >> 1;
	}

	i = 0;
	while (linked < n) {
		a = el[i].a, b = el[i].b;
		if (find_root(a) != find_root(b)) {
			union_set(a, b);
			linked++;
			ans += el[i].len;
			if (ans >= curbest)
				return curbest;
		}
		i++;
	}
	if (ans < curbest)
		return ans;
	return curbest;
}
int main() {
	int i, j, t, m, T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca) printf("\n");
		scanf("%d%d", &n, &q);
		for (i = 0; i < q; i++) {
			scanf("%d%d", &t, &nl[i].cost);
			nl[i].city.resize(t);
			for (j = 0; j < t; j++) {
				scanf("%d", &nl[i].city[j]);
				nl[i].city[j]--;
			}
		}
		for (i = 0; i < n; i++) {
			scanf("%d%d", &pl[i].x, &pl[i].y);
		}
		m = 0;
		for (i = 0; i < n; i++)
			for (j = i + 1; j < n; j++) {
				el[m++] = EDGE(i, j, dis(pl[i], pl[j]));
			}
		sort(el, el + m);
		getmst(m);
		curbest = 1 << 30;
		for (i = 0; i < (1 << q); i++) {
			curbest = checknet(i);
		}
		printf("%d\n", curbest);
	}
	return 0;
}
