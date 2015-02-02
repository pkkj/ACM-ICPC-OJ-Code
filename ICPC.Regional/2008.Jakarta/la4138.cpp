// 2008 Jakarta: Anti Brute Force Lock
// ACM-ICPC Live Archive 4138
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 505
struct EDGE {
	int a, b, w;
	bool operator <(const EDGE &e) const {
		return w < e.w;
	}
	EDGE() {
	}
	EDGE(int a, int b, int w) :
		a(a), b(b), w(w) {
	}
};
char ch[N][5];
int iabs(int x) {
	return x < 0 ? -x : x;
}
int dis(char *a, char *b) {
	int ret = 0, i;
	for (i = 0; i < 4; i++) {
		ret += min(iabs((int)a[i] - (int)b[i]), 10 - iabs((int)a[i] - (int)b[i]));
	}
	return ret;
}
EDGE el[N * N];
// Union set
int fa[N];
void init(int n) {
	for (int i = 0; i < n; i++)
		fa[i] = i;
}
int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
// End of union set
void solve() {
	int n, i, j, tot = 0,ans = 100000;
	scanf("%d", &n);
	char zero[] = "0000";
	for (i = 0; i < n; i++)
		scanf("%s", ch[i]);
	for (i = 0; i < n; i++)
	{
		int k = dis(ch[i], zero);
		if (k < ans) ans = k;
		for (j = i + 1; j < n; j++)
			el[tot++] = EDGE(i, j, dis(ch[i], ch[j]));
	}
	sort(el, el + tot);
	i = j = 0;
	init(n);
	while (j < n - 1) {
		int x = find(el[i].a);
		int y = find(el[i].b);
		if (x != y) {
			j++;
			ans += el[i].w;
			fa[x] = y;
		}
		i++;
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}