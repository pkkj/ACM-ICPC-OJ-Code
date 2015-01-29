// CII 4425 
// 2008 Tehran: Another Brick in the Wall
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
#define SI 105
#define N 10005
char s[SI][SI];
int id[SI][SI], size[N], ind[N];
struct EDGE {
	int b, next;
};
int GA[N], GF[N], tot;
EDGE E[200000];
void addedge(int G[], int a, int b) {
	EDGE e = { b, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
void build() {
	int i, j, k;
	memset(GA, -1, sizeof(GA));
	memset(GF, -1, sizeof(GF));
	tot = 0;
	for (i = n - 1; i > 0; i--)
		for (j = 0; j < m;) {
			if (s[i][j] == '0') {
				j++;
			} else {
				int cur = id[i][j], pre = -1;
				for (k = j; k < j + s[i][j] - '0'; k++) {
					int next = id[i - 1][k];
					if (next != pre && next != -1) {
						addedge(GA, cur, next);
						addedge(GF, next, cur);
						ind[next]++;
						pre = next;
					}
				}
				j = k;
			}
		}
}
bool v[N];
int Q[N];
int bfs(int st) {
	int qh, qe, ret = 0, i, j;
	memset(v, 0, sizeof(v));
	memset(ind, 0, sizeof(ind));
	v[st] = 1;
	qh = qe = 0;
	Q[qe++] = st;
	while (qh < qe) {
		int top = Q[qh++];
		v[top] = 1;
		ret += size[top];
		for (i = GA[top]; ~i; i = E[i].next) {
			int ok = 1;
			if (v[E[i].b]) continue;
			for (j = GF[E[i].b]; (~j) && ok; j = E[j].next) {
				if (v[E[j].b] == 0) ok = 0;
			}
			if (ok) {
				Q[qe++] = E[i].b;
				v[E[i].b] = 1;
			}
		}
	}
	return ret;
}
void solve() {
	int i, j, k, sid = 0, ans = 0;
	for (i = 0; i < n; i++)
		scanf("%s", s[i]);
	for (i = 0; i < n; i++) {
		for (j = 0; j < m;) {
			if (s[i][j] == '0') {
				id[i][j] = -1;
				j++;
			} else {
				size[sid] = s[i][j] - '0';
				for (k = j; k < j + s[i][j] - '0'; k++)
					id[i][k] = sid;
				sid++, j = k;
			}
		}
	}
	build();
	for (i = 0; i < sid; i++) {
		if(ind[i]==1)continue;
		int ret = bfs(i);
		if (ret > ans) ans = ret;
	}
	printf("%d\n", ans);
}
 
int main() {
	while (scanf("%d%d", &n, &m) && n)
		solve();
	return 0;
}
