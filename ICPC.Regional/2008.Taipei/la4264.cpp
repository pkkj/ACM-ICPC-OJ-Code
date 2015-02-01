// 2008 Taipei: Message
// CII 4264
#include <cstdio>
#include <cstring>
#include <algorithm>
#define S 10
#define N 55
bool mode[N][S][S][4];
bool map[S][S];
char letter[N], cmd[N];
int n;
 
void trans(int x) {
	for (int r = 1; r <= 3; r++)
		for (int i = 0; i < S; i++)
			for (int j = 0; j < S; j++)
				mode[x][S - j - 1][i][r] = mode[x][i][j][r - 1];
}
int cmp(int x) {
	int ret = 1 << 29, r, i, j;
	for (r = 0; r < 4; r++) {
		int t = 0;
		for (i = 0; i < S; i++)
			for (j = 0; j < S; j++)
				t += mode[x][i][j][r] != map[i][j];
		ret = t < ret ? t : ret;
	}
	return ret;
}
void solve() {
	int i, j, k, m;
	for (i = 0; i < n; i++) {
		scanf("%s", cmd);
		letter[i] = cmd[0];
		for (j = 0; j < S; j++) {
			scanf("%s", cmd);
			for (k = 0; k < S; k++)
				mode[i][j][k][0] = cmd[k] == '1';
		}
		trans(i);
	}
	scanf("%d", &m);
	while (m--) {
		for (i = 0; i < S; i++) {
			scanf("%s", cmd);
			for (j = 0; j < S; j++)
				map[i][j] = cmd[j] == '1';
		}
		int miss = 1 << 29, pos;
		for (i = 0; i < n; i++) {
			int ret = cmp(i);
			//printf("%d\n", ret);
			if (ret < miss) miss = ret, pos = i;
		}
		putchar(letter[pos]);
	}
}
int main() {
	while (scanf("%d", &n) != EOF) {
		solve();
		putchar('\n');
	}
	return 0;
}