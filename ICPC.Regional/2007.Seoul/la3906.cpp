// 2007 Seoul: Signals
// ACM-ICPC Live Archive 3906
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> as0, as1;
char s[2][1000];
int p;
bool isletter(char ch) {
	return ch >= 'a' && ch <= 'z';
}
vector<string> dfs(int idx) {
	vector<string> a[30], t1, t2;
	int i, j, uu = 0;
	a[0].push_back("");
	for (;;) {
		if (s[idx][p] == ')') {
			p++;
			break;
		} else if (isletter(s[idx][p])) {
			for (i = 0; i < (int) a[uu].size(); i++)
				a[uu][i] += s[idx][p];
			p++;
		} else if (s[idx][p] == '|') {
			uu++, p++;
			a[uu].push_back("");
		} else if (s[idx][p] == '(') {
			p++;
			t1 = dfs(idx);
			t2.clear();
			for (i = 0; i < (int) a[uu].size(); i++)
				for (j = 0; j < (int) t1.size(); j++)
					t2.push_back(a[uu][i] + t1[j]);
			a[uu] = t2;
		} else if (s[idx][p] == '1') p++;
	}
	t1.clear();
	for (i = 0; i <= uu; i++)
		for (j = 0; j < (int) a[i].size(); j++)
			t1.push_back(a[i][j]);
	return t1;
}
bool issubset(vector<string> &as0, vector<string> &as1) {
	if (as0.size() < as1.size()) {
		int ok = 1;
		for (int i = 0; i < (int)as0.size() && ok; i++) {
			int found = 0;
			for (int j = 0; j < (int)as1.size() && !found; j++)
				if (as0[i] == as1[j]) found = 1;
			if (!found) ok = 0;
		}
		if (ok) return 1;
	}
	return 0;
}
void solve() {
	int len;
	scanf("%s%s", s[0], s[1]);
	len = strlen(s[0]);
	s[0][len] = ')';
	len = strlen(s[1]);
	s[1][len] = ')';
	p = 0;
	as0 = dfs(0);
	p = 0;
	as1 = dfs(1);
	sort(as0.begin(), as0.end());
	sort(as1.begin(), as1.end());
	as0.erase(unique(as0.begin(), as0.end()), as0.end());
	as1.erase(unique(as1.begin(), as1.end()), as1.end());
	if (as0[0] == "") as0.erase(as0.begin());
	if (as1[0] == "") as1.erase(as1.begin());
 
	if (as0 == as1) {
		printf("=\n");
		return;
	}
	if (issubset(as0, as1)) printf("<\n");
	else if (issubset(as1, as0)) printf(">\n");
	else {
		vector<string> IT;
		set_intersection(as0.begin(), as0.end(), as1.begin(), as1.end(), back_inserter(IT));
		if (IT.size() == 0) printf("0\n");
		else printf("1\n");
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}