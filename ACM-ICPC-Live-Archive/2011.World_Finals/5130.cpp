// CII 5130
// 2011 World Finals: Ancient Messages
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
#define N 300

int n, m;
char image[N][N];
int map[N][N];
bool vis[N][N];
char s[N];
char hex[16][5] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001",
		"1010", "1011", "1100", "1101", "1110", "1111" };

char hole[] = {'W', 'A', 'K', 'J', 'S', 'D'};
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
void dfs(int x, int y, int sym) {
	vis[x][y] = 1;
	map[x][y] = sym;
	for (int i = 0; i < 4; i++) {
		int nx = dx[i] + x, ny = dy[i] + y;
		if (!vis[nx][ny] && nx >= 0 && ny >= 0 && nx < n && ny < m && image[x][y] == image[nx][ny])
			dfs(nx, ny, sym);
	}

}
void solve() {
	int i, j, k, bidx, widx;
	bidx = 1, widx = 1;
	memset(vis, 0, sizeof(vis));
	memset(image, '0', sizeof(image));
	for (i = 1; i <= n; i++) {
		scanf("%s", s);
		for (j = 0, k = 1; j < m; j++) {
			int idx;
			if (s[j] >= '0' && s[j] <= '9')
				idx = s[j] - '0';
			else
				idx = s[j] - 'a' + 10;
			image[i][k++] = hex[idx][0], image[i][k++] = hex[idx][1], image[i][k++] = hex[idx][2], image[i][k++]
					= hex[idx][3];
		}
	}
	m = m * 4 + 2;
	n += 2;


	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++) {
			if (!vis[i][j]) {
				if (image[i][j] == '0') {
					dfs(i, j, -widx);
					widx++;
				} else
					dfs(i, j, bidx++);
			}
		}

	set<int> S[1000];
	vector<char> ans;
	for (i = 1; i < n; i++)
		for (j = 1; j < m; j++) {
			if (map[i][j] > 0)
				for (k = 0; k < 4; k++) {
					int nx = i + dx[k], ny = j + dy[k];
					if (map[nx][ny] < 0)
						S[map[i][j]].insert(map[nx][ny]);
				}
		}
	for (i = 1; i < bidx; i++)
		ans.push_back(hole[S[i].size()-1]);

	sort(ans.begin(), ans.end());
	for(i = 0; i< (int)ans.size();i++)
		printf("%c", ans[i]);

}
int main() {
	int ca = 1;
	freopen("in.txt", "r", stdin);
	while (scanf("%d%d", &n, &m) && n) {
		printf("Case %d: ",ca++);
		solve();
		printf("\n");

	}
}

