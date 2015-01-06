// CII 3523
// 2005 Central Europe: Knights of the Round Table
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#define N 1005
#define M 2000005
#define WHITE 0
#define BLACK 1
#define GRAY 2

using namespace std;

int n, root, counter, tot, nblock;
int C[N], D[N], A[N], low[N], cut[N], color[N], good[N];

stack<int> S;
vector<int> block[N];

struct EDGE {
	int a, b, next;
};

EDGE ET[M];
int NT[N], sum;
void addedge(int a, int b) {
	EDGE x = { a, b, NT[a] };
	ET[tot] = x;
	NT[a] = tot++;
}
void dfs_block(int k, int father, int deep) {
	int tot, i;
	C[k] = GRAY, D[k] = deep, low[k] = deep, tot = 0;
	S.push(k);
	for (int j = NT[k]; j != -1; j = ET[j].next) {
		i = ET[j].b;
		if (i != father && C[i] == GRAY) low[k] = min(low[k], D[i]);
		if (C[i] == WHITE) {
			dfs_block(i, k, deep + 1);
			tot++, low[k] = min(low[k], low[i]);
			if ((k == root && tot > 1) || (k != root && low[i] >= D[k])) {
				cut[k] = 1;
			}
			if (low[i] >= D[k]) {
				block[nblock].push_back(k);
				while (!S.empty() && S.top() != i) {
					block[nblock].push_back(S.top());
					S.pop();
				}
				block[nblock].push_back(S.top());
				S.pop();
				nblock++;
			}
		}
	}
	C[k] = BLACK, A[k] = ++counter;
}
int dfs(int t, int col) {
	int i;
	C[t] = 1;
	color[t] = col;
	for (int j = NT[t]; j != -1; j = ET[j].next) {
		i = ET[j].b;
		if (cut[i] && i != t) {
			if (!C[i]) {
				if (dfs(i, !col)) return 1;
			} else if (color[t] == color[i]) return 1;

		}
	}
	return 0;
}
void judge(int id) {
	int i;
	memset(cut, 0, sizeof(cut));
	memset(C, 0, sizeof(C));
	memset(color, 0, sizeof(color));
	for (i = 0; i < block[id].size(); i++)
		cut[block[id][i]] = 1;
	if (dfs(block[id][0], 0)) {
		for (unsigned k = 0; k < block[id].size(); k++)
			good[block[id][k]] = 1;
	}
}

bool hate[N][N];
int main() {
	int m, i, j;
	while (scanf("%d%d", &n, &m) && n) {
		int ans = 0;
		memset(NT, -1, sizeof(NT));
		memset(hate, 0, sizeof(hate));
		memset(C, 0, sizeof(C));
		memset(cut, 0, sizeof(cut));
		memset(block, 0, sizeof(block));
		memset(good, 0, sizeof(good));
		nblock = tot = 0;
		for (i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			hate[a][b] = hate[b][a] = 1;
		}
		for (i = 1; i <= n; i++)
			for (j = i; j <= n; j++)
				if (!hate[i][j]) addedge(i, j), addedge(j, i);

		for (i = 1; i <= n; i++) {
			if (!C[i]) {
				root = i, counter = 0;
				dfs_block(i, 0, i);
			}
		}

		for (i = 0; i < nblock; i++)
			judge(i);
		for (i = 1; i <= n; i++)
			ans += good[i];
		printf("%d\n", n - ans);
	}
	return 0;
}

