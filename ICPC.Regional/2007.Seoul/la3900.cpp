// 2007 Seoul: Molar mass
// ACM-ICPC Live Archive 3900
#include <cstdio>
#include <cstring>
#define C 12.01
#define N 14.01
#define O 16.00
#define H 1.008
char cmd[100000], num[5];
bool isletter(char ch) {
	return ch >= 'A' && ch <= 'Z';
}
 
void solve() {
	double ans = 0;
	int i, j, len, x;
	char pre = 0;
	scanf("%s", cmd);
	len = strlen(cmd);
	for (i = 0; i < len; i++) {
		if (isletter(cmd[i])) {
			if (pre) {
				if (j) {
					num[j] = 0;
					sscanf(num, "%d", &x);
				} else x = 1;
				if (pre == 'N') ans += (double) x * N;
				else if (pre == 'O') ans += (double) x * O;
				else if (pre == 'C') ans += (double) x * C;
				else if (pre == 'H') ans += (double) x * H;
			}
			j = 0;
			pre = cmd[i];
		} else num[j++] = cmd[i];
	}
	if (pre) {
		if (j) {
			num[j] = 0;
			sscanf(num, "%d", &x);
		} else x = 1;
		if (pre == 'N') ans += (double) x * N;
		else if (pre == 'O') ans += (double) x * O;
		else if (pre == 'C') ans += (double) x * C;
		else if (pre == 'H') ans += (double) x * H;
	}
	printf("%.3lf\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}