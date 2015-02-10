// 2009 Southwestern Europe: Haunted Graveyard
// ACM-ICPC Live Archive 4509
// POJ 3878
#include <cstdio>
#include <cstring>

const int INF = 1 << 30;
const int SIZE = 30 + 1;
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

struct HOLE{
	int dx, dy, dt;
	void read(){
		scanf("%d%d%d", &dx, &dy, &dt);
	}
};

int nrow, ncol, d[SIZE * SIZE + 5];
bool stones[SIZE][SIZE];
HOLE holes[SIZE][SIZE];

int bellman_ford(int s, int t) {
	int n = nrow * ncol, relaxed;
	for (int i = 1; i < n; i++) d[i] = INF;
	d[s] = 0;
	for (int k = 0; k < n; k++) {
		relaxed = false;
		// Pay attention, no calculation for the exit, whose id is (n-1).
		for (int i = 0; i < n - 1; i++){
			if (d[i] == INF)
				continue;
			int cx = i / ncol, cy = i  % ncol;
			if (holes[cx][cy].dx != -1){
				int dest = holes[cx][cy].dx * ncol + holes[cx][cy].dy;
				if (d[dest] > d[i] + holes[cx][cy].dt) {
					d[dest] = d[i] + holes[cx][cy].dt;
					relaxed = true;
				}
			}
			else{
				for (int j = 0; j < 4; j++){
					int nx = cx + dx[j], ny = cy + dy[j];
					if (nx < 0 || ny < 0 || nx >= nrow || ny >= ncol || stones[nx][ny])
						continue;
					int dest = nx * ncol + ny;
					if (d[dest] > d[i] + 1) {
						d[dest] = d[i] + 1;
						relaxed = true;
					}
				}
			}
		}
		if (!relaxed) break;
	}
	return relaxed ? -INF : d[t];
}

int main(){
	while (scanf("%d%d", &nrow, &ncol) && nrow){
		int nstone, nhole, x, y;
		memset(holes, -1, sizeof(holes));
		memset(stones, 0, sizeof(stones));

		scanf("%d", &nstone);
		for (int i = 0; i < nstone; i++){
			scanf("%d%d", &x, &y);
			stones[x][y] = true;
		}
		scanf("%d", &nhole);
		for (int i = 0; i < nhole; i++){
			scanf("%d%d", &x, &y);
			holes[x][y].read();
		}

		int ans = bellman_ford(0, nrow * ncol - 1);
		if (ans == -INF) printf("Never\n");
		else if (ans == INF) printf("Impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}

