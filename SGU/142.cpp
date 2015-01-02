// SGU 142 Keyword
#include <cstdio>
#define N 500005
 
int child[2 * N][2], tot, diff;
bool key[2 * N], data[N];
 
void insert(int beg, int end) {
	int x = 0, y;
	while (beg != end) {
		y = data[beg];
		if (child[x][y] == -1) {
			child[x][y] = tot++;
			child[child[x][y]][0] = child[child[x][y]][1] = -1;
			key[child[x][y]] = 0;
		}
		x = child[x][y];
		beg++;
	}
	if (!key[x]) key[x] = 1, diff++;
}
int depth;
bool ans[25], tmp[25];
int dfs(int x, int len) {
	int i;
	if (len == depth) return 0;
	tmp[len] = 0;
	if (child[x][0] == -1) {
		for (i = 0; i < len; i++)
			ans[i] = tmp[i];
		ans[i] = 0;
		return 1;
	}
	if (child[x][1] == -1) {
		for (i = 0; i < len; i++)
			ans[i] = tmp[i];
		ans[i] = 1;
		return 1;
	}
	if (dfs(child[x][0], len + 1)) return 1;
	tmp[len] = 1;
	return dfs(child[x][1], len + 1);
}
int main() {
	int n, i, ch, l, r;
	scanf("%d\n", &n);
	for (i = 0; i < n; i++) {
		ch = getchar();
		data[i] = ch == 'b';
	}
	l = 1, r = 20 > (n / 2 + 1) ? (n / 2 + 1) : 20;
	while (l < r) {
		int mid = (l + r) >> 1;
		tot = 1, child[0][0] = child[0][1] = -1, key[0] = 0;
		diff = 0;
		for (i = 0; i < n - mid + 1; i++)
			insert(i, i + mid);
		depth = mid;
		if (diff == (1 << mid)) l = mid + 1;
		else {
			if (dfs(0, 0)) r = mid;
			else l = mid + 1;
		}
	}
	printf("%d\n", l);
	for (i = 0; i < l; i++)
		putchar(ans[i] ? 'b' : 'a');
	return 0;
}
