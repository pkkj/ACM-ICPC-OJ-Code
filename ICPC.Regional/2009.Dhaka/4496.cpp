// CII 4496
// 2009 Dhaka: A Match Making Problem
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main() {
	int ca = 1, B, H;
	while (scanf("%d%d", &B, &H) && B + H) {
		int x, mm = 10000, i;
		for (i = 0; i < B; i++) {
			scanf("%d", &x);
			mm = min(mm, x);
		}
		for (i = 0; i < H; i++)
			scanf("%d", &x);
		printf("Case %d: %d", ca++, max(B - H, 0));
		if (max(B - H, 0)) printf(" %d", mm);
		printf("\n");
	}
	return 0;
}
