// 2007 Seoul: PHONE
// ACM-ICPC Live Archive 3903
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
bool X[30][10], has[30];
void pre() {
	memset(X, 0, sizeof(X));
	X[0][1] = X[0][2] = X[0][3] = 1;
	X[1][4] = X[1][5] = X[1][6] = 1;
	X[2][7] = X[2][8] = X[2][9] = 1;
 
	X[3][1] = X[3][4] = X[3][7] = 1;
	X[4][2] = X[4][5] = X[4][8] = 1;
	X[5][3] = X[5][6] = X[5][9] = 1;
 
	X[6][1] = X[6][5] = X[6][9] = 1;
	X[7][3] = X[7][5] = X[7][7] = 1;
 
	X[8][2] = X[8][4] = 1;
	X[9][6] = X[9][8] = 1;
	X[10][2] = X[10][6] = 1;
	X[11][4] = X[11][8] = 1;
 
	X[12][1] = X[12][0] = 1;
	X[13][3] = X[13][0] = 1;
	X[14][4] = X[14][0] = 1;
 
	X[15][6] = X[15][0] = 1;
	X[16][7] = X[16][0] = 1;
	X[17][9] = X[17][0] = 1;
 
	X[18][1] = X[18][8] = 1;
	X[19][3] = X[19][8] = 1;
	X[20][7] = X[20][2] = 1;
	X[21][9] = X[21][2] = 1;
 
	X[22][3] = X[22][4] = 1;
	X[23][9] = X[23][4] = 1;
	X[24][1] = X[24][6] = 1;
	X[25][7] = X[25][6] = 1;
}
 
void solve() {
	int i, j, len;
	char s[100];
	int h1 = 0, h2 = 0, h3 = 0;
	memset(has, 0, sizeof(has));
	scanf("%s", s);
	len = strlen(s);
	for (i = 1; i < len; i++) {
		int a = s[i - 1] - '0';
		int b = s[i] - '0';
		if(a == b)continue;
		if (a > b) swap(a, b);
		if (a == 2 && b == 5) h1 = 1;
		else if (a == 0 && b == 8) h2 = 1;
		else if (a == 2 && b == 8 || a == 0 && b == 2 || a == 5 && b == 8 || a == 0 && b == 5) h3 = 1;
		else {
			for (j = 0; j <= 25; j++) {
				if (X[j][a] && X[j][b]) {
					has[j] = 1;
					break;
				}
			}
		}
	}
	int cnt = 0;
	for (i = 0; i <= 25; i++)
		cnt += has[i];
	if (h3) cnt += 1;
	else if (h3 == 0 && h1 && h2) cnt += 2;
	else cnt += h1 || h2;
	if (cnt <= 3) puts("EXCELLENT");
	else if (cnt == 4) puts("GOOD");
	else puts("BAD");
}
int main() {
	pre();
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}