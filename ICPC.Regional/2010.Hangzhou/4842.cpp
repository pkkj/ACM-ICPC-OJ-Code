// CII 4842
// 2010 Hangzhou: Infinite monkey theorem

#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
#define N 27
#define M 1005
#define LEN 15
double dp[M][N], probability[256];
char ch[N][2];
string prefix[LEN];
int go[LEN][N];
int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) && n) {
		int i, j, k, u, v, len;
		double x;
		char dest[LEN];
		string tmp;
		memset(dp, 0, sizeof(dp));
		for (i = 0; i < n; i++) {
			scanf("%s%lf", ch[i], &x);
			probability[(int) ch[i][0]] = x;
		}
 
		scanf("%s", dest);
		len = strlen(dest);
		for (i = 0; i < len; i++) {
			tmp += dest[i];
			prefix[i] = tmp;
		}
		for (i = 0; i < len - 1; i++)
			for (j = 0; j < n; j++) {
				string next = prefix[i] + ch[j];
				bool find = false;
				for (u = 0; u < (int) next.length() && !find; u++) {
					string sstr = next.substr(u);
					for (v = 0; v < len && !find; v++)
						if (sstr == prefix[v]) {
							find = true;
							go[i][j] = v;
						}
				}
				if (!find) go[i][j] = len;
			}
		dp[0][0] = probability[(int) dest[0]];
		dp[0][len] = 1 - dp[0][0];
		for (i = 0; i < m - 1; i++) {
			for (j = 0; j < len - 1; j++)
				for (k = 0; k < n; k++)
					dp[i + 1][go[j][k]] += probability[(int) ch[k][0]] * dp[i][j];
			dp[i + 1][0] += probability[(int) dest[0]] * dp[i][len];
			dp[i + 1][len] += (1 - probability[(int) dest[0]]) * dp[i][len];
		}
		x = 0;
		for (i = 0; i < m; i++)
			x += dp[i][len - 1];
		printf("%.2lf%%\n", x * 100);
	}
	return 0;
}
