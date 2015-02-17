// 2001 Taejon: Moving Tables
// ACM-ICPC Live Archive 2326
// POJ 1083

#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct WORK{
	int a, b, used;
};

int compare(const void* a, const void *b){
	if ((*(WORK *)a).a == (*(WORK *)b).a)
		return (*(WORK *)a).b > (*(WORK *)b).b ? 1 : -1;
	return (*(WORK *)a).a > (*(WORK *)b).a ? 1 : -1;
}

int main(){
	int T;
	WORK queue[210];
	scanf("%d", &T);
	while (T--) {
		int i, j, n, time = 0;
		scanf("%d", &n);

		for (i = 0; i < n; i++) {
			scanf("%d%d", &queue[i].a, &queue[i].b);
			if (queue[i].a > queue[i].b) 
				swap(queue[i].a, queue[i].b);
			queue[i].used = 0;
		}

		qsort(queue, n, sizeof(queue[0]), compare);
		// Check the task one by one. 
		for (i = 0; i < n; i++) {
			if (!queue[i].used) {
				queue[i].used = 1;
				int u = i;
				// Find another moving task
				for (j = i + 1; j < n; j++) {
					if (!queue[j].used) {
						if ((queue[j].a > queue[u].b + 1) || (queue[j].a - 1 == queue[u].b) && (queue[u].b % 2 == 0)) {
							queue[j].used = 1;
							u = j;
						}
					}
				}
				time++;
			}
		}
		printf("%d\n", time * 10);
	}
	return 0;
}

