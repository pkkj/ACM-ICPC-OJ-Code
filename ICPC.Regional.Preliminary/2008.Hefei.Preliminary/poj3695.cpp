// 2008 Hefei Preliminary: Rectangles
// POJ 3695
#include <cstdio>
#define N 22
#define M 500000
#define MAX(a, b)   a > b ? a : b;
#define MIN(a, b)   a < b ? a : b;
struct NODE {
	int lx, ly, rx, ry;
	int tag;
};

NODE input[N], queue[M];
int nn, nq;
void cut(int i, int tail, int &p) {
	if (queue[i].lx >= queue[tail].rx || queue[i].rx <= queue[tail].lx)
		return;
	if (queue[i].ly >= queue[tail].ry || queue[i].ry <= queue[tail].ly)
		return;

	queue[p].lx = MAX(queue[i].lx, queue[tail].lx);
	queue[p].rx = MIN(queue[i].rx, queue[tail].rx);
	queue[p].ly = MAX(queue[i].ly, queue[tail].ly);
	queue[p].ry = MIN(queue[i].ry, queue[tail].ry);
	queue[p].tag = -queue[i].tag;
	p++;
}
void solve() {
	int i, j, T = 0, n, x;
	while (nq--) {
		int ans = 0, tp, end = 0;
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d\n", &x);
			queue[end] = input[x - 1];
			queue[end].tag = 1;
			tp = end++;
			for (j = 0; j < tp; j++)
				cut(j, tp, end);
		}
		for (i = 0; i < end; i++)
			ans += (queue[i].rx - queue[i].lx) * (queue[i].ry - queue[i].ly) * queue[i].tag;
		printf("Query %d: %d\n", ++T, ans);
	}
}
int main() {
	int T = 0, i;
	while (scanf("%d%d", &nn, &nq) && nn) {
		printf("Case %d:\n", ++T);
		for (i = 0; i < nn; i++)
			scanf("%d%d%d%d", &input[i].lx, &input[i].ly, &input[i].rx, &input[i].ry);
		solve();
		printf("\n");
	}
	return 0;
}