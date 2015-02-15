// 2003 Guangzhou: Task Sequences
// ACM-ICPC Live Archive 2954
// POJ 1776
#include <cstdio>
#include <cstring>
#define N 1005
int g[N][N], path[N], n;
 
void find() {
	int i, j, k;
	for (i = 1; i <= n; i++) {
		j = 0;
		while (1) {
			k = path[j];
			if (k == -1) {
				path[j] = i;
				break;
			}
			if (g[i][k]) {
				path[j] = i, path[i] = k;
				break;
			}
			j = k;
		}
	}
}
char cmd[10000];
void read() {
	int i, j, k;
	getchar();
	for (i = 1; i <= n; i++) {
		k = 0, j = 1;
		gets(cmd);
		while (cmd[k]) {
			if (cmd[k] == '1') g[i][j++] = 1;
			if (cmd[k] == '0') g[i][j++] = 0;
			k++;
		}
	}
}
void solve() {
	int i;
	read();
	memset(path, -1, sizeof(path));
	find();
	i = 0;
	while (1) {
		printf("%d ", path[i]);
		i = path[i];
		if (path[i] == -1) break;
	}
	printf("\n");
}
int main() {
	while (scanf("%d", &n) != EOF) {
		printf("1\n%d\n", n);
		solve();
	}
	return 0;
}