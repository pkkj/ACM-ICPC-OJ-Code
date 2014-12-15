// POJ 3225
// PKU Local 2007 (POJ Monthly--2007.04.28): Help with Intervals

#include <cstdio>
#include <cstring>
#define N 65540 * 2
 
short c[N*4];
bool a[N*4];
 
void downseg(int p, int l, int r) {
	if (l == r) {
		if (c[p] == 1) a[l] ^= 1;
		else if (c[p] == 2) a[l] = 0;
		else if (c[p] == 3) a[l] = 1;
	} else {
		if (c[p] == 1) c[p << 1] ^= 1, c[p << 1 | 1] ^= 1;
		else if (c[p] > 1) c[p << 1] = c[p << 1 | 1] = c[p];
	}
	c[p] = 0;
}
 
void insert(int p, int l, int r, int u, int v, int op) {
	if (r < u || l > v) return;
	if (c[p]) downseg(p, l, r);
	if (u <= l && r <= v) {
		c[p] = op;
		return;
	}
	if (l == r) return;
	int mid = (l + r) >> 1;
	insert(p << 1, l, mid, u, v, op);
	insert(p << 1 | 1, mid + 1, r, u, v, op);
}
 
void final(int p, int l, int r) {
	if (c[p]) downseg(p, l, r);
	if (l == r) return;
	int mid = (l + r) >> 1;
	final(p << 1, l, mid);
	final(p << 1 | 1, mid + 1, r);
}
void print(int a, int b) {
	if (a & 1) printf("(%d,", a >> 1);
	else printf("[%d,", a >> 1);
	if (b & 1) printf("%d)", (b + 1) >> 1);
	else printf("%d]", b >> 1);
}
int main() {
	char op, cl, cr;
	int l, r, i, be, cnt;
	memset(c, 0, sizeof(c));
	memset(a, 0, sizeof(a));
	while (scanf("%c %c%d,%d%c", &op, &cl, &l, &r, &cr) != EOF) {
		getchar();
		l *= 2, r *= 2;
		if (cl == '(') l++;
		if (cr == ')') r--;
		switch (op) {
		case 'U':
			insert(1, 0, N, l, r, 3);
			break;
		case 'I':
			insert(1, 0, N, 0, l - 1, 2);
			insert(1, 0, N, r + 1, N, 2);
			break;
		case 'D':
			insert(1, 0, N, l, r, 2);
			break;
		case 'C':
			insert(1, 0, N, 0, N, 1);
			insert(1, 0, N, 0, l - 1, 2);
			insert(1, 0, N, r + 1, N, 2);
			break;
		case 'S':
			insert(1, 0, N, l, r, 1);
			break;
		}
	}
	final(1, 0, N);
	cnt = 0;
	for (i = 0; i < N; i++) {
		if (i == 0 && a[0] == 1 || i > 1 && a[i] == 1 && a[i - 1] == 0) be = i;
		if (a[i] == 0 && a[i - 1] == 1) {
			print(be, i - 1);
			cnt++;
			printf(" ");
		}
	}
	if (!cnt) printf("empty set");
	return 0;
}
