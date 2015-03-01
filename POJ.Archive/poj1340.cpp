// 2002 Kaohsiung: The Longest Detour Problem
// POJ 1340

#include <cstdio>
#include <cstring>

const int N = 105;
const int INF = 1 << 10;

int g[N][N], path[N], dis[N], n, np;
bool vis[N];
char s[3000];
void input(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++){
			scanf("%d", &g[i][j]);
			if (g[i][j] == 0)
				g[i][j] = INF;
		}
	gets(s);
	gets(s);
	int begin = 0, len = strlen(s);
	np = 0;
	while (begin < len){
		sscanf(s + begin, "%d", &path[np++]);
		while (begin < len && s[begin] != ' ')
			begin++;
		begin++;
	}
}

void dijkstra(int s) {
	int i, min, w, next;
	memset(vis, 0, sizeof(vis));
	for (i = 1; i <= n; i++)
		dis[i] = g[s][i];
	dis[s] = 0, vis[s] = 1;

	for (i = 1; i <= n; i++) {
		min = INF;
		for (w = 1; w <= n; w++)
			if (!vis[w] && dis[w] < min) next = w, min = dis[w];
		if (min == INF) break;
		vis[next] = 1;
		for (w = 1; w <= n; w++)
			if (!vis[w] && min + g[next][w] < dis[w]) dis[w] = min + g[next][w];
	}	
}

void solve(){
	int gap = 0, localDis[N];
	localDis[path[np - 1]] = 0;
	for (int j = np - 2; j >= 0; j--)
		localDis[path[j]] = g[path[j]][path[j + 1]] + localDis[path[j + 1]];

	// Disconnect the edge in shortest path one by one. Then find the shortest path from "s".
	for (int i = 0; i < np - 1; i++){
		int tmp = g[path[i]][path[i + 1]];
		g[path[i]][path[i + 1]] = g[path[i + 1]][path[i]] = INF;

		dijkstra(path[np - 1]);
		for (int j = 0; j < np - 1; j++){
			int increase = dis[path[j]] - localDis[path[j]];
			if (increase > gap)
				gap = increase;
		}
		g[path[i]][path[i + 1]] = g[path[i + 1]][path[i]] = tmp;
	}
	printf("%d\n", gap);
}

int main(){
	int T;
	scanf("%d", &T);
	while (T--){
		input();
		solve();
	}
	return 0;
}