// 2001 Taejon: Flip and Shift
// ACM-ICPC Live Archive 2325
// POJ 1063

#include <cstdio>

int main(){
	int T, n, c1, c2, x;
	scanf("%d", &T);
	while (T--){
		scanf("%d", &n);
		c1 = c2 = 0;
		for (int i = 0; i < n; i++){
			scanf("%d", &x);
			i % 2 == 0 ? c1 += x : c2 += x;
		}
		printf(n % 2 || c1 - c2 == 1 || c2 - c1 == 1 || c1 == c2 ? "YES\n" : "NO\n");
	}
	return 0;
}