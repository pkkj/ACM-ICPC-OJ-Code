// SGU 177 Square
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1005
struct NODE {
	int s[4], c, w;
	int x1, y1, x2, y2;
};
int p = 1;
NODE tree[N*N * 5];
 
void create(int p, int x1, int y1, int x2, int y2) {
	tree[p].x1 = x1, tree[p].y1 = y1, tree[p].x2 = x2, tree[p].y2 = y2;
	for (int i = 0; i < 4; i++)
		tree[p].s[i] = 0;
	tree[p].c = 1, tree[p].w = (x2 - x1 + 1) * (y2 - y1 + 1);
}
 
void update(int p) {
	if (tree[p].c == 1) tree[p].w = (tree[p].x2 - tree[p].x1 + 1) * (tree[p].y2 - tree[p].y1 + 1);
	else if (tree[p].c == 0) tree[p].w = 0;
	else {
		tree[p].w = 0;
		for (int i = 0; i < 4; i++)
			if (tree[p].s[i]) tree[p].w += tree[tree[p].s[i]].w;
	}
}
 
void build(int id, int x1, int y1, int x2, int y2) {
	int mx, my;
	create(id, x1, y1, x2, y2);
	if (x1 == x2 && y1 == y2) return;
	mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
	tree[id].s[0] = ++p;
	build(p, x1, y1, mx, my);
	if (x1 != x2) {
		tree[id].s[1] = ++p;
		build(p, mx + 1, y1, x2, my);
	}
	if (y1 != y2) {
		tree[id].s[2] = ++p;
		build(p, x1, my + 1, mx, y2);
	}
	if (x1 != x2 && y1 != y2) {
		tree[id].s[3] = ++p;
		build(p, mx + 1, my + 1, x2, y2);
	}
}
 
void insert(int p, int x1, int y1, int x2, int y2, int col) {
	if (x1 > tree[p].x2 || x2 < tree[p].x1 || y1 > tree[p].y2 || y2 < tree[p].y1) return;
	if (x1 <= tree[p].x1 && x2 >= tree[p].x2 && y1 <= tree[p].y1 && y2 >= tree[p].y2) tree[p].c = col;
	else {
		for (int i = 0; i < 4; i++)
			if (tree[p].s[i]) {
				if (tree[p].c != -1) {
					tree[tree[p].s[i]].c = tree[p].c;
					update(tree[p].s[i]);
				}
				insert(tree[p].s[i], x1, y1, x2, y2, col);
			}
		tree[p].c = -1;
	}
	update(p);
}
int main() {
	int n, Q, x1, y1, x2, y2, xa, xb, ya, yb;
	char ch;
	scanf("%d%d", &n, &Q);
	build(1, 1, 1, n, n);
	while (Q--) {
		scanf("%d%d%d%d %c", &xa, &ya, &xb, &yb, &ch);
		x1 = min(xa, xb), x2 = max(xa, xb);
		y1 = min(ya, yb), y2 = max(ya, yb);
		insert(1, x1, y1, x2, y2, ch == 'w');
	}
	printf("%d\n", tree[1].w);
	return 0;
}
