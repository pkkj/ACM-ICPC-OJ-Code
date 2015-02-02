// 2007 Seoul: Editor
// ACM-ICPC Live Archive 3901
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <cstring>
#define N 6000
#define A1 68537LL
#define A2 58493LL
#define M1 103757LL
#define M2 62453LL
typedef long long ll;
struct NODE {
	ll v2;
	int next;
};
int n, k, s[N];
int G[M1], tot;
NODE E[N * 2];
void init() {
	tot = 0;
	memset(G, -1, sizeof(G));
}
 
bool find(ll v1, ll v2) {
	for (int i = G[v1]; ~i; i = E[i].next)
		if (E[i].v2 == v2) return 1;
	return 0;
}
void addnode(ll v1, ll v2) {
	if (!find(v1, v2)) {
		int pos = v1;
		NODE nn = { v2, G[pos] };
		E[tot] = nn;
		G[pos] = tot++;
	}
}
 
int check(int k) {
	int i;
	ll v1, v2, base1, base2;
	init();
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
		if (find(v1, v2)) return 1;
		addnode(v1, v2);
		ll t = base1 * s[i] % M1;
		v1 = ((((v1 - t) + M1) % M1) * A1 + s[i + k]) % M1;
		t = base2 * s[i] % M2;
		v2 = ((((v2 - t) + M2) % M2) * A2 + s[i + k]) % M2;
	}
	return 0;
}
char cmd[N];
int cnt[N];
int solve() {
	int i, zero = 1, ans;
	scanf("%s", cmd);
	n = strlen(cmd);
	memset(cnt, 0, sizeof(cnt));
	for (i = 0; i < n; i++) {
		s[i + 1] = cmd[i] - 'a' + 1;
		cnt[s[i + 1]]++;
	}
	for (i = 1; i <= 26 && zero; i++)
		if (cnt[i] > 1) zero = 0;
	if (zero) return 0;
	int l = 1, r = n;
 
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid, l = mid + 1;
		} else r = mid - 1;
 
	}
	return ans;
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}