// CII 4670 - Aho–Corasick string matching algorithm
// 2009 Hefei: Dominating Patterns
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define SIZE 50000
#define N 155
#define LEN 75
int fc[SIZE], next[SIZE], suf[SIZE];
bool danger[SIZE];
char letter[SIZE], table[N][LEN];
int ans[N], n;
vector<int> idx[SIZE];
int sufchild(int x, char c) {
	int p;
	while (1) {
		p = fc[x];
		while (p && letter[p] != c)
			p = next[p];
		if (p)
			return p;
		if (x == 1)
			return 1;
		x = suf[x];
	}
}
 
void build_trie() {
	int i, p, t, len, id;
	char c, cmd[LEN];
	getchar();
	id = 1, fc[1] = 0;
	memset(danger, 0, sizeof(danger));
	memset(letter, 0, sizeof(letter));
	memset(fc, 0, sizeof(fc));
	memset(suf, 0, sizeof(suf));
	memset(next, 0, sizeof(next));
	for(i = 0;i < SIZE;i++)
		idx[i].clear();
	for (i = 0; i < n; i++) {
		scanf("%s", cmd);
		strcpy(table[i], cmd);
		len = 0, p = 1;
		while (cmd[len]) {
			c = cmd[len];
			t = fc[p];
			while (t && letter[t] != c)
				t = next[t];
			if (t > 0)
				p = t;
			else {
				id++;
				letter[id] = c, next[id] = fc[p], fc[p] = id, p = id;
			}
			len++;
			if (danger[p])
				break;
		}
		danger[p] = 1;
		idx[p].push_back(i);
	}
}
 
queue<int> Q;
void build_graph() {
	int p, x;
	suf[1] = 1, p = fc[1];
	while (p) {
		Q.push(p), suf[p] = 1;
		p = next[p];
	}
	while (!Q.empty()) {
		x = Q.front(), Q.pop();
		p = fc[x];
		while (p) {
			Q.push(p);
			suf[p] = sufchild(suf[x], letter[p]);
			p = next[p];
		}
	}
}
char text[1000005];
void scan() {
	int i, j, k, p, best = 0;
	char c;
	scanf("%s", text);
	memset(ans, 0, sizeof(ans));
	i = j = 0, p = 1;
	while (c = text[i++]) {
		p = sufchild(p, c);
		if (danger[p]) {
			for (k = 0; k < (int)idx[p].size(); k++)
				ans[idx[p][k]]++;
		}
		j++;
	}
	for (i = 0; i < n; i++)
		best = max(best, ans[i]);
	printf("%d\n", best);
	for (i = 0; i < n; i++)
		if (ans[i] == best)
			printf("%s\n", table[i]);
}
int main() {
	while (scanf("%d", &n) && n) {
		build_trie();
		build_graph();
		scan();
	}
	return 0;
}
