// Rocky Mountain 2005: Smallest Difference
// ACM-ICPC Live Archive 3341
// POJ 2718

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
struct NUM {
	int v, u;
	bool operator <(const NUM &x) const {
		return v < x.v;
	}
};

int getdigit(char ch) {
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	return -1;
}

int mabs(int x) {
	return x < 0 ? -x : x;
}

int solve() {
	char cmd[100], n1[10], n2[10];
	vector<NUM> nl;
	NUM tmp;
	int i, j, p1, p2, ans = 10000000, pp1, pp2;
	tmp.u = 0;

	gets(cmd);
	for (i = 0; cmd[i]; i++) {
		int x = getdigit(cmd[i]);
		if (x != -1) {
			tmp.v = x;
			nl.push_back(tmp);
		}

	}
	sort(nl.begin(), nl.end());
	if (nl.size() == 2) {
		return nl[1].v - nl[0].v;
	}
	p1 = p2 = 0;
	if (nl.size() % 2) {
		if (nl[0].v)
			n1[p1++] = '0' + nl[0].v, nl[0].u = 1;
		else
			n1[p1++] = '0' + nl[1].v, nl[1].u = 1;
	}
	for (i = 0; i < (int) nl.size(); i++) {
		if (nl[i].u || nl[i].v == 0 && p1 == 0)
			continue;
		nl[i].u = 1;
		n1[p1++] = '0' + nl[i].v;
		for (j = 0; j < (int) nl.size(); j++) {
			if (nl[j].u || nl[j].v == 0 && p2 == 0)
				continue;
			nl[j].u = 1, n2[p2++] = '0' + nl[j].v;
			pp1 = p1, pp2 = p2;
			{
				int k, l = 0, r = nl.size() - 1;
				for (k = 0; k < nl.size() / 2 - 1; k++) {
					while (nl[l].u)
						l++;
					n1[p1++] = '0' + nl[l++].v;
					while (nl[r].u)
						r--;
					n2[p2++] = '0' + nl[r--].v;
				}
				n1[p1] = 0, n2[p2] = 0;
				int aa, bb;
				sscanf(n1, "%d", &aa);
				sscanf(n2, "%d", &bb);
				if (mabs(aa - bb) < ans)
					ans = mabs(aa - bb);
			}
			p1 = pp1, p2 = pp2;
			nl[j].u = 0, p2--;
		}
		nl[i].u = 0, p1--;
	}

	return ans;
}
int main() {
	int T;
	scanf("%d\n", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}
