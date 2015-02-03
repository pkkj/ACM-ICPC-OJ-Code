// 2007 Beijing: Difficult Melody
// ACM-ICPC Live Archive 4026
#include <cstdio>
#include <cstring>
#define M 105
#define N 300000
typedef long long ll;
struct NODE {
	ll v2;
	int next, idx, cy, cn;
};
#define A1 68537LL
#define A2 58493LL
#define M1 103757LL
#define M2 62453LL
 
NODE E[N];
int G[M1], tot;
int P, Q, n, m, k;
char ans[M], tmp[M], s[M], sym[5];
void init() {
	tot = 0;
	memset(G, -1, sizeof(G));
}
 
int find(ll v1, ll v2) {
	for (int i = G[v1]; ~i; i = E[i].next)
		if (E[i].v2 == v2) return i;
	return -1;
}
void addnode(ll v1, ll v2, int idx, int pos, bool ok) {
	int ret = find(v1, v2), i, j;
	NODE ce;
	if (ret == -1) {
		NODE nn = { v2, G[v1], idx, 0, 0 };
		if (ok) nn.cy++;
		else nn.cn++;
		ce = E[tot] = nn;
		G[v1] = tot++;
	} else {
		if (E[ret].idx == idx) return;
		if (ok) E[ret].cy++;
		else E[ret].cn++;
		ce = E[ret];
	}
	if (ce.cn + ce.cy >= m) {
		double c1 = (double) Q / P;
		double c2 = (double) ce.cy / (ce.cn + ce.cy);
		if (c2 <= c1) {
			if (c2 < c1 || c1 == c2 && ce.cn + ce.cy > P) {
				Q = ce.cy, P = (ce.cn + ce.cy);
				for (i = pos, j = 0; i < pos + k; i++)
					ans[j++] = s[i];
				ans[j] = 0;
			} else if (c1 == c2 && ce.cn + ce.cy == P) {
				for (i = pos, j = 0; i < pos + k; i++)
					tmp[j++] = s[i];
				tmp[j] = 0;
				if (strcmp(tmp, ans) < 0) strcpy(ans, tmp);
			}
		}
 
	}
}
 
void hash(int idx, bool ok) {
	int i, len;
	ll v1, v2, base1, base2;
	v1 = v2 = 0, base1 = base2 = 1;
	len = strlen(s);
	if (len < k) return;
	for (i = 0; i < k - 1; i++) {
		base1 = (base1 * A1) % M1;
		base2 = (base2 * A2) % M2;
	}
	for (i = 0; i < k; i++) {
		v1 = (v1 * A1 + (s[i] - 'A' + 1)) % M1;
		v2 = (v2 * A2 + (s[i] - 'A' + 1)) % M2;
	}
	for (i = 0; i < len - k + 1; i++) {
		addnode(v1, v2, idx, i, ok);
		ll t = base1 * (s[i] - 'A' + 1) % M1;
		v1 = ((((v1 - t) + M1) % M1) * A1 + (s[i + k] - 'A' + 1)) % M1;
		t = base2 * (s[i] - 'A' + 1) % M2;
		v2 = ((((v2 - t) + M2) % M2) * A2 + (s[i + k] - 'A' + 1)) % M2;
	}
 
}
void solve() {
	int i;
	scanf("%d%d", &m, &k);
	init();
	P = 1, Q = 11;
	for (i = 0; i < n; i++) {
		bool ok;
		scanf("%s%s", s, sym);
		if (sym[0] == 'Y') ok = 1;
		else ok = 0;
		hash(i, ok);
	}
	if (P == 1 && Q == 11) printf("No solution\n");
	else printf("%s\n", ans);
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}