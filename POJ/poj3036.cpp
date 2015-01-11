// POJ 3036
// Nordic 2006: Honeycomb Walk
#include <cstdio>
int main() {
	int ans[] = { 0, 0, 6, 12, 90, 360, 2040, 10080, 54810, 290640, 1588356,
			8676360, 47977776, 266378112, 1488801600 };
	int T, i;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &i);
		printf("%d\n", ans[i]);
	}
	return 0;
}

