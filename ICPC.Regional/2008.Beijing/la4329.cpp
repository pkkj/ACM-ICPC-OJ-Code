// 2008 Beijing: Ping pong
// ACM-ICPC Live Archive 4329
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lowbit(x) (x&(x^(x-1)))
#define N 20005
 
long long C[N], ans[2][N];
int n;
void modify(int pos, int d) {
	while (pos <= n)
		C[pos] += d, pos += lowbit(pos);
}
int query(int pos) {
	int sum = 0;
	while (pos > 0)
		sum += C[pos], pos -= lowbit(pos);
	return sum;
}
int in[N], idx[N], rank[N];
bool cmpv(const int &a, const int &b) {
	return in[a] < in[b];
}
void solve() {
	int i, j;
	long long ret = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &in[i]), idx[i] = i;
	sort(idx, idx + n, cmpv);
	for (i = 0; i < n; i++)
		rank[idx[i]] = i + 1;
	memset(ans, 0, sizeof(ans));
	memset(C, 0, sizeof(C));
	for (i = 0; i < n; i++) {
		j = rank[i];
		ans[0][i] = query(j - 1);
		modify(j, 1);
	}
	memset(C, 0, sizeof(C));
	for (i = 0; i < n; i++) {
		j = rank[i];
		ans[1][i] = query(j - 1);
		modify(j, ans[0][i]);
	}
	for (i = 0; i <= n; i++)
		ret += ans[1][i];
	reverse(rank, rank + n);
	memset(ans, 0, sizeof(ans));
	memset(C, 0, sizeof(C));
	for (i = 0; i < n; i++) {
		j = rank[i];
		ans[0][i] = query(j - 1);
		modify(j, 1);
	}
	memset(C, 0, sizeof(C));
	for (i = 0; i < n; i++) {
		j = rank[i];
		ans[1][i] = query(j - 1);
		modify(j, ans[0][i]);
	}
	for (i = 0; i <= n; i++)
		ret += ans[1][i];
	printf("%lld\n", ret);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}