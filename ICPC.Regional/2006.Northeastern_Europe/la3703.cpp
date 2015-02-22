// 2006 Northeastern Europe: Billing Tables
// ACM-ICPC Live Archive 3703

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
#define N 105
#define M 20005
#define LEN 11
#define AA 25
#define VAR -1
#define INV -2
#define MIN "00000000000"
#define MAX "99999999999"
struct ITEM {
	string l, r;
	int idx;
};

struct ANS {
	string prefix;
	int idx;
	ANS() {
	}
	ANS(string prefix, int idx) :
			prefix(prefix), idx(idx) {
	}
};

ITEM item[N];
ANS al[M];
map<string, int> MAP;
char list[N][AA];
int aid, n;

string fill(const string s, char ch) {
	string ans = s;
	int len = s.size();
	while (len < LEN)
		ans += ch, len++;
	return ans;
}

int cover(string prefix) {
	int i, ans = 0;
	string cl = MAX, cr = MIN, pl, pr;
	pl = fill(prefix, '0');
	pr = fill(prefix, '9');
	for (i = 1; i <= n; i++) {
		if (pr < item[i].l || item[i].r < pl)
			continue;
		if (ans == 0)
			ans = item[i].idx;
		else if (ans != item[i].idx)
			return VAR;
		cl = min(cl, item[i].l);
		cr = max(cr, item[i].r);
		if (cl <= pl && pr <= cr)
			return ans;
	}
	if (ans == 0)
		return INV;
	return VAR;
}

void dfs(string prefix) {
	char ch;
	int ret = cover(prefix);
	if (prefix == "" || ret == VAR) {
		for (ch = '0'; ch <= '9'; ch++)
			dfs(prefix + ch);
	} else if (ret != INV)
		al[aid++] = ANS(prefix, ret);
}

int main() {
	int begin = 1;
	while (~scanf("%d", &n)) {
		char tmp[10], beg[AA], end[AA], title[AA];
		int i, j, tot = 1;

		if (begin)
			begin = 0;
		else
			printf("\n");

		MAP.clear();
		for (i = 1; i <= n; i++) {
			scanf("%s%s%s%s", beg, tmp, end, title);
			item[i].l = string(beg);
			item[i].r = string(end);
			j = item[i].l.length() - item[i].r.length() - 1;
			while (item[i].r.length() < item[i].l.length())
				item[i].r = item[i].l[j--] + item[i].r;
			if (MAP[string(title)] == 0) {
				MAP[string(title)] = tot;
				strcpy(list[tot++], title);
			}
			if (string(title) == "invalid")
				item[i].idx = INV;
			else
				item[i].idx = MAP[string(title)];
			item[i].l = fill(item[i].l, '0');
			item[i].r = fill(item[i].r, '9');
		}
		aid = 0;
		dfs("");
		printf("%d\n", aid);
		for (i = 0; i < aid; i++)
			printf("%s %s\n", al[i].prefix.c_str(), list[al[i].idx]);
	}
	return 0;
}
