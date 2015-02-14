// 2006 Northeastern Europe: Interconnect
// ACM-ICPC Live Archive 3710

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 35
int C[N][N];

void make(int n) {
	memset(C, 0, sizeof(C));
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= i && j <= 2; j++)
			if (j == 0)
				C[i][j] = 1;
			else
				C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
}

struct LIST {
	int d[N], size;
	LIST() {
		size = 0;
	}
	void add(int x) {
		d[size++] = x;
	}
	int &operator[](int idx) {
		return d[idx];
	}
	void sort() {
		std::sort(d, d + size);
	}
};
// Union set
int fa[N];
void init(int n) {
	for (int i = 0; i <= n; i++)
		fa[i] = i;
}
int find(int x) {
	if (fa[x] != x)
		fa[x] = find(fa[x]);
	return fa[x];
}
void sunion(int x, int y) {
	fa[x] = y;
}
// End of union set

// Hash table
#define M 35123
int ranum1[] = { 17690, 17618, 3584, 8850, 8525, 19176, 6494, 944, 3060, 638, 16369, 13486, 7082, 3014, 10022, 10171, 14879, 5662, 15348,
		14902, 16921, 7835, 18212, 19589, 4505, 11120, 6596, 659, 13227, 11532, 4407 };
int ranum2[] = { 6292, 9283, 11564, 2020, 19715, 1344, 14538, 5922, 13346, 18284, 14113, 1825, 3933, 16574, 2111, 8806, 15067, 6409, 971,
		8830, 17636, 9864, 1269, 11248, 3760, 10717, 14239, 18660, 10914, 1044, 18663 };
struct NODE {
	int v1, v2, next;
	double v;
};

NODE E[M];
int G[M], tot;
int iabs(int x) {
	return x < 0 ? -x : x;
}
void gethash(LIST &V, int &v1, int &v2) {
	v1 = v2 = 0;
	for (int i = 0; i < V.size; i++) {
		v1 += V[i] * ranum1[i];
		v2 += V[i] * ranum2[i];
	}
}

int find(int v1, int v2) {
	int x = iabs(v1) % M;
	for (int i = G[x]; ~i; i = E[i].next)
		if (E[i].v1 == v1 && E[i].v2 == v2)
			return i;
	return -1;
}
void addnode(int v1, int v2, double v) {
	int pos = find(v1, v2);
	if (pos != -1)
		return;
	pos = iabs(v1) % M;
	NODE e = { v1, v2, G[pos], v };
	G[pos] = tot;
	E[tot++] = e;
}
// End of hash table

// Main DP
int n;
double dp(LIST x) {
	int pos, v1, v2, i, j;
	double pp, tmp, ans = 0;
	gethash(x, v1, v2);
	if ((pos = find(v1, v2)) != -1)
		return E[pos].v;
	pp = tmp = 1;
	for (i = 0; i < x.size; i++)
		for (j = i + 1; j < x.size; j++) {
			LIST y = x;
			double p = (double) x[i] * x[j] / C[n][2];
			pp -= p;
			y[i] = y[i] + y[j];
			y[j] = N;
			y.sort();
			y.size--;
			tmp += p * dp(y);
		}
	ans = tmp / (1 - pp);
	addnode(v1, v2, ans);
	return ans;
}

int main() {
	int m, a, b, i, cnt[N];
	while (~scanf("%d%d", &n, &m)) {
		LIST ist, est;
		make(n);
		init(n);
		while (m--) {
			scanf("%d%d", &a, &b);
			a = find(a), b = find(b);
			sunion(a, b);
		}
		memset(cnt, 0, sizeof(cnt));
		for (i = 1; i <= n; i++)
			cnt[find(i)]++;
		for (i = 1; i <= n; i++)
			if (cnt[i])
				ist.add(cnt[i]);
		ist.sort();
		tot = 0;
		memset(G, -1, sizeof(G));

		est.add(n);
		gethash(est, a, b);
		addnode(a, b, 0);
		printf("%.8lf\n", dp(ist));
	}
	return 0;
}
