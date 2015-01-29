// CII 4513
// 2009 Southwestern Europe: Stammering Aliens
#include <cstdio>
#include <cstring>
#define N 40005
#define A1 68537LL
#define A2 58493LL
#define M1 73757LL
#define M2 62453LL
typedef long long ll;
struct NODE {
	ll v2;
	int next, cnt;
};
int G[M1], tot, n, m, right;
NODE E[N * 2];
char s[N];
 
int find(ll v1, ll v2) {
	for (int i = G[v1]; ~i; i = E[i].next)
		if (E[i].v2 == v2) return i;
	return -1;
}
int addnode(ll v1, ll v2) {
	int add = find(v1, v2);
	if (add == -1) {
		int pos = v1;
		NODE nn = { v2, G[pos], 1 };
		E[tot] = nn;
		G[pos] = tot++;
		return 1;
	}
	return ++E[add].cnt;
}
int check(int k) {
	int i, ok = 0;
	ll v1, v2, base1, base2;
	tot = 0;
	memset(G, -1, sizeof(G));
	v1 = v2 = 0, base1 = base2 = 1;
	for (i = 1; i <= k - 1; i++) {
		base1 = (base1 * A1) % M1;
		base2 = (base2 * A2) % M2;
	}
	for (i = 1; i <= k; i++) {
		v1 = (v1 * A1 + s[i]) % M1;
		v2 = (v2 * A2 + s[i]) % M2;
	}
	for (i = 1; i <= n - k + 1; i++) {
		if (addnode(v1, v2) >= m) {
			right = i;
			ok = 1;
		}
		ll t = base1 * s[i] % M1;
		v1 = ((((v1 - t) + M1) % M1) * A1 + s[i + k]) % M1;
		t = base2 * s[i] % M2;
		v2 = ((((v2 - t) + M2) % M2) * A2 + s[i + k]) % M2;
	}
	return ok;
}
 
void solve() {
	int i, cnt[30] = { 0 }, ok = 0, ans, ri;
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (i = 1; i <= n; i++) {
		s[i] = s[i] - 'a' + 1;
		cnt[s[i] - 1]++;
	}
	for (i = 0; i < 26; i++)
		if (cnt[i] >= m) ok = 1;
	if (!ok) {
		printf("none\n");
		return;
	}
	int l = 1, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid, ri = right, l = mid + 1;
		} else r = mid - 1;
	}
	printf("%d %d\n", ans, ri-1);
}
int main() {
	while (scanf("%d", &m) && m)
		solve();
	return 0;
}
