// 2008 Chengdu: Transit search
// ACM-ICPC Live Archive 4400
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define NL 105
#define NS 5005
struct POINT {
	int x, y;
	POINT() {
	}
	POINT(int x, int y) :
		x(x), y(y) {
	}
	void get(char cmd[], int dx, int dy) {
		int scale[] = { 5120, 2560, 1280, 640, 320, 160, 80, 40 };
		x = dx * 4, y = dy * 4;
		for (int i = 0; i < 8; i++) {
			switch (cmd[i]) {
			case '1':
				y += scale[i];
				break;
			case '2':
				x += scale[i];
				break;
			case '3':
				x += scale[i], y += scale[i];
				break;
			}
		}
	}
};
struct STATION {
	POINT pt;
	bool bus[NL], cs, ct;
};
 
struct LINE {
	vector<int> l;
	bool cs, ct;
};
double sqr(double x) {
	return x * x;
}
double dis(POINT &a, POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
map<string, int> maptosta;
int nl, ns;
POINT ps, pt;
LINE line[NL];
bool G[NL][NL];
STATION station[NS];
void init() {
	char rs[9], rt[9];
	int sx, sy, tx, ty, i, j, x, y;
	char name[25];
	maptosta.clear();
	scanf("%s%d%d", rs, &sx, &sy);
	scanf("%s%d%d", rt, &tx, &ty);
	ps.get(rs, sx, sy);
	pt.get(rt, tx, ty);
	scanf("%d", &ns);
	for (i = 0; i < ns; i++) {
		scanf("%s%d%d", name, &x, &y);
		maptosta[string(name)] = i;
		memset(station[i].bus, 0, sizeof(station[i].bus));
		station[i].pt = POINT(x, y);
	}
	scanf("%d", &nl);
	for (i = 0; i < nl; i++) {
		int m, idx;
		scanf("%d", &m);
		line[i].l.clear();
		for (j = 0; j < m; j++) {
			scanf("%s", name);
			idx = maptosta[name];
			line[i].l.push_back(idx);
			station[idx].bus[i] = 1;
		}
	}
}
 
bool pre() {
	int i, cs = 0, ct = 0;
	if (dis(ps, pt) <= 2000) {
		printf("walk there\n");
		return 0;
	}
	for (i = 0; i < ns; i++) {
		if (dis(ps, station[i].pt) <= 1000) cs = 1, station[i].cs = 1;
		else station[i].cs = 0;
		if (dis(pt, station[i].pt) <= 1000) ct = 1, station[i].ct = 1;
		else station[i].ct = 0;
	}
	if (!(cs && ct)) {
		printf("take a taxi\n");
		return 0;
	}
	return 1;
}
bool checklink(int i, int j) {
	int k;
	for (k = 0; k < (int) line[i].l.size(); k++)
		if (station[line[i].l[k]].bus[j]) return 1;
	return 0;
}
void build() {
	int i, j;
	memset(G, 0, sizeof(G));
	for (i = 0; i < nl; i++) {
		line[i].cs = line[i].ct = 0;
		for (j = 0; j < (int) line[i].l.size(); j++) {
			if (station[line[i].l[j]].cs) line[i].cs = 1;
			if (station[line[i].l[j]].ct) line[i].ct = 1;
		}
		for (j = i + 1; j < nl; j++) {
			if (checklink(i, j)) G[i][j] = G[j][i] = 1;
		}
	}
}
#define INF 1000
int best;
int bfs(int s) {
	int np = 1, sp, d = 1, i;
	bool v[NL] = { 0 };
	queue<int> Q;
	Q.push(s), v[s] = 1;
	while (!Q.empty()) {
		sp = 0;
		while (np--) {
			int x = Q.front();
			Q.pop();
			if (line[x].ct) return d;
			for (i = 0; i < nl; i++)
				if (G[x][i] && !v[i]) Q.push(i), sp++, v[i] = 1;
		}
		np = sp, d++;
		if (d >= best) return INF;
	}
	return INF;
}
void solve() {
	int i;
	init();
	if (!pre()) return;
	build();
	for (i = 0,best = INF; i < nl; i++)
		if (line[i].cs) best = min(best, bfs(i));
	if (best == INF) printf("take a taxi\n");
	else printf("%d\n", best);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}