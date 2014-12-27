// CII 4487
// 2009 Wuhan: Exclusive-OR
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20005
int n, Q;
int fa[N], ve[N];
void init() {
	for (int i = 0; i <= n + 1; i++)
		fa[i] = i;
	memset(ve, 0, sizeof(ve));
}
int find(int a) {
	int pref = fa[a];
	if (fa[a] == a) return a;
	fa[a] = find(fa[a]);
	ve[a] = ve[pref] ^ ve[a];
	return fa[a];
}
bool uniset(int a, int b, int v) {
	int pa = find(a), pb = find(b);
	if (pa == pb) {
		if ((ve[a] ^ ve[b]) != v) return 0;
	} else {
		if (pa ==n) swap(pa, pb);
		fa[pa] = pb;
		ve[pa] = v ^ ve[a] ^ ve[b];
	}
	return 1;
}
int K, num[20];
int query() {
	bool g[20] = { 0 };
	int i, j, ans = 0, ff, ret;
	for (i = 0; i < K; i++) {
		int sz = 1;
		if (g[i]) continue;
		ff = find(num[i]), ans ^= ve[num[i]];
		g[i] = 1;
		for (j = i + 1; j < K; j++) {
			if (g[j]) continue;
			ret = find(num[j]);
			if (ret == ff) g[j] = 1, sz++, ans ^= ve[num[j]];
		}
		if (ff != n && sz % 2 == 1) return -1;
	}
	return ans;
}
void solve() {
	int T = 1, i, a, b, v;
	bool ig = 0;
	char s[500];
	init();
	while (Q--) {
		scanf("%s ", s);
		if (s[0] == 'Q') {
			scanf("%d", &K);
			for (i = 0; i < K; i++)
				scanf("%d", &num[i]);
 
			if (!ig) {
				int ret = query();
				if (ret == -1) printf("I don't know.\n");
				else printf("%d\n", ret);
			}
		} else {
			int blank = 0;
			gets(s);
			if (ig) continue;
			for (i = 0; i < (int) strlen(s); i++)
				if (s[i] == ' ') blank++;
			if (blank == 1) sscanf(s, "%d%d", &a, &v), b = n;
			else sscanf(s, "%d%d%d", &a, &b, &v);
			if (!uniset(a, b, v)) {
				printf("The first %d facts are conflicting.\n", T);
				ig = 1;
			}
			T++;
		}
	}
}
int main() {
 
	int ca = 1;
	while (scanf("%d%d\n", &n, &Q) && n) {
		printf("Case %d:\n", ca++);
		solve();
		printf("\n");
	}
	return 0;
}
