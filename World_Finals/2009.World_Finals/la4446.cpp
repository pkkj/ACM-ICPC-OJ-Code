// 2009 World Finals: My Bad
// ACM-ICPC Live Archive 4446

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 60
struct EDGE {
	int b, next;
};
int G[N], tot, data[1005][N], num[N];
char op[N];
int ni, no, ng, nb;
EDGE E[N * N * 5];
 
int dx, ds;
void addedge(int a, int b) {
	EDGE e = { b, G[a] };
	E[tot] = e;
	G[a] = tot++;
}
int dfs(int x) {
	if (num[x] != -1) return num[x];
	int i, j, a[3], ans;
	for (j = 0, i = G[x]; ~i; i = E[i].next)
		a[j++] = dfs(E[i].b);
 
	if (op[x] == 'a') ans = a[0] & a[1];
	else if (op[x] == 'o') ans = a[0] | a[1];
	else if (op[x] == 'x') ans = a[0] ^ a[1];
	else if (op[x] == 'n') ans = !a[0];
	else ans = a[0];
	if (dx == x) {
		if (ds == 0) ans = 0;
		else if (ds == 1) ans = 1;
		else if (ds == 2) ans = !ans;
	}
	return num[x] = ans;
}
int check() {
	int i, j;
	for (i = 0; i < nb; i++) {
		memset(num, -1, sizeof(num));
		for (j = 0; j < ni; j++)
			num[j] = data[i][j];
		for (j = 0; j < no; j++)
			if (dfs(j + ni + ng) != data[i][ni + j]) return 0;
	}
	return 1;
}
 
void solve() {
	int i, j, x, y, total = 0;
	char s[30], s1[5], s2[5];
	int cnt[N] = { 0 }, a1[N], a2[N];
	memset(G, -1, sizeof(G));
	tot = 0;
	for (i = 0; i < ng; i++) {
		x = i + ni;
		gets(s);
		op[x] = s[0];
		if (s[0] == 'n') {
			sscanf(s + 3, "%d", &y);
			if (s[2] == 'g') y += ni;
			addedge(x, y - 1);
		} else {
			sscanf(s + 1, "%s%s", s1, s2);
			sscanf(s1 + 1, "%d", &y);
			if (s1[0] == 'g') y += ni;
			addedge(x, y - 1);
 
			sscanf(s2 + 1, "%d", &y);
			if (s2[0] == 'g') y += ni;
			addedge(x, y - 1);
		}
	}
	for (i = 0; i < no; i++) {
		x = i + ni + ng;
		scanf("%d", &y);
		y += ni;
		addedge(x, y - 1);
		op[x] = 0;
	}
 
	scanf("%d", &nb);
	for (i = 0; i < nb; i++)
		for (j = 0; j < ni + no; j++)
			scanf("%d", &data[i][j]);
	dx = -1;
	if (check()) {
		printf("No faults detected\n");
		return;
	}
	for (i = 0; i < ng; i++)
		for (j = 0; j < 3; j++) {
			dx = i + ni, ds = j;
			if (check()) cnt[i]++, a1[i] = i + 1, a2[i] = j;
		}
	for (i = 0; i < ng; i++)
		if (cnt[i] == 1)
			total++;
 
	if (total == 1) for (i = 0; i < ng; i++)
		if (cnt[i] == 1) {
			if (a2[i] <= 1) printf("Gate %d is failing; output stuck at %d\n", a1[i], a2[i]);
			else printf("Gate %d is failing; output inverted\n", a1[i]);
			return;
		}
	printf("Unable to totally classify the failure\n");
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d\n", &ni, &ng, &no) && ni) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
