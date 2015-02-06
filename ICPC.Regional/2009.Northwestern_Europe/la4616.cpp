// CII 4616
// 2009 Northwestern Europe: Settlers of Catan
#include <cstdio>
#include <cstring>

#define N 10005
#define M 2005
#define K 1000
#define INF 10000
#define DIR 6

int dir[DIR][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { -1, 0 }, { 0, -1 },
		{ 1, -1 } };
int ans[N];
int stage[M][M]; // The level of spiral
int resCounter[DIR];
int resource[M][M];
int coord(int num) {
	return num + K;
}

void assignResource(int id, int x, int y, int resId) {
	resource[x][y] = ans[id] = resId;
	resCounter[resId]++;
}

void preprocess() {
	memset(stage, -1, sizeof(stage));
	memset(resCounter, 0, sizeof(resCounter));
	memset(resource, -1, sizeof(resource));
	stage[coord(0)][coord(0)] = 0;
	stage[coord(1)][coord(0)] = 1;
	assignResource(1, coord(0), coord(0), 1);
	assignResource(2, coord(1), coord(0), 2);
	int curx = coord(1), cury = coord(0), curStage = 1;
	for (int i = 3; i < N; i++) {
		// Search the next cell in counter-clockwise way
		int nextx = INF, nexty = INF;
		for (int j = 0; j < DIR; j++) {
			int tmpx = curx + dir[j][0], tmpy = cury + dir[j][1];
			if (stage[tmpx][tmpy] != -1)
				continue;
			// Determine whether it's the correct next cell.
			// The next cell must be:
			//   1) Not visited before.
			//   2) Adjacent to a visited cells in inner spiral
			bool adjToLowerStage = false;
			for (int k = 0; k < DIR && !adjToLowerStage; k++) {
				int adjx = tmpx + dir[k][0], adjy = tmpy + dir[k][1];
				if (stage[adjx][adjy] == curStage - 1)
					adjToLowerStage = true;
			}
			if (adjToLowerStage) {
				nextx = tmpx, nexty = tmpy;
				break;
			}
		}
		// Cannot find the next cell, we need to expand to the next spiral
		if (nextx == INF) {
			curStage++;
			nextx = curx + 1, nexty = cury;
		}
		curx = nextx, cury = nexty;
		stage[curx][cury] = curStage;

		// Find the available resource
		bool usedResource[6];
		memset(usedResource, 0, sizeof(usedResource));
		for (int j = 0; j < 6; j++) {
			int tmpx = curx + dir[j][0], tmpy = cury + dir[j][1];
			if (resource[tmpx][tmpy] != -1) {
				usedResource[resource[tmpx][tmpy]] = true;
			}
		}
		// Allocate the resource to the cell
		int localAns = INF, ansCounter = INF;
		for (int j = 1; j <= 5; j++) {
			if (!usedResource[j] && resCounter[j] < ansCounter) {
				localAns = j, ansCounter = resCounter[j];
			}
		}
		assignResource(i, curx, cury, localAns);
		// printf("(%d %d) %d = %d\n", curx - K, cury - K, i, localAns);
	}
}

int main() {
	preprocess();
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}

