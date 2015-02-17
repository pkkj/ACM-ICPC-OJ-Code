// 2001 Taejon: Calendar Game
// ACM-ICPC Live Archive 2321
// POJ 1082

#include <cstdio>

int main(){
	int T, y, m, d;
	scanf("%d", &T);
	while (T--){
		scanf("%d%d%d", &y, &m, &d);
		if (m == 9 && d == 30 || m == 11 && d == 30)
			puts("YES");
		else
			puts(m % 2 == d % 2 ? "YES" : "NO");
	}
	return 0;
}