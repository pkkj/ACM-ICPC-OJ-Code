// 2006 Dhaka: Expression
// ACM-ICPC Live Archive 2193
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>
using namespace std;
#define N 300
 
struct NODE {
	int sgn, size;
	vector<int> v;
};
 
int idx[N];
NODE ans[N];
bool cmp1(int a, int b) {
	if (ans[a].sgn != ans[b].sgn) return ans[a].sgn > ans[b].sgn;
	return a > b;
}
 
bool cmp2(int a, int b) {
	if (ans[a].sgn != ans[b].sgn) return ans[a].sgn < ans[b].sgn;
	return a < b;
}
void solve() {
	int len, i, pre, sgn = 1, tsgn = 1, tot = 0, j, k, sum = 0;
	char cc[N], num[N];
	bool vis[N] = { 0 };
 
	gets(cc);
	gets(num);
	len = strlen(cc);
	pre = 0;
	for (i = 0; i < len; i++) {
		if (cc[i] == '#' && cc[i + 1] != '#') {
			ans[tot].sgn = sgn * tsgn;
			ans[tot].size = i - pre + 1;
			ans[tot].v.clear();
			tot++;
		} else if (cc[i] == '(') {
			sgn *= tsgn;
			tsgn = 1;
			pre = i + 1;
		} else if (cc[i] == ')') {
			for (j = i;; j--)
				if (cc[j] == '(' && !vis[j]) break;
			if (j > 0 && cc[j - 1] == '-') sgn *= -1;
			vis[j] = 1;
			pre = i + 1;
		} else if (cc[i] == '+') {
			tsgn = 1;
			pre = i + 1;
		} else if (cc[i] == '-') {
			tsgn = -1;
			pre = i + 1;
		}
	}
 
	for (i = 0; i < tot; i++)
		idx[i] = i;
 
	len = strlen(num);
 
	// Arrange the positive
	i = 0;
	sort(num, num + len, greater<char> ());
	sort(idx, idx + tot, cmp1);
	while (1) {
		int pos = -1, max = 0;
		for (j = 0; j < tot; j++) {
			if (ans[idx[j]].sgn == -1) break;
			int remain = ans[idx[j]].size - (int) ans[idx[j]].v.size();
			if (remain > max) pos = j, max = remain;
		}
		if (pos == -1) break;
		ans[idx[pos]].v.push_back(num[i++] - '0');
	}
	// Arrange the negative
	i = 0;
	sort(idx, idx + tot, cmp2);
	sort(num, num + len);
	while (1) {
		int pos = -1, max = 0;
		for (j = 0; j < tot; j++) {
			if (ans[idx[j]].sgn == 1) break;
			int remain = ans[idx[j]].size - (int) ans[idx[j]].v.size();
			if (remain > max) pos = j, max = remain;
		}
		if (pos == -1) break;
		ans[idx[pos]].v.push_back(num[i++] - '0');
	}
	for (i = k = 0; i < tot; i++) {
		int x = 0;
		for (j = 0; j < (int) ans[i].v.size(); j++) {
			while (cc[k] != '#')
				k++;
			cc[k] = ans[i].v[j] + '0';
			x = x * 10 + ans[i].v[j];
		}
		sum += ans[i].sgn * x;
	}
 
	printf("%s\n%d\n", cc, sum);
}
int main() {
	int T, ca = 1;
	scanf("%d\n", &T);
	while (T--) {
		printf("Case %d:\n", ca++);
		solve();
	}
	return 0;
}