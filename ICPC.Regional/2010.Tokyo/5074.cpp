// CII 5074
// 2010 Tokyo: Where's Wally
#include <cstdio>
#include <cstring>
#define N 1105
#define M 103757
#define BASE 3
int w, h, p;
char image[N][N], pattern[N][N];
int im[N][N], pa[N][N], pa2[N][N], pa3[N][N];
bool occur[N][N];
int h1[N][N], h2[N];
void decode(int mat[N][N], char c, int x, int y) {
	int pos = y + 5;
	int code;
	if ('A' <= c && c <= 'Z') code = c - 'A';
	else if ('a' <= c && c <= 'z') code = c - 'a' + 26;
	else if ('0' <= c && c <= '9') code = c - '0' + 52;
	else if (c == '+') code = 62;
	else if (c == '/') code = 63;
	while (code) {
		mat[x][pos--] = code & 1;
		code >>= 1;
	}
}
 
int A[N], B[N], P[N];
int kmp(int pos) {
	int i, j = 0, ans = 0;
	for (i = 0; i < h; i++)
		A[i + 1] = h1[i][pos];
	for (i = 1; i <= h; i++) {
		while (j > 0 && B[j + 1] != A[i])
			j = P[j];
		if (B[j + 1] == A[i]) j++;
		if (j == p) {
			j = P[j];
			if (!occur[i - p][pos]) occur[i - p][pos] = 1, ans++;
		}
	}
	return ans;
}
int match() {
	int ans = 0, i, j;
	for (i = 0; i < p; i++)
		B[i + 1] = h2[i];
	P[1] = 0, j = 0;
	for (i = 2; i <= p; i++) {
		while ((j > 0) && (B[j + 1] != B[i]))
			j = P[j];
		if (B[j + 1] == B[i]) j++;
		P[i] = j;
	}
	for (i = 0; i < w - p + 1; i++)
		ans += kmp(i);
	return ans;
}
void hash_pattern(int pa[N][N]) {
	int i, j;
	for (i = 0; i < p; i++) {
		h2[i] = 0;
		for (j = 0; j < p; j++)
			h2[i] = (((h2[i] * BASE) % M) + pa[i][j]) % M;
	}
}
 
void mirror(int pa[N][N], int pa2[N][N]) {
	for (int i = 0; i < p; i++)
		for (int j = 0; j < p; j++)
			pa2[i][p - j - 1] = pa[i][j];
}
void rotate(int pa[N][N], int pa2[N][N]) {
	for (int i = 0; i < p; i++)
		for (int j = 0; j < p; j++)
			pa2[p - j - 1][i] = pa[i][j];
}
void solve() {
	int m1, m2, i, j;
	m1 = (w + 5) / 6;
	m2 = (p + 5) / 6;
	for (i = 0; i < h; i++)
		scanf("%s", image[i]);
	for (i = 0; i < p; i++)
		scanf("%s", pattern[i]);
 
	// Decode the image and pattern
	memset(im, 0, sizeof(im));
	memset(pa, 0, sizeof(pa));
	for (i = 0; i < h; i++) {
		int y = 0;
		for (j = 0; j < m1; j++) {
			decode(im, image[i][j], i, y);
			y += 6;
		}
	}
 
	for (i = 0; i < p; i++) {
		int y = 0;
		for (j = 0; j < m2; j++) {
			decode(pa, pattern[i][j], i, y);
			y += 6;
		}
	}
 
	for (i = 0; i < h; i++)
		for (j = 0; j < w; j++)
			im[i][j]++;
 
	for (i = 0; i < p; i++)
		for (j = 0; j < p; j++)
			pa[i][j]++;
 
	// Hash the image
	int base = 1;
	for (i = 1; i < p; i++)
		base = (base * BASE) % M;
 
	for (i = 0; i < h; i++) {
		int v = 0;
		for (j = 0; j < p; j++)
			v = ((v * BASE) % M + im[i][j]) % M;
		h1[i][0] = v;
		for (j = 0; j < w - p; j++) {
			int t = (im[i][j] * base) % M;
			v = ((((v - t) + M) % M) * BASE + im[i][j + p]) % M;
			h1[i][j + 1] = v;
		}
	}
 
	// Hash the pattern for different rotations and match
	int ans = 0;
	memset(occur, 0, sizeof(occur));
 
	// 1. original
	hash_pattern(pa);
	ans += match();
 
	// 2. rotate 90 degree
	rotate(pa, pa3);
	hash_pattern(pa3);
	ans += match();
 
	// 3. rotate 180 degree
	rotate(pa3, pa2);
	hash_pattern(pa2);
	ans += match();
 
	// 4. rotate 270 degree
	rotate(pa2, pa3);
	hash_pattern(pa3);
	ans += match();
 
	// 5. mirror
	mirror(pa, pa2);
	hash_pattern(pa2);
	ans += match();
 
	// 6. mirror rotate 90 degree
	rotate(pa2, pa3);
	hash_pattern(pa3);
	ans += match();
 
	// 7. mirror rotate 180 degree
	rotate(pa3, pa2);
	hash_pattern(pa2);
	ans += match();
 
	// 8. mirror rotate 270 degree
	rotate(pa2, pa3);
	hash_pattern(pa3);
	ans += match();
 
	printf("%d\n", ans);
}
 
int main() {
	while (scanf("%d%d%d", &w, &h, &p) && w)
		solve();
	return 0;
}
