// 2008 Kuala Lumpur: Unlock the Lock
// ACM-ICPC Live Archive 4408
#include <cstdio>
#include <cstring>
#define N 10005
bool v[N];
int Q[N];
int l, u, r;
void solve() {
	int i, qh, qe, inq = 1, next, step = 0;
	int code[20];
	for (i = 0; i < r; i++)
		scanf("%d", code + i);
	qh = 0, qe = 0;
	memset(v, 0, sizeof(v));
	v[l] = 1;
	Q[qe++] = l;
	while (qh < qe) {
		next = 0;
		while (inq--) {
			int top = Q[qh++];
			if (top == u) {
				printf("%d\n", step);
				return;
			}
			for (i = 0; i < r; i++) {
				if (!v[(top + code[i]) % 10000]) {
					v[(top + code[i]) % 10000] = 1;
					Q[qe++] = (top + code[i]) % 10000;
					next++;
				}
			}
		}
		step++;
		inq = next;
	}
	printf("Permanently Locked\n");
}
int main() {
	int ca = 1;
	while (scanf("%d%d%d", &l, &u, &r) && l + u + r) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}