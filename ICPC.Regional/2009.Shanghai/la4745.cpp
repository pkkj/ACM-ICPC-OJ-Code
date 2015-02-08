// 2009 Shanghai: Compressed String
// ACM-ICPC Live Archive 4745
#include <cstdio>
#include <cstring>
#define N 25
typedef long long ll;
#define INF __LONG_LONG_MAX__
#define MOD 402653189LL
char s1[N], s2[N];
ll mid, DD, limit;
bool isletter(char c) {
	return c >= 'a' && c <= 'z';
}
bool isdigit(char c) {
	return c >= '0' && c <= '9';
}
ll hash(char *s, int begin, int end, ll &pos) {
	int i, j, pn, tb, te, ba;
	ll thash1, thash2, rep, ans = 0, tpos, sublen, dd;
	char num[N];
	for (i = begin; i <= end;) {
		if (s[i] == '[') {
			ba = 0;
			tb = i + 1;
			for (j = i;; j++) {
				if (s[j] == '[') ba++;
				else if (s[j] == ']') ba--;
				if (ba == 0 && s[j] == ']') break;
			}
			te = j - 1;
			i = j + 1;
			pn = 0;
			for (;; i++) {
				if (isdigit(s[i])) num[pn++] = s[i];
				else break;
			}
			num[pn] = 0;
			sscanf(num, "%lld", &rep);
 
			if (rep && tb <= te) {
				thash1 = hash(s, tb, te, pos);
				tpos = pos;
				ll tmid = mid;
				mid = INF;
				thash2 = hash(s, tb, te, pos);
				mid = tmid;
				sublen = pos - tpos;
				pos = tpos - sublen;
				dd = thash2 - thash1 + MOD;
				if (pos + rep * sublen <= mid) {
					ans = (ans + rep * thash1) % MOD + (rep % MOD) * (rep % MOD - 1) / 2 % MOD * dd % MOD;
					ans %= MOD;
					pos += rep * sublen;
				} else {
					ll remain = (mid - (pos - 1)) / sublen;
					ans = (ans + remain * thash1) % MOD + (remain % MOD) * (remain % MOD - 1) / 2 % MOD * dd % MOD;
					ans %= MOD;
					pos += remain * sublen;
					if (pos > mid) return ans;
					ans += hash(s, tb, te, pos);
					ans %= MOD;
					return ans;
				}
			}
		} else {
			for (;; i++) {
				if (pos > mid) return ans;
				if (isletter(s[i])) {
					ans += (s[i] - 'a' + 1) * ((pos * DD % MOD - 1 + MOD) % MOD) % MOD;
					ans %= MOD;
					pos++;
				} else break;
			}
		}
	}
	return ans;
}
int l1, l2;
 
bool check(ll mid) {
	ll dq[] = { 2, 3 };
	::mid = mid;
	for (int i = 0; i < 2; i++) {
		ll pos1 = 1, pos2 = 1, h1, h2;
		DD = dq[i];
		h1 = hash(s1, 0, l1 - 1, pos1);
		h2 = hash(s2, 0, l2 - 1, pos2);
		if (mid == INF) limit = pos1 < pos2 ? pos1 : pos2;
		if (h1 != h2) return 0;
	}
	return 1;
}
void solve() {
	ll l, r, ans;
	scanf("%s%s", s1, s2);
	l1 = strlen(s1), l2 = strlen(s2);
	if (check(INF)) printf("YES\n");
	else {
		l = 0, r = limit;
		while (l <= r) {
			mid = l + r >> 1;
			if (check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("NO %lld\n", ans + 1);
	}
}
int main() {
	int T, ca = 1;
	//freopen("in.txt", "r", stdin);
	scanf("%d\n", &T);
	while (T--) {
		printf("Case #%d: ", ca++);
		solve();
	}
	return 0;
}
