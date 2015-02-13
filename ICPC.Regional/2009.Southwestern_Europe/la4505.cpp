// 2009 Southwestern Europe: Working at the Restaurant
// ACM-ICPC Live Archive 4505
// POJ 3874
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main() {
	int n, x, begin = true;
	char cmd[10];

	while (scanf("%d", &n) && n) {
		int pile1 = 0, pile2 = 0;
		if (begin)
			begin = false;
		else
			printf("\n");

		while (n--) {
			scanf("%s%d", cmd, &x);
			if (strcmp(cmd, "DROP") == 0) {
				printf("DROP 2 %d\n", x);
				pile2 += x;
			} else {
				if (pile1) {
					int take = min(x, pile1);
					printf("TAKE 1 %d\n", take);
					x -= take, pile1 -= take;
				}
				if (x) {
					printf("MOVE 2->1 %d\n", pile2);
					pile1 += pile2;
					pile2 = 0;
					x = min(pile1, x);
					printf("TAKE 1 %d\n", x);
					pile1 -= x;
				}
			}
		}
	}
	return 0;
}
