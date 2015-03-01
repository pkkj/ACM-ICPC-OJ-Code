// 2000 Tehran: Number Steps
// ACM-ICPC Live Archive 2052
// POJ 1663
#include <cstdio>

int x1[5100], x2[5100];

void solve() {
	int x, y;
	scanf("%d %d", &x, &y);
	if (x != y && x - y != 2) {
		printf("No Number\n");
		return;
	}
	if (x == y)
		printf("%d\n", x1[x]);
	else
		printf("%d\n", x2[x]);
}


int main() {
	int T;

	x1[0] = 0;
	x1[1] = 1;
	x2[2] = 2;
	x2[3] = 3;
	for (int i = 2; i <= 5001; i++) {
		x1[i] = x1[i - 2] + 4;
		x2[i + 2] = x2[i] + 4;
	}
	scanf("%d", &T);
	while (T--)
		solve();

	return 0;
}

