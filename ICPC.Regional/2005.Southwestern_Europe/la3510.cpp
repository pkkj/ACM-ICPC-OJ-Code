// 2005 Southwestern Europe: Pixel Shuffle
// ACM-ICPC Live Archive 3510
#include <cstdio>
#include <cstring>
#define N 1026
int n, p;
int a[2][N][N];
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
	return a / gcd(a, b) * b;
}
void init() {
	int tot = 0, i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[0][i][j] = tot++;
}

void rot() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[!p][n - j - 1][i] = a[p][i][j];
}

void rot2() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[!p][j][n - i - 1] = a[p][i][j];
}
void sym() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[!p][i][n - j - 1] = a[p][i][j];
}
void bhsym() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i < n / 2) a[!p][i][j] = a[p][i][j];
			else a[!p][i][n - j - 1] = a[p][i][j];
}
void bvsym() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i < n / 2) a[!p][i][j] = a[p][i][j];
			else a[!p][n - 1 + n / 2 - i][j] = a[p][i][j];

}
void div() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i % 2 == 0) a[!p][i / 2][j] = a[p][i][j];
			else a[!p][n / 2 + i / 2][j] = a[p][i][j];

}
void div2() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i < n / 2) a[!p][i * 2][j] = a[p][i][j];
			else a[!p][(i - n / 2) * 2 + 1][j] = a[p][i][j];
}
void mix2() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j += 2) {
			if (i % 2 == 0) {
				a[!p][i][j / 2] = a[p][i][j];
				a[!p][i + 1][j / 2] = a[p][i][j + 1];
			}
			else {
				a[!p][i - 1][j / 2 + n / 2] = a[p][i][j];
				a[!p][i][j / 2 + n / 2] = a[p][i][j + 1];
			}
		}

}
void mix() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j += 2) {
			if (i % 2 == 0) {
				a[!p][i][j] = a[p][i][j / 2];
				a[!p][i][j + 1] = a[p][i + 1][j / 2];
			}
			else {
				a[!p][i][j] = a[p][i - 1][j / 2 + n / 2];
				a[!p][i][j + 1] = a[p][i][j / 2 + n / 2];
			}
		}
}
char cmd[50][10], line[10000];
void solve() {
	char s[10];
	int ncmd = 0, begin = 0;
	gets(line);
	while (begin < strlen(line)){
		sscanf(line + begin, "%s", cmd[++ncmd]);
		begin += strlen(cmd[ncmd]);
		while (line[begin] == ' ')
			begin++;
	}

	p = 0;
	while (ncmd) {
		strcpy(s, cmd[ncmd]);
		ncmd--;
		if (strcmp(s, "id") == 0 || strcmp(s, "id-") == 0)
			continue;
		if (strcmp(s, "rot") == 0) rot();
		else if (strcmp(s, "rot-") == 0) rot2();
		else if (strcmp(s, "sym") == 0 || strcmp(s, "sym-") == 0) sym();
		else if (strcmp(s, "bhsym") == 0 || strcmp(s, "bhsym-") == 0) bhsym();
		else if (strcmp(s, "bvsym") == 0 || strcmp(s, "bvsym-") == 0) bvsym();
		else if (strcmp(s, "div") == 0) div();
		else if (strcmp(s, "div-") == 0) div2();
		else if (strcmp(s, "mix") == 0) mix();
		else if (strcmp(s, "mix-") == 0) mix2();
		p = !p;

	}
}
bool v[N][N];

int dfs(int x, int y) {
	int ret = 0;
	do {
		v[x][y] = 1;
		ret++;
		int nx = a[p][x][y] / n, ny = a[p][x][y] % n;
		x = nx, y = ny;
	} while (!v[x][y]);
	return ret;
}

void calc() {
	int i, j, ans = 1;
	memset(v, 0, sizeof(v));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (!v[i][j])
				ans = lcm(ans, dfs(i, j));
	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca) printf("\n");
		scanf("%d\n", &n);
		init();
		solve();
		calc();
	}
	return 0;
}
