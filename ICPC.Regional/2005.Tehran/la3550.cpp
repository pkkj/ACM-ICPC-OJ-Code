// 2005 Tehran: Hotel
// ACM-ICPC Live Archive 3550
// POJ 2901

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 500 + 5;
const int INF = 1 << 20;
int m, f, r, c;
int capacity[N], price[N], dp[N][N][2], summ1[N], sumf1[N], summ2[N], sumf2[N];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d%d", &m, &f, &r, &c);
		summ1[0] = sumf1[0] = 0;
		for (int i = 1; i <= r; i++){
			scanf("%d%d", &capacity[i], &price[i]);
			summ1[i] = min(capacity[i] + summ1[i - 1], m);
			sumf1[i] = min(capacity[i] + sumf1[i - 1], f);
		}

		summ2[r + 1] = sumf2[r + 1] = 0;
		for (int i = r; i >= 1; i--){
			summ2[i] = min(capacity[i] + summ2[i + 1], m);
			sumf2[i] = min(capacity[i] + sumf2[i + 1], f);
		}
		for (int i = 1; i <= r; i++){
			summ2[i] = max(m - summ2[i], 0);
			sumf2[i] = max(f - sumf2[i], 0);
		}

		memset(dp, 127, sizeof(dp));
		dp[0][0][0] = 0;

		// If the number of couple (c) is even, we can separate them into (c / 2) rooms, 
		// then we can even put other man/women into these rooms to obtain a better answer.
		// Therefore, at most one couple may stay together, when c is odd.
		c %= 2;
		int ans = INF;
		for (int k = 1; k <= r; k++){
			// You can use:
			// for (int x = m; x >= 0; x--)
			// for (int y = f; y >= 0; y--)
			// summ1, sumf1, summ2, sumf2 is just a minor optimization.
			for (int x = summ1[k]; x >= summ2[k]; x--){
				for (int y = sumf1[k]; y >= sumf2[k]; y--){
					for (int z = 0; z <= c; z++){
						int cx = x < capacity[k] ? x : capacity[k];
						int cy = y < capacity[k] ? y : capacity[k];

						dp[x][y][z] = min(dp[x][y][z], dp[x - cx][y][z] + price[k]);
						dp[x][y][z] = min(dp[x][y][z], dp[x][y - cy][z] + price[k]);

						if (x >= 1 && y >= 1 && z >= 1 && capacity[k] >= 2)
							dp[x][y][z] = min(dp[x][y][z], dp[x - 1][y - 1][z - 1] + price[k]);
					}
				}

			}
			ans = min(ans, dp[m][f][0]);
			ans = min(ans, dp[m][f][1]);
		}
		if (ans == INF)
			printf("Impossible\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}
