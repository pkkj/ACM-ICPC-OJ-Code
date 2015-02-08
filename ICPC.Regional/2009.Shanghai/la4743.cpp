// 2009 Shanghai: Alice’s Cube
// ACM-ICPC Live Archive 4743
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 17
int EX[N * N], EY[N * N], dp[(1 << 16) + 5], ce = 0;
queue<int> Q;
void add(int x, int y) {
	EX[ce] = x - 1, EY[ce] = y - 1;
	ce++;
}
void init();
int main() {
	int T, i, x, st, nst, ca = 1;
	init();
	dp[65280] = 0;
	Q.push(65280);
	while (!Q.empty()) {
		st = Q.front();
		Q.pop();
		for (i = 0; i < ce; i++) {
			int x = (st & (1 << EX[i])) > 0, y = (st & (1 << EY[i])) > 0;
			if (x != y) {
				nst = st;
				if (x) nst = nst & (~(1 << EX[i]));
				else nst = nst | (1 << EX[i]);
				if (y) nst = nst & (~(1 << EY[i]));
				else nst = nst | (1 << EY[i]);
				if (dp[nst] == -1) {
					dp[nst] = dp[st] + 1;
					Q.push(nst);
				}
			}
		}
	}
	scanf("%d", &T);
	while (T--) {
		st = 0;
		for (i = 0; i < 16; i++) {
			scanf("%d", &x);
			if (x) st |= (1<<i);
		}
		printf("Case #%d: ", ca++);
		if (dp[st] > 3) printf("more\n");
		else printf("%d\n", dp[st]);
	}
	return 0;
}
void init() {
	memset(dp, -1, sizeof(dp));
	add(1, 2);
	add(1, 3);
	add(1, 5);
	add(1, 9);
	add(2, 4);
	add(2, 6);
	add(2, 10);
	add(3, 4);
	add(3, 7);
	add(3, 11);
	add(4, 8);
	add(4, 12);
	add(5, 6);
	add(5, 7);
	add(5, 13);
	add(6, 8);
	add(6, 14);
	add(7, 8);
	add(7, 15);
	add(8, 16);
	add(9, 10);
	add(9, 11);
	add(9, 13);
	add(10, 12);
	add(10, 14);
	add(11, 12);
	add(11, 15);
	add(12, 16);
	add(13, 14);
	add(13, 15);
	add(14, 16);
	add(15, 16);
}
