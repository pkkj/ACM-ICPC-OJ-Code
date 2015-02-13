// 2009 Southwestern Europe: Darts
// Solution II
// ACM-ICPC Live Archive 4507
// POJ 3876
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define A 0
#define B 1
#define N 505
int target[] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5, 20, 1};
const int SIZE = 20;
bool vis[2][N][N];
double ans[2][N][N];

double calc(int player, int n, int m){
	if (vis[player][n][m])
		return ans[player][n][m];

	if (n >= SIZE || m >= SIZE){
		if (player == A){
			for (int i = 1; i <= SIZE; i++)
				ans[A][n][m] += 1 - calc(B, n - i >= 0 ? n - i : n, m);
			ans[A][n][m] /= 20.0;
			vis[A][n][m] = true;
		}
		else if (player == B){
			for (int i = 0; i < SIZE; i++){
				double p = (
					calc(A, n, m - target[i] >= 0 ? m - target[i] : m) +
					calc(A, n, m - target[i + 1] >= 0 ? m - target[i + 1] : m) +
					calc(A, n, m - target[i + 2] >= 0 ? m - target[i + 2] : m)) / 3.0;
				ans[B][n][m] = max(ans[B][n][m], 1 - p);
			}
			vis[B][n][m] = true;
		}
	}
	else{
		double a1 = 1, a2;
		for (int i = 1; i <= n; i++)
			a1 -= calc(B, n - i, m) / 20.0;		
		a2 = (n - 20.0) / 20.0;

		for (int aim = 0; aim < SIZE; aim++){
			double b1 = 1, b2 = 0;
			for (int j = 0; j < 3; j++){
				if (target[aim + j] > m) 
					b2 -= 1 / 3.0;				
				else
					b1 -= calc(A, n, m - target[aim + j]) / 3.0;
			}
			double pA = (a1 + a2 * b1) / (1 - a2 * b2);
			double pB = (b1 + a1 * b2) / (1 - a2 * b2);
			if (pB >= ans[B][n][m]){
				ans[A][n][m] = pA;
				ans[B][n][m] = pB;
			}
		}
		vis[A][n][m] = vis[B][n][m] = true;
	}

	return ans[player][n][m];
}

int main(){
	memset(vis, 0, sizeof(vis));
	memset(ans, 0, sizeof(ans));
	for (int i = 0; i < N; i++){
		ans[A][0][i] = ans[B][i][0] = 1;
		vis[A][0][i] = vis[A][i][0] = vis[B][i][0] = vis[B][0][i] = true;
	}

	int n;
	while (scanf("%d", &n) && n)
		printf("%.10lf %.10lf\n", calc(A, n, n), calc(B, n, n));
	
	return 0;
}