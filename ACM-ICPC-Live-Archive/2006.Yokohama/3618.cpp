// 2006 Yokohama: Cubic Eight-Puzzle
// ACM-ICPC Live Archive 3618
// POJ 3131
#include <cstdio>
#include <cstring>
#define SS 9
#define SIZE 2000000
#define EMPTY 6
int sx, sy;
char dest[SS];
int Q[2][SIZE], qh[2], qe[2];
int trans[6][2] = { { 2, 1 }, { 3, 0 }, { 0, 4 }, { 1, 5 }, { 5, 2 }, { 4, 3 } };
short st[SS];
int hash(short *a) {
	int ret = 0, i;
	for (i = 0; i < 9; i++)
		ret = ret * 7 + a[i];
	return ret;
}
 
void fhash(int x, short *a) {
	for (int i = 8; i >= 0; i--)
		a[i] = x % 7, x /= 7;
}
 
// Hash table
struct NODE {
	short k;
	int next, v;
};
int G[SIZE], tot;
NODE E[SIZE];
short find(int id) {
	int p = id % SIZE, i;
	for (i = G[p]; ~i; i = E[i].next)
		if (E[i].v == id) return E[i].k;
	return 0;
}
void addnode(int id, short k) {
	int p = id % SIZE;
	NODE e = { k, G[p], id };
	E[tot] = e;
	G[p] = tot++;
}
void inithash() {
	memset(G, -1, sizeof(G));
	tot = 1;
}
// End of hash table
int init() {
	char ss[3];
	scanf("%d%d", &sy, &sx);
	if (sx == 0) return 0;
	for (int i = 0; i < SS; i++) {
		scanf("%s", ss);
		dest[i] = ss[0];
	}
	memset(st, 0, sizeof(st));
	sx--, sy--;
	st[sx * 3 + sy] = EMPTY;
	return 1;
}
int check() {
	for (int i = 0; i < 9; i++) {
		if (dest[i] == 'E' && st[i] != EMPTY) return 0;
		if (dest[i] == 'B' || dest[i] == 'R') return 0;
	}
	return 1;
}
// General the initial status
short aa[SS];
void dfs(int i) {
	if (i == 9) {
		int id = hash(aa);
		Q[1][qe[1]++] = id;
		addnode(id, -1);
		return;
	}
	if (dest[i] == 'E') {
		aa[i] = EMPTY;
		dfs(i + 1);
	} else if (dest[i] == 'W') {
		aa[i] = 0;
		dfs(i + 1);
		aa[i] = 5;
		dfs(i + 1);
	} else if (dest[i] == 'B') {
		aa[i] = 1;
		dfs(i + 1);
		aa[i] = 4;
		dfs(i + 1);
	} else if (dest[i] == 'R') {
		aa[i] = 2;
		dfs(i + 1);
		aa[i] = 3;
		dfs(i + 1);
	}
}
// BFS in two direction
int step;
int expand(int id, int dir) {
	short ret = find(id);
	if (dir == 0) {
		if (ret < 0) return step - ret - 1;
		if (ret == 0) {
			addnode(id, step + 1);
			Q[0][qe[0]++] = id;
		}
	} else if (dir == 1) {
		if (ret > 0) return step + ret - 1;
		if (ret == 0) {
			addnode(id, -step - 1);
			Q[1][qe[1]++] = id;
		}
	}
	return 0;
}
int search(int dir) {
	int sstep = step, ret;
	short cur[SS];
	if (dir == 1) sstep = -step;
	while (qh[dir] < qe[dir] && find(Q[dir][qh[dir]]) == sstep) {
		int x;
		fhash(Q[dir][qh[dir]], cur);
		qh[dir]++;
		for (x = 0;; x++)
			if (cur[x] == EMPTY) break;
		// DIR 0
		if (x >= 3) {
			int y = x - 3;
			short vy = cur[y];
			cur[x] = trans[cur[y]][0];
			cur[y] = EMPTY;
			ret = expand(hash(cur), dir);
			if (ret) return ret;
			cur[x] = EMPTY, cur[y] = vy;
		}
		// DIR 1
		if (x <= 5) {
			int y = x + 3;
			short vy = cur[y];
			cur[x] = trans[cur[y]][0];
			cur[y] = EMPTY;
			ret = expand(hash(cur), dir);
			if (ret) return ret;
			cur[x] = EMPTY, cur[y] = vy;
		}
		// DIR 2
		if (x != 0 && x != 3 && x != 6) {
			int y = x - 1;
			short vy = cur[y];
			cur[x] = trans[cur[y]][1];
			cur[y] = EMPTY;
			ret = expand(hash(cur), dir);
			if (ret) return ret;
			cur[x] = EMPTY, cur[y] = vy;
		}
		// DIR 3
		if (x != 2 && x != 5 && x != 8) {
			int y = x + 1;
			short vy = cur[y];
			cur[x] = trans[cur[y]][1];
			cur[y] = EMPTY;
			ret = expand(hash(cur), dir);
			if (ret) return ret;
			cur[x] = EMPTY, cur[y] = vy;
		}
	}
	return 0;
}
int solve() {
	if (check()) return 0;
	int id;
	inithash();
	qh[0] = qh[1] = qe[0] = qe[1] = 0;
	id = hash(st);
	addnode(id, 1);
	Q[0][qe[0]++] = id;
	dfs(0);
	step = 1;
	while (qh[0] < qe[0] && qh[1] < qe[1] && step <= 21) {
		int ret = search(0);
		if (ret) return ret;
		if (step <= 9) {
			ret = search(1);
			if (ret) return ret;
		}
		step++;
	}
	return -1;
}
int main() {
	while (init()) {
		int ret = solve();
		if (ret > 30) ret = -1;
		printf("%d\n", ret);
	}
}