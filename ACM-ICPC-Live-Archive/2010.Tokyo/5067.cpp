// CII 5067
// 2010 Tokyo: Membership Management
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
using namespace std;
#define N 2000
char s[2000];
int deg[2000], vis[2000], ans;
vector<int> sub[1000];
void dfs(int x) {
	vis[x] = 1;
	if (sub[x].size() == 0) ans++;
	else {
		for (int i = 0; i < (int)sub[x].size(); i++)
			if(!vis[sub[x][i]])dfs(sub[x][i]);
	}
}
int main() {
	int i, j, n;
	while (scanf("%d", &n) && n) {
		int idx = 1;
		ans = 0;
		map<string, int> m;
 
		memset(vis, 0, sizeof(vis));
		memset(deg, 0, sizeof(deg));
		gets(s);
		for (i = 0; i < n; i++) {
			string t;
			int gid;
			gets(s);
			for (j = 0; s[j] != ':'; j++)
				t += s[j];
			if (m.find(t) == m.end()) m[t] = idx++;
			gid = m[t];
			j++;
			t = "";
			for (; s[j] != '.'; j++) {
				if (s[j] == ',') {
					if (m.find(t) == m.end()) m[t] = idx++;
					sub[gid].push_back(m[t]);
					t = "";
				} else t += s[j];
			}
			if (m.find(t) == m.end()) m[t] = idx++;
			sub[gid].push_back(m[t]);
		}
		dfs(1);
		printf("%d\n", ans);
		for (i = 1; i < idx; i++)
			sub[i].clear();
	}
	return 0;
}
