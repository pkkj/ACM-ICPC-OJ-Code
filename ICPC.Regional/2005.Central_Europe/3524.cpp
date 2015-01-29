// CII 3524
// 2005 Central Europe: The Cow Doctor
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define M 305
struct SET {
	long long s[5];
	int k;
	void init() {
		memset(s, 0, sizeof(s));
	}
	void setbit(int x) {
		int i, j;
		i = x >> 6, j = x & 63;
		s[i] |= (1LL << j);
	}
	bool operator ==(const SET &b) const {
		for (int i = 0; i < 5; i++)
			if (s[i] != b.s[i]) return false;
		return true;
	}
	bool operator <(const SET &b) const {
		return k > b.k;
	}
};
bool include(SET &a, SET &b) {
	for (int i = 0; i < 5; i++)
		if ((a.s[i] | b.s[i]) != a.s[i]) return false;
	return true;
}
void sunion(SET &a, SET &b) {
	for (int i = 0; i < 5; i++)
		a.s[i] |= b.s[i];
}
int n, m;
SET S[M];
void solve() {
	int i, j, x, ans = 0;
	SET mix;
	for (i = 0; i < m; i++) {
		scanf("%d", &S[i].k);
		S[i].init();
		for (j = 0; j < S[i].k; j++) {
			scanf("%d", &x);
			S[i].setbit(x - 1);
		}
	}
	sort(S, S + m);
	for (i = 0; i < m; i++) {
		mix.init();
		for (j = i + 1; j < m; j++)
			if (include(S[i], S[j]))
				sunion(mix, S[j]);
		if (mix == S[i])
			ans++;
	}
	printf("%d\n", ans);
}
int main() {
	while (scanf("%d%d", &n, &m) && n + m)
		solve();
	return 0;
}
