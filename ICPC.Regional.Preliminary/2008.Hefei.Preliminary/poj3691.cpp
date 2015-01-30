// 2008 Hefei Preliminary: DNA repair
// POJ 3691
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define NAL 4	// Number of letters
#define NW 51	// Number of words
#define NL 22	// Length of word
#define N NW*NL+5 // Number of nodes in the Tire tree
#define M 1005 // The length of the string to be modified
#define INF 1000000
class TRIE {
public:
	int id, na;
	bool danger[N];	//danger: marking the "dangerous" node.
	short child[N][NAL], suf[N];
	char sw[200]; // Convert the char set to number

	TRIE() {
	}
	TRIE(int na) {
		id = 1, this->na = na;
		sw['A'] = 0, sw['C'] = 1, sw['G'] = 2, sw['T'] = 3;
	}
	void insert(char *str) {
		int j, x, y;
		x = 1, j = 0;
		while (str[j]) {
			y = sw[str[j]];
			if (!child[x][y]) child[x][y] = ++id, danger[id] = 0;
			x = child[x][y];
			if (danger[x]) break;
			j++;
		}
		danger[x] = true;
	}

	// Build the graph by using BFS
	void build_graph() {
		queue<int> Q;
		int i, x, y;
		for (i = 0; i < na; i++) {
			if (!child[1][i]) child[1][i] = 1;
			else {
				x = child[1][i];
				Q.push(x);
				suf[x] = 1;
			}
		}
		while (!Q.empty()) {
			x = Q.front(), Q.pop();
			danger[x] = danger[x] || danger[suf[x]];
			if (!danger[x]) for (y = 0; y < na; y++) {
				if (!child[x][y]) child[x][y] = child[suf[x]][y];
				else {
					Q.push(child[x][y]);
					suf[child[x][y]] = child[suf[x]][y];
				}
			}
		}
	}
};

TRIE ac;
char str[M];
short dp[M][N];

inline int checkmin(int a, int b) {
	if (a == -1) return b;
	return a < b ? a : b;
}
void solve() {
	int i, x, y, k, ans, m;
	memset(dp, -1, sizeof(dp));
	k = ac.sw[str[0]];
	// Set the initial values of the DP formula
	for (i = 0; i < ac.na; i++) {
		if (!ac.danger[ac.child[1][i]]) {
			if (i == k) dp[0][ac.child[1][i]] = 0;
			else dp[0][ac.child[1][i]] = 1;
		}
	}
	m = strlen(str);
	for (i = 1; i < m; i++) {
		for (x = 1; x <= ac.id; x++) {
			if (dp[i - 1][x] == -1) continue;
			k = ac.sw[str[i]];
			for (y = 0; y < ac.na; y++) {
				// Determine whether the current node is a "dangerous" node. If yes, we should not do the DP
				if (!ac.danger[ac.child[x][y]]) {
					if (y == k) dp[i][ac.child[x][y]] = checkmin(dp[i][ac.child[x][y]], dp[i - 1][x]);//No modification, go to next character
					else dp[i][ac.child[x][y]] = checkmin(dp[i][ac.child[x][y]], dp[i - 1][x] + 1); // Modify the current character and go to another character, increase the cost
				}
			}
		}
	}
	ans = INF;
	for (i = 1; i <= ac.id; i++) {
		if (dp[m - 1][i] == -1) continue;
		ans = ans < dp[m - 1][i] ? ans : dp[m - 1][i];
	}
	if (ans == INF) ans = -1;
	printf("%d\n", ans);
}

int main() {
	int nw, T = 0;
	char cmd[30];
	while (scanf("%d", &nw) && nw) {
		ac = TRIE(4);
		while (nw--) {
			scanf("%s", cmd);
			ac.insert(cmd);
		}
		scanf("%s", str);
		ac.build_graph();
		printf("Case %d: ", ++T);
		solve();
	}
	return 0;
}