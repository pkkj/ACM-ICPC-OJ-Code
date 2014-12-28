// CII 4427
// 2008 Tehran: deltree
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;
#define N 10000
 
struct EDGE {
	int b, next;
	string name;
};
int G[N], tot, id, size[N], fa[N];
EDGE E[N];
 
char cmd[10000];
int curdir;
void addedge(int a, int b, string s) {
	EDGE e = { b, G[a], s };
	G[a] = tot;
	E[tot++] = e;
}
void init() {
	memset(G, -1, sizeof(G));
	memset(size, -1, sizeof(size));
	tot = id = 0;
	curdir = id++;
}
void parsedir() {
	int len, blank, i;
	char tmp[30];
	string s;
	len = strlen(cmd);
	blank = len;
	for (i = 0; i < len; i++)
		if (cmd[i] == ' ') {
			blank = i;
			break;
		}
	for (i = 0; i < blank; i++)
		tmp[i] = cmd[i];
	tmp[i] = 0;
	s = tmp;
	addedge(curdir, id, s);
	fa[id] = curdir;
	if (blank != len) {
		int sz;
		sscanf(cmd + blank, "%d", &sz);
		size[id] = sz;
	}
	id++;
}
 
void changedir(char *cmd) {
	int i, len, j;
	string s;
	len = strlen(cmd);
	i = 0;
	if (cmd[i] == '\\') {
		i++;
		curdir = 0;
	}
	for (; i < len; i++) {
		if (cmd[i] == '\\') {
			if (s == "..") curdir = fa[curdir];
			else {
				int found = 0;
				for (j = G[curdir]; ~j; j = E[j].next)
					if (E[j].name == s) {
						found = 1;
						break;
					}
				if (found) curdir = E[j].b;
				else {
					addedge(curdir, id, s);
					fa[id] = curdir;
					curdir = id;
					id++;
				}
			}
			s = "";
		} else s += cmd[i];
	}
	if (s == "..") curdir = fa[curdir];
	else if (s != "") {
		int found = 0;
		for (j = G[curdir]; ~j; j = E[j].next)
			if (E[j].name == s) {
				found = 1;
				break;
			}
		if (found) curdir = E[j].b;
		else {
			addedge(curdir, id, s);
			fa[id] = curdir;
			curdir = id;
			id++;
		}
	}
}
int dfs(int x) {
	int i, ans = 0;
	if (size[x] != -1) ans += size[x];
	for (i = G[x]; ~i; i = E[i].next)
		ans += dfs(E[i].b);
	return ans;
}
int solve() {
	int read = 1, len;
	init();
	while (1) {
		if (read) gets(cmd);
		read = 1;
		len = strlen(cmd);
		if (len == 0) continue;
		if (cmd[len - 1] == ' ') cmd[len - 1] = 0;
		if (cmd[0] == '>' && cmd[1] == 'e') return 0;
		if (cmd[0] == '>' && cmd[1] == 'd' && cmd[2] == 'i') {
			read = 0;
			while (1) {
				gets(cmd);
				len = strlen(cmd);
				if (cmd[len - 1] == ' ') cmd[len - 1] = 0;
				if (cmd[0] == '>')
					break;
				parsedir();
			}
		} else if (cmd[0] == '>' && cmd[1] == 'd' && cmd[2] == 'e') break;
		else if (cmd[0] == '>' && cmd[1] == 'c') changedir(cmd + 4);
	}
	changedir(cmd + 9);
	printf("%d\n", dfs(curdir));
	return 1;
}
int main() {
	while (solve())
		;
	return 0;
}
