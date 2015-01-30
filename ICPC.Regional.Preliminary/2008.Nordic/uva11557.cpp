// 2008 Nordic: Code Theft
// UVA 11557
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;
#define NC 105
#define LEN 300
// Suffix Array
#define MAXN 20020
int b[MAXN], array[4][MAXN], *rank, *nrank, *sa, *nsa, height[MAXN], str[MAXN];
void make_sa(int *str, int n, int tot) {
	int i, k;
	sa = array[0], nsa = array[1], rank = array[2], nrank = array[3];
	memset(b, 0, sizeof(b));
	for (i = 0; i < n; i++)
		b[str[i]]++;
	for (i = 1; i <= tot; i++)
		b[i] += b[i - 1];
	for (i = n - 1; i >= 0; i--)
		sa[--b[str[i]]] = i;
 
	for (rank[sa[0]] = 0, i = 1; i < n; i++) {
		rank[sa[i]] = rank[sa[i - 1]];
		if (str[sa[i]] != str[sa[i - 1]]) rank[sa[i]]++;
	}
	for (k = 1; k < n && rank[sa[n - 1]] < n - 1; k *= 2) {
		for (i = 0; i < n; i++)
			b[rank[sa[i]]] = i;
 
		for (i = n - 1; i >= 0; i--)
			if (sa[i] - k >= 0) nsa[b[rank[sa[i] - k]]--] = sa[i] - k;
 
		for (i = n - k; i < n; i++)
			nsa[b[rank[i]]--] = i;
 
		for (nrank[nsa[0]] = 0, i = 1; i < n; i++) {//nsa[i]
			nrank[nsa[i]] = nrank[nsa[i - 1]];
			if (rank[nsa[i]] != rank[nsa[i - 1]] || rank[nsa[i] + k] != rank[nsa[i - 1] + k]) nrank[nsa[i]]++;
		}
		int *t = sa;
		sa = nsa;
		nsa = t;
		t = rank;
		rank = nrank;
		nrank = t;
	}
}
 
void cal_height(int *str, int n) {
	int i, j, k;
	for (i = 0, k = 0; i < n; i++) {
		if (rank[i] == 0) height[rank[i]] = 0;
		else {
			for (j = sa[rank[i] - 1]; str[i + k] == str[j + k]; k++)
				;
			height[rank[i]] = k;
			if (k > 0) k--;
		}
	}
}
 
// End of Suffix array
struct CODE {
	char name[LEN];
	vector<string> c;
	int l;
	void get() {
		char s[LEN];
		int i;
		gets(name);
		c.clear();
		while (1) {
			int b, e, len;
			string ss;
			gets(s);
			len = strlen(s);
			if (strcmp(s, "***END***") == 0) break;
			for (b = 0; b < len; b++)
				if (s[b] != ' ') break;
			for (e = len - 1; e >= 0; e--)
				if (s[e] != ' ') break;
			for (i = b; i <= e; i++) {
				if (i > b && s[i] == ' ' && s[i - 1] == ' ') continue;
				ss += s[i];
			}
			if (ss != "") c.push_back(ss);
		}
	}
 
};
int n;
CODE cc[NC];
map<string, int> line;
void solve() {
	int i, j, b, e, tot = 1, len, slen = 0;
	line.clear();
	for (i = 0; i < n; i++)
		cc[i].get();
	while (1) {
		string ss;
		char s[LEN];
		gets(s);
		if (strcmp(s, "***END***") == 0) break;
		len = strlen(s);
		for (b = 0; b < len; b++)
			if (s[b] != ' ') break;
		for (e = len - 1; e >= 0; e--)
			if (s[e] != ' ') break;
		for (i = b; i <= e; i++) {
			if (i > b && s[i] == ' ' && s[i - 1] == ' ') continue;
			ss += s[i];
		}
		if (ss != "") {
			if (line.find(ss) == line.end()) line[ss] = tot++;
			str[slen++] = line[ss];
		}
	}
	len = slen;
	str[slen++] = tot + 3;
 
	for (i = 0; i < n; i++) {
		int prelen = slen;
		for (j = 0; j < (int) cc[i].c.size(); j++) {
			if (line.find(cc[i].c[j]) != line.end()) str[slen++] = line[cc[i].c[j]];
			else str[slen++] = tot;
		}
		str[slen++] = tot + 2;
		str[slen++] = 0;
		make_sa(str, slen, tot + 5);
		cal_height(str, slen);
		int ans = 0;
		for (j = 1; j < slen; j++)
			if ((sa[j] > len && sa[j - 1] < len) || (sa[j] < len && sa[j - 1] > len)) ans = height[j] > ans ? height[j] : ans;
		cc[i].l = ans;
		slen = prelen;
	}
	int ans = 0;
	for (i = 0; i < n; i++)
		ans = max(ans, cc[i].l);
	printf("%d", ans);
	if (ans) {
		for (i = 0; i < n; i++)
			if (cc[i].l == ans)
				printf(" %s", cc[i].name);
	}
	printf("\n");
}
int main() {
	while (scanf("%d\n", &n) != EOF)
		solve();
	return 0;
}