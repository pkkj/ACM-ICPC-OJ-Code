// 2005 Tokyo: Network Mess
// CII 3405
// POJ 2745
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define SIZE 55
#define N 110
#define INF 1<<30
int n, D[SIZE][SIZE], adj[N][N], degree[N];

struct EDGE {
	int from, to, len;
	int disF[SIZE], disT[SIZE]; // Distance from "from" and "to" to all leaves,
	EDGE() {}
	EDGE(int from, int to, int len) : from(from), to(to), len(len) {}
};
EDGE E[N * N];
int tot, totalNode; // Total edges and total nodes
void addEdge(int from, int to, int len, int idx) {
	E[idx] = EDGE(from, to, len);
	adj[from][to] = adj[to][from] = idx;
}

bool vis[N];
void DFS(int root, int node, int dis) {
	vis[node] = 1;
	for (int i = 0; i < totalNode; i++) {
		if (adj[node][i] == -1 || vis[i])
			continue;
		E[adj[node][i]].disF[root] = dis + (node == E[adj[node][i]].from ? 0 : E[adj[node][i]].len);
		E[adj[node][i]].disT[root] = dis + (node == E[adj[node][i]].to ? 0 : E[adj[node][i]].len);
		DFS(root, i, dis + E[adj[node][i]].len);
	}
}

void solve() {
	tot = 0;
	totalNode = n;
	memset(adj, -1, sizeof(adj));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &D[i][j]);

	addEdge(0, 1, D[0][1], tot++);
	for (int i = 2; i < n; i++) {
		// DFS from all the leaves, update their distance to all the nodes
		for (int node = 0; node < i; node++) {
			memset(vis, 0, sizeof(vis));
			DFS(node, node, 0);
		}
		for (int j = 0; j < tot; j++) {
			// Verify whether it's feasible
			bool ok = true;
			int offsetA = INF, offsetB = INF;
			for (int leaf = 0; leaf < i && ok; leaf++) {
				if (E[j].disF[leaf] < E[j].disT[leaf]) {
					int localOffset = D[i][leaf] - E[j].disF[leaf];
					if (offsetA == INF)
						offsetA = localOffset;
					else if (offsetA != localOffset)
						ok = false;
				} else {
					int localOffset = D[i][leaf] - E[j].disT[leaf];
					if (offsetB == INF)
						offsetB = localOffset;
					else if (offsetB != localOffset)
						ok = false;
				}
			}

			if (!ok || offsetA < 0 || offsetB < 0)
				continue;

			// If feasible, add the new edges to the tree
			int newLength = (offsetA + offsetB - E[j].len) / 2;
			if (offsetA - newLength == 0) {
				addEdge(i, E[j].from, newLength, tot++);
			} else if (offsetB - newLength == 0) {
				addEdge(i, E[j].to, newLength, tot++);
			} else {
				// Need to split the current edge
				addEdge(E[j].from, totalNode, offsetA - newLength, tot++);
				addEdge(totalNode, E[j].to, offsetB - newLength, tot++);
				adj[E[j].from][E[j].to] = adj[E[j].to][E[j].from] = -1;
				addEdge(totalNode, i, newLength, j);
				totalNode++;
			}
			break;
		}
	}

	// Calculate the degrees of all the nodes
	vector<int> networkDegree;
	memset(degree, 0, sizeof(degree));
	for (int i = 0; i < tot; i++) {
		degree[E[i].from]++;
		degree[E[i].to]++;
		for (int j = 1; j < E[i].len; j++)
			networkDegree.push_back(2); // Split a "long" edge to small edges(len = 1)
	}
	for (int i = n; i < totalNode; i++)
		networkDegree.push_back(degree[i]);
	sort(networkDegree.begin(), networkDegree.end());
	for (size_t i = 0; i < networkDegree.size(); i++)
		printf(i ? " %d" : "%d", networkDegree[i]);
	printf("\n");
}
int main() {
	while (scanf("%d", &n) && n)
		solve();
}

