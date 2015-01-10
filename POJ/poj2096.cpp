// POJ 2096
// 2004 Northeastern Europe, Northern Subregion: Collecting Bugs
#include <cstdio>
#include <cstring>
#define N 1005
double f[N][N];
int main() {
	int n, s, i, j;
	double ns;
	scanf("%d%d", &n, &s);
	memset(f, 0, sizeof(f));
	ns = n * s;
	for (i = n; i >= 0; i--)
		for (j = s; j >= 0; j--)
			if (i != n || j != s){
				f[i][j] =
					(
					ns
					+ f[i + 1][j + 1] * (n - i)*(s - j)
					+ f[i][j + 1] * i * (s - j)
					+ f[i + 1][j] * (n - i) * j
					) / (ns - i * j );
		}
	printf("%lf\n", f[0][0]);
	return 0;
}
