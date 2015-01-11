// POJ 3558
// Northeastern Europe 2005, Western Subregion: Map Generator returns (MG-II)
#include <cstdio>
#include <cstring>
#define N 21
double C[N][N], pow[110], f[N];
 
int main() {
	int i, j, n;
	double p;
	scanf("%d%lf", &n, &p);
	for (i = 0; i <= n; i++) {
		C[i][0] = C[i][i] = 1.0;
		for (j = 0; j < i; j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
	pow[1] = 1.0 - p;
	for (i = 2; i <=((n + 1) / 2) * ((n + 1) / 2); i++)
		pow[i] = pow[i - 1] * (1.0 - p);
	f[1] = 1, f[2] = p;
	for (i = 3; i <= n; i++) {
		f[i] = 1.0;
		for (j = 1; j < i; j++)
			f[i] -= C[i - 1][j - 1] * f[j] * pow[j * (i - j)];
	}
	printf("%.15lf\n", f[n]);
}
