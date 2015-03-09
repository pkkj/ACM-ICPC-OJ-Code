// 2001 Taejon: Modular Multiplication of Polynomials
// ACM-ICPC Live Archive 2323
// POJ 1060

#include <cstdio>
#include <cstring>

const int N = 2005;
int f[N], g[N], h[N], product[N], remain[N];
int df, dg, dh;

void input(int &deg, int poly[]){
	scanf("%d", &deg);
	for (int i = deg - 1; i >= 0; i--)
		scanf("%d", &poly[i]);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		input(df, f), input(dg, g), input(dh, h);
		memset(product, 0, sizeof(product));
		for (int i = 0; i < df; i++)
			for (int j = 0; j < dg; j++)
				product[i + j] ^= f[i] & g[j];

		int dp = df + dg, i, j;
		while (1){
			while (!product[--dp]);
			if (dp + 1 < dh) break;
			for (i = dh - 1, j = dp; i >= 0; i--, j--)
				product[j] ^= h[i];
		}
		printf("%d", dp + 1);
		for (int i = dp; i >= 0; i--)
			printf(" %d", product[i]);
		printf("\n");
	}
	return 0;
}
