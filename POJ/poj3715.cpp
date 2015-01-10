// POJ 3715
// POJ Monthly Contest - 2009.02.22: Blue and Red
#include <cstdio>
#include <cstring>
#define N 205
#define M 40005
bool color[N], del[N], v[N];
int nl, nr, link[N], n, tot, G[N];
struct EDGE {
	int b, nxt;
};
EDGE E[M];
int dfs(int x) {
	int i, j;
	for (j = G[x]; j != -1; j = E[j].nxt) {
		i = E[j].b;
		if (!del[i] && !v[i]) {
			v[i] = 1;
			if (link[i] == -1 || dfs(link[i])) {
				link[i] = x;
				return 1;
			}
		}
	}
	return 0;
}
 
void add(int a, int b) {
	EDGE e = { b, G[a] };
	E[tot] = e;
	G[a] = tot++;
 
}
void solve() {
	int i, j, m, x, match = 0, aa;
	// Init
	tot = 0;
	memset(G, -1, sizeof(G));
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d", &x);
		color[i] = x == 1;
	}
	while (m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		a++, b++;
		if (color[a] != color[b]) add(a, b), add(b, a);
	}
 
	// Hungary Algorithm
	memset(link, -1, sizeof(link));
	memset(del, 0, sizeof(del));
 
	for (i = 1; i <= n; i++)
		if (!color[i]) {
			memset(v, 0, sizeof(v));
			match += dfs(i);
		}
	printf("%d ", match);
	for (j = 1; j <= n && match; j++) {
		del[j] = 1, aa = 0;
		memset(link, -1, sizeof(link));
 
		for (i = 1; i <= n; i++)
			if (!color[i] && !del[i]) {
				memset(v, 0, sizeof(v));
				aa += dfs(i);
			}
		if (aa + 1 == match) {
			printf("%d ", j - 1);
			match--;
		} else del[j] = 0;
	}
	printf("\n");
}
int main() {
	int T;
	//freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}
