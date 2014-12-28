// CII 4430
// 2008 Tehran: ACM Coalition
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 55
int n, m;
int size[N];
struct NODE {
	int a, b, c;
	NODE() {
	}
	NODE(int a, int b, int c) :
		a(a), b(b), c(c) {
	}
};
vector<NODE> ll[N];
char s[1000];
char cmd[10000];
void read() {
	int i, j, a, b, c;
	for (i = 1; i <= n; i++) {
		scanf("%d: ", &size[i]);
		ll[i].clear();
		gets(cmd);
		int p = 0, in = 0;
		for (j = 0;; j++) {
			if (cmd[j] == ';') break;
			if (cmd[j] == '(') {
				p = 0;
				in = 1;
			} else if (cmd[j] == ')') {
				in = 0;
				s[p] = 0;
				sscanf(s, "%d,%d,%d", &a, &b, &c);
				ll[i].push_back(NODE(a, b, c));
			} else {
				if (in) s[p++] = cmd[j];
			}
		}
	}
}
int dp[N][2][3][7];
void solve() {
	int p, i, j, k, a, b, c, best = 10000;
	memset(dp, 0, sizeof(dp));
	for (p = 1; p <= n; p++)
		for (i = 0; i < (int) ll[p].size(); i++)
			for (a = 0; a <= 1; a++)
				for (b = 0; b <= 2; b++)
					for (c = 0; c <= 6; c++)
						for (j = 0; j < p; j++) {
							int pa = a + ll[p][i].a, pb = b + ll[p][i].b, pc = c + ll[p][i].c;
							if (pa <= 1 && pb <= 2 && pc <= 6) {
								if (dp[j][a][b][c] + size[p] > dp[p][pa][pb][pc]) dp[p][pa][pb][pc] = dp[j][a][b][c] + size[p];
							}
						}
 
	a = 1, b = 2, c = 6;
	for (p = 1; p <= n; p++)
		for (i = 0; i <= 1; i++)
			for (j = 0; j <= 2; j++)
				for (k = 0; k <= 6; k++) {
					if (dp[p][i][j][k] >= m) {
						if (i * 25 + j * 8 + k < best) {
							best = i * 25 + j * 8 + k;
							a = i, b = j, c = k;
						}
					}
				}
	printf("%d %d %d\n", 1 - a, 2 - b, 6 - c);
 
}
int main() {
	while (scanf("%d%d", &n, &m) && n) {
		read();
		solve();
	}
	return 0;
}
