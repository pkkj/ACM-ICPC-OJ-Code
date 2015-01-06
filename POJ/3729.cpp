// POJ 3729
// POJ Monthly Contest – 2009.04.05: Facer’s string
#include <cstdio>
#include <cstring>
#define N 50105
#define A1 68537LL
#define A2 58493LL
#define M1 103757LL
#define M2 62453LL
typedef long long ll;
struct NODE {
	ll v2;
	int next;
};
int n, m, k, s1[N], s2[N];
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
 
int ask(int k) {
	int ans = 0, i;
	ll v1, v2, base1, base2;
	init();
	v1 = v2 = 0, base1 = base2 = 1;
	for (i = 1; i <= k - 1; i++) {
		base1 = (base1 * A1) % M1;
		base2 = (base2 * A2) % M2;
	}
 
	for (i = 1; i <= k; i++) {
		v1 = (v1 * A1 + s2[i]) % M1;
		v2 = (v2 * A2 + s2[i]) % M2;
	}
	for (i = 1; i <= m - k + 1; i++) {
		addnode(v1, v2);
		ll t = base1 * s2[i] % M1;
		v1 = ((((v1 - t) + M1) % M1) * A1 + s2[i + k]) % M1;
		t = base2 * s2[i] % M2;
		v2 = ((((v2 - t) + M2) % M2) * A2 + s2[i + k]) % M2;
	}
 
	v1 = v2 = 0;
	for (i = 1; i <= k; i++) {
		v1 = (v1 * A1 + s1[i]) % M1;
		v2 = (v2 * A2 + s1[i]) % M2;
	}
 
	for (i = 1; i <= n - k + 1; i++) {
		if (find(v1, v2)) ans++;
		ll t = base1 * s1[i] % M1;
		v1 = ((((v1 - t) + M1) % M1) * A1 + s1[i + k]) % M1;
		t = base2 * s1[i] % M2;
		v2 = ((((v2 - t) + M2) % M2) * A2 + s1[i + k]) % M2;
	}
	return ans;
}
void solve() {
	int i;
	for (i = 1; i <= n; i++) {
		scanf("%d", s1 + i);
		s1[i]++;
	}
	for (i = 1; i <= m; i++) {
		scanf("%d", s2 + i);
		s2[i]++;
	}
	printf("%d\n", ask(k) - ask(k + 1));
}
 
int main() {
	//freopen("in.txt", "r", stdin);
	while (~scanf("%d%d%d", &n, &m, &k))
		solve();
	return 0;
}
