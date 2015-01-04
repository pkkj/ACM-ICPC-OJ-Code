// POJ 3739 Special Squares
// PKU Campus 2009 (POJ Monthly Contest – 2009.05.17), Doraemonok
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 1050
int n1, n2, n3;
int lx[N], ly[N], sum[N][N];
struct EDGE {
	int e1, e2, next;
};
int GY[N], tot;
EDGE E[N * N];
 
void addnode(int *G, int dd, int e1, int e2) {
	EDGE e = { e1, e2, G[dd] };
	E[tot] = e;
	G[dd] = tot++;
}
 
void solve() {
	int i, j, x, y, ans = 0;
	memset(sum, 0, sizeof(sum));
	for (i = 0; i < n1; i++) {
		scanf("%d", lx + i);
		lx[i]++;
	}
	for (i = 0; i < n2; i++) {
		scanf("%d", ly + i);
		ly[i]++;
	}
	for (i = 0; i < n3; i++) {
		scanf("%d%d", &x, &y);
		if (x + 1 >= N || y + 1 >= N) continue;
		sum[x + 1][y + 1] = 1;
	}
	for (i = 1; i < N; i++)
		for (j = 1; j < N; j++)
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	memset(GY, -1, sizeof(GY));
	sort(lx, lx + n1);
	sort(ly, ly + n2);
	tot = 0;
	for (i = 0; i < n2; i++)
		for (j = i + 1; j < n2; j++)
			addnode(GY, ly[j] - ly[i], ly[i], ly[j]);
	for (i = 0; i < n1; i++)
		for (j = i + 1; j < n1; j++) {
			for (y = GY[lx[j] - lx[i]]; ~y; y = E[y].next)
				ans += sum[lx[j]][E[y].e2] - sum[lx[i] - 1][E[y].e2] - sum[lx[j]][E[y].e1 - 1] + sum[lx[i] - 1][E[y].e1 - 1] > 0;
		}
	printf("%d\n", ans);
}
int main() {
	//freopen("in.txt", "r", stdin);
	while (scanf("%d%d%d", &n1, &n2, &n3) != EOF)
		solve();
	return 0;
}
