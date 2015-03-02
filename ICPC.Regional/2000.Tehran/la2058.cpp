// 2000 Tehran: Cashier Employment
// ACM-ICPC Live Archive 2058
// POJ 1275

// Use Bellman-Ford shortest path algorithm to resolve a system of difference constraints

#include <cstdio>
#include <cstring>
using namespace std;

const int HOUR = 24;
const int INF = 1 << 20;

struct EDGE{
	int x, y, w;
	EDGE(){}
	EDGE(int x, int y, int w) :x(x), y(y), w(w){}
};

int need[HOUR + 1], start[HOUR + 1];

int bellman_ford(int total){
	int ne = 0, flag, dis[HOUR + 1] = { 0 };
	EDGE edges[HOUR * 5];

	// Construct the graph with the constraints
	for (int i = 1; i <= HOUR; i++){
		edges[ne++] = EDGE(i, i - 1, 0);
		edges[ne++] = EDGE(i - 1, i, -start[i]);
		if (i - 8 >= 0)
			edges[ne++] = EDGE(i, i - 8, need[i]);
		else
			edges[ne++] = EDGE(i, i + 16, need[i] - total);
	}
	edges[ne++] = EDGE(HOUR, 0, total);

	for (int i = 1; i <= HOUR; i++)
		dis[i] = INF;
	for (int i = 0; i <= HOUR; i++) {
		flag = 1;
		for (int j = 0; j < ne; j++){
			int v = dis[edges[j].x] + edges[j].w;
			if (v > dis[edges[j].y])
				dis[edges[j].y] = v, flag = 0;
		}
		if (flag) break;
	}
	return flag;
}

int main(){
	int T, x, n;
	scanf("%d", &T);
	while (T--){
		for (int i = 1; i <= HOUR; i++)
			scanf("%d", &need[i]);

		memset(start, 0, sizeof(start));
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			scanf("%d", &x);
			start[x + 1]++;
		}

		int left = 0, right = n, ans = -1;
		while (left <= right){
			int mid = (left + right) / 2;
			if (bellman_ford(mid)){
				ans = mid;
				right = mid - 1;
			}
			else{
				left = mid + 1;
			}
		}

		ans == -1 ? printf("No Solution\n") : printf("%d\n", ans);
	}
	return 0;
}
