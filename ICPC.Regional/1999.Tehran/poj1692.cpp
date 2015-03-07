// 1999 Tehran: Crossed Matchings
// POJ 1692

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 101

int s1[N], s2[N], match[N][N];

int main() {
	int T, n1, n2, i, j, k1, k2;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n1, &n2);
		memset(match, 0, sizeof(match));
		for (i = 1; i <= n1; i++)
			scanf("%d", &s1[i]);
		for (i = 1; i <= n2; i++)
			scanf("%d", &s2[i]);
		for (i = 1; i <= n1; i++)
			for (j = 1; j <= n2; j++) {
				match[i][j] = max(match[i][j - 1], match[i - 1][j]);
				if (s1[i] == s2[j])
					continue;
				for (k1 = i - 1; k1 >= 1; k1--)
					if (s1[k1] == s2[j])
						for (k2 = j - 1; k2 >= 1; k2--)
							if (s1[i] == s2[k2]) {
								match[i][j] = max(match[i][j], match[k1 - 1][k2 - 1] + 2);
								break;
							}
			}

		printf("%d\n", match[n1][n2]);
	}
	return 0;
}
