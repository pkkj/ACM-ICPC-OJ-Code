// 2005 Southwestern Europe: The mysterious X network
// ACM-ICPC Live Archive 3502
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define N 100005
using namespace std;
int n, s, t;
vector<int> G[N];

int v[N];
int bfs() {
	queue<int> Q;
	int pt, dep = 0, size = 1, ts;
	v[s] = 0;
	Q.push(s);
	while (!Q.empty()) {
		ts = 0;
		while (size--) {
			pt = Q.front();
			Q.pop();
			if (pt == t) return v[t];
			for (size_t i = 0; i < G[pt].size(); i++) {
				int x;
				x = G[pt][i];
				if (v[x] == -1) {
					v[x] = dep;
					Q.push(x);
					ts++;
				}
			}
		}
		size = ts;
		dep++;
	}
	return 0;
}
int main() {
	int T, ca, j, c, k;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca) printf("\n");
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			G[i].clear();
		
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &c, &k);
			for (j = 0; j < k; j++) {
				int x;
				scanf("%d", &x);
				G[c].push_back(x);
				G[x].push_back(c);
			}
		}
		scanf("%d%d", &s, &t);
		memset(v, -1, sizeof(v));
		printf("%d %d %d\n", s, t, bfs());
	}
	return 0;
}