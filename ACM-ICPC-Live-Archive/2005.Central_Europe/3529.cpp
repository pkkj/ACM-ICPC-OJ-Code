// CII 3529
// 2005 Central Europe: Widget Factory
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
using namespace std;
#define N 305
#define M 7
int mm[N][N];
int iabs(int x) {
	return x < 0 ? -x : x;
}
int gcd(int m, int n) {
	int r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
 
int lcm(int a, int b) {
	return a * b / gcd(a, b);
}
int x[N];
int gauss(int var, int equ) {
	int i, j, k, row, col;
	for (k = col = 0; k < equ && col < var; k++, col++) {
		row = k;
		for (i = k + 1; i < equ; i++)
			if (iabs(mm[i][col]) > iabs(mm[row][col])) row = i;
		if (k != row) for (i = k; i <= var; i++)
			swap(mm[k][i], mm[row][i]);
		if (mm[k][col] == 0) {
			k--;
			continue;
		}
		for (i = k + 1; i < equ; i++)
			if (mm[i][col]) {
				int ll = lcm(iabs(mm[i][col]), iabs(mm[k][col]));
				int tk = ll / mm[k][col], ti = ll / mm[i][col];
				for (j = col; j <= var; j++)
					mm[i][j] = (mm[i][j] * ti - mm[k][j] * tk) % M;
			}
	}
	for (i = k; i < equ; i++)
		if (mm[i][col]) return -1;
	if (var - k) return var - k;
	for (i = var - 1; i >= 0; i--) {
		int t = mm[i][var];
		for (j = i + 1; j < var; j++)
			t -= mm[i][j] * x[j];
		while (t % mm[i][i])
			t += 7;
		x[i] = t / mm[i][i];
	}
	return 0;
}
int n, m;
map<string, int> MM;
void solve() {
	int i, t, j;
	char s1[10], s2[10];
	memset(mm, 0, sizeof(mm));
	for (i = 0; i < m; i++) {
		scanf("%d%s%s", &t, s1, s2);
		mm[i][n] = (MM[string(s2)] - MM[string(s1)] + 1 + M) % M;
		while (t--) {
			scanf("%d", &j);
			mm[i][j - 1]++;
			mm[i][j - 1] %= M;
		}
	}
	int ans = gauss(n, m);
	if (ans == -1) printf("Inconsistent data.\n");
	else if (ans) printf("Multiple solutions.\n");
	else {
		for (i = 0; i < n; i++) {
			while (x[i] < 3)
				x[i] += 7;
			while (x[i] > 9)
				x[i] -= 7;
			if (i)
				printf(" ");
			printf("%d", x[i]);
		}
		printf("\n");
	}
}
 
void init() {
	MM["MON"] = 0, MM["TUE"] = 1, MM["WED"] = 2, MM["THU"] = 3;
	MM["FRI"] = 4, MM["SAT"] = 5, MM["SUN"] = 6;
}
int main() {
	init();
	while (scanf("%d%d", &n, &m) && n + m) 
		solve();
	return 0;
}
