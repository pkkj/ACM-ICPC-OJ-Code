// 2006 Rocky Mountain: Knots
// ACM-ICPC Live Archive 3582

#include <cstdio>
double calc(int n) {
	double ans = 1;
	int i;
	for (i = n - 2; i > 1; i -= 2)
		ans = (double) i / (double) (i + 1) * ans;
	return ans;
}
int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		printf("%.5lf\n", calc(n));
	}
	return 0;
}