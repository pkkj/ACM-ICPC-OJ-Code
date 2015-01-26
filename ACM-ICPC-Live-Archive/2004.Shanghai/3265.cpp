// 2004 Shanghai: The Rotation Game
// POJ 2286
// ACM-ICPC Live Archive 3265
#include <cstdio>
#include <cstring>
#define N 24
int st[N];
int target[] = { 6, 7, 8, 11, 12, 15, 16, 17 };
int change[8][7] = { { 0, 2, 6, 11, 15, 20, 22 }, { 1, 3, 8, 12, 17, 21, 23 }, { 10, 9, 8, 7, 6, 5, 4 }, { 19, 18, 17, 16, 15, 14, 13 }, {
		23, 21, 17, 12, 8, 3, 1 }, { 22, 20, 15, 11, 6, 2, 0 }, { 13, 14, 15, 16, 17, 18, 19 }, { 4, 5, 6, 7, 8, 9, 10 } };
 
bool read() {
	scanf("%d", &st[0]);
	if (!st[0]) return false;
	for (int i = 1; i < N; i++)
		scanf("%d", st + i);
	return true;
}
 
int atleast(int st[N]) {
	int i, j, ans = 0;
	int cnt[8] = { 0 };
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++)
			if (st[target[i]] == st[target[j]]) cnt[i]++;
		ans = ans > cnt[i] ? ans : cnt[i];
	}
	return 8 - ans;
}
int DEP;
char stack[100];
bool dfs(int st[N], int dep) {
	int i, finish = 1, nst[N], k;
	for (i = 1; i < 8 && finish; i++)
		if (st[target[i]] != st[target[0]]) finish = 0;
	if (finish) {
		if (dep == 0) printf("No moves needed\n");
		else {
			for (i = 0; i < dep; i++)
				printf("%c", stack[i]);
			printf("\n");
		}
		printf("%d\n", st[target[0]]);
		return true;
	}
 
	if (atleast(st) + dep >= DEP) return false;
	for (i = 0; i < 8; i++) {
		stack[dep] = 'A' + i;
		memcpy(nst, st, sizeof(nst));
		for (k = 0; k < 7; k++)
			nst[change[i][k]] = st[change[i][(k + 1) % 7]];
		if (dfs(nst, dep + 1)) return true;
	}
	return false;
}
 
int main() {
	while (read())
		for (DEP = 0;; DEP++)
			if (dfs(st, 0)) break;
	return 0;
}