// 2008 Jakarta: Bonus Treasure
// ACM-ICPC Live Archive 4139
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
void print(long long s, long long l, long long r) {
	long long i, p, q;
	if (s == 1) {
		if (l == 0 && r == 1) printf("()");
		else if (l == r && l == 0) printf("(");
		else printf(")");
		return;
	}
	if (l == 0) {
		printf("(");
		l++;
	}
	p = 1LL;
	for (i = 1; i < s; i++) {
		q = p + (1LL << i) - 1LL;
		if (l > q || r < p) {
			p += (1LL << i);
			continue;
		}
		print(i, max(0LL, l - p), min(r - p, (1LL << i) - 1LL));
		p += (1LL << i);
	}
	if (r == (1LL << s) - 1) printf(")");
}
 
int main() {
	long long s, l, r;
	while (scanf("%lld%lld%lld", &s, &l, &r) && s) {
		print(s, l, l + r - 1);
		printf("\n");
	}
	return 0;
}