// CII 4493
// 2009 Dhaka: That is Your Queue
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int Q[5000];
int main() {
	int ca = 1, n, q, x;
	char cmd[3];
	while (scanf("%d%d", &n, &q) && n + q) {
		printf("Case %d:\n", ca++);
		int qh = 2000, qe = 2000, i;
		for (i = 1; i <= min(1000, n); i++)
			Q[qe++] = i;
		while (q--) {
			scanf("%s", cmd);
			if (cmd[0] == 'N') {
				while (1) {
					x = Q[qh++];
					if (x != -1) break;
				}
				Q[qe++] = x;
				printf("%d\n", x);
			} else {
				scanf("%d", &x);
				for (i = qh; i < qe; i++)
					if (Q[i] == x) {
						Q[i] = -1;
						break;
					}
				Q[--qh] = x;
			}
		}
	}
	return 0;
}
