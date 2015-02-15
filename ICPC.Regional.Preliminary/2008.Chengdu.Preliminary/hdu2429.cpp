// 2008 Chengdu Preliminary: Word Game
// HDU 2429

#include <cstdio>
#include <cstring>
#define N 31
#define LEN 11
#define M 10001
 
int n, cnt;
void mul(int a[][2 * N], int b[][2 * N]) {
	int i, j, k;
	int c[N][2 * N];
	memset(c, 0, sizeof(c));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++) {
				c[i][j] += a[i][k] * b[k][j];
				c[i][j] %= M;
			}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				c[i][j + n] += a[i][k] * b[k][j + n];
				c[i][j + n] %= M;
			}
			c[i][j + n] += a[i][j + n];
			c[i][j + n] %= M;
		}
	for (i = 0; i < n; i++)
		for (j = 0; j < 2 * n; j++)
			a[i][j] = c[i][j];
}
 
void power(int res[][2 * N], int exp) {
	int x[N][2 * N], p = 0;
	memcpy(x, res, sizeof(x));
	for (; (1 << p) <= exp; p++)
		;
	for (p -= 2; p >= 0; p--) {
		mul(res, res);
		if ((1 << p) & exp) mul(res, x);
	}
}
 
char table[N][2], word[N][LEN];
char sw[LEN], tw[LEN];
int ss, tt;
void init() {
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", word[i]);
		table[i][0] = word[i][0], table[i][1] = word[i][strlen(word[i]) - 1];
	}
	scanf("%s%s", sw, tw);
	for (i = 0; i < n; i++) {
		if (strcmp(word[i], sw) == 0) ss = i;
		if (strcmp(word[i], tw) == 0) tt = i;
	}
	scanf("%d", &cnt);
}
int g[N][N], g2[N][2 * N], g3[N][N], g4[N][N];
void build() {
	int i, j;
	memset(g, 0, sizeof(g));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (table[i][1] == table[j][0]) g[i][j] = 1;
}
 
void calc() {
	int i, j, k;
	if (cnt % 2 == 0) cnt--;
	memset(g2, 0, sizeof(g2));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				g2[i][j] += g[i][k] * g[k][j];
 
	for (i = 0; i < n; i++)
		g2[i][i + n] = 1;
	k = (cnt - 1) / 2;
	power(g2, k + 1);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			g3[i][j] = g2[i][j + n];
	memset(g4, 0, sizeof(g4));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++) {
				g4[i][j] += g[i][k] * g3[k][j];
				g4[i][j] %= M;
			}
	printf("%d\n", g4[ss][tt]);
 
}
void solve() {
	init();
	build();
	calc();
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}