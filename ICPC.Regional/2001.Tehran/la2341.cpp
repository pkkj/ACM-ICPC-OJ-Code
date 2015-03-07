// Tehran 2001: Illusive Chase
// ACM-ICPC Live Archive 2341
// POJ 1071

#include <cstdio>
#include <cstring>
using namespace std;

const int N = 100 + 5;
int block[N][N], range1[N], range2[N], dir[N];
bool vis[2][N][N];

int solve(){
	int n, m, cur = 0, next = 1, move = 0;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++){
			scanf("%d", &block[i][j]);
			vis[cur][i][j] = block[i][j] ? false : true;
		}

	while (scanf("%d%d ", &range1[move], &range2[move])){
		if (!range1[move])break;
		scanf("%c", &dir[move]);
		move++;
	}

	for (int mv = move - 1; mv >= 0; mv--){
		int dx = 0, dy = 0;
		if (dir[mv] == 'R') dx = 0, dy = -1;
		if (dir[mv] == 'L') dx = 0, dy = 1;
		if (dir[mv] == 'D') dx = -1, dy = 0;
		if (dir[mv] == 'U') dx = 1, dy = 0;

		memset(vis[next], 0, sizeof(vis[next]));

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++){
				if (!vis[cur][i][j]) continue;

				for (int step = range1[mv]; step <= range2[mv]; step++){
					bool ok = true;
					for (int k = 1; k <= step && ok; k++){
						int nx = i + dx * k, ny = j + dy * k;
						if (nx < 0 || ny < 0 || nx >= n || ny >= m || block[nx][ny])
							ok = false;
					}
					if (ok) vis[next][i + dx * step][j + dy * step] = true;
				}
			}
		cur = !cur, next = !next;
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans += vis[cur][i][j];
	return ans;
}
int main(){
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}