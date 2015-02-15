// 2005 Japan Domestic: Ohgas' Fortune
// POJ 2683
#include <stdio.h>
double rate;
int base, year, cut;
int comp() {
	int i, ans = base;
	for (i = 1; i <= year; i++)
		ans = (int) ((double) ans * (rate + 1)) - cut;
	return ans;
}

int single() {
	int sumrate = 0, i, ans = base;
	for (i = 1; i <= year; i++) {
		sumrate += (int) ((double) ans * rate);
		ans -= cut;
	}
	return ans + sumrate;

}
int main() {
	int T, op, i, max;
	scanf("%d", &T);
	while (T--) {
		max = 0;
		scanf("%d%d%d", &base, &year, &op);
		for (i = 0; i < op; i++) {
			int c_s, t;
			scanf("%d%lf%d", &c_s, &rate, &cut);
			t = c_s ? comp() : single();
			if (t > max)
				max = t;
		}
		printf("%d\n", max);
	}
	return 0;
}



