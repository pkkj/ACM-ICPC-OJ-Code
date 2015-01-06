// CII 3527
// 2005 Central Europe: Find the Clones
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20005
typedef long long ll;
 
int n, m;
int map[100];
short ans[N];
ll num[N];
void get(int x) {
	num[x] = 0;
	for (int i = 0; i < m; i++) {
		char ch = getchar();
		num[x] = (num[x] << 2) | map[(int) ch];
	}
	getchar();
}
int main() {
	map['A'] = 0, map['T'] = 1, map['C'] = 2, map['G'] = 3;
	while (scanf("%d%d\n", &n, &m) && n + m) {
		int i, dup;
		memset(ans, 0, sizeof(ans));
		for (i = 0; i < n; i++)
			get(i);
		sort(num, num + n);
		dup = 1;
		for (i = 1; i < n; i++) {
			if (num[i] == num[i - 1]) dup++;
			else {
				ans[dup]++;
				dup = 1;
			}
		}
		ans[dup]++;
		for (i = 1; i <= n; i++)
			printf("%d\n", ans[i]);
	}
	return 0;
}
