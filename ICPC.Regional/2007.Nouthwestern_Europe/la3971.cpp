// 2007 Nouthwestern Europe: Assemble
// ACM-ICPC Live Archive 3971
#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 1005
using namespace std;

struct ITEM {
	int p, q;
	char name[30];
};
ITEM list[N];
int n, budget;
int cmp(const ITEM &a, const ITEM &b) {
	int f = strcmp(a.name, b.name);
	if (f)
		return f > 0 ? 1 : 0;
	return a.p < b.p;
}

int check(int q) {
	int i, tt = 0, match = 0;
	if (list[0].q >= q)
		match = 1, tt += list[0].p;
	if (tt > budget)
		return 0;
	for (i = 1; i < n; i++) {
		if (strcmp(list[i].name, list[i - 1].name))
			match = 0;
		if (!match) {
			if (list[i].q >= q)
				tt += list[i].p, match = 1;
			if (tt > budget)
				return 0;
			if ((i == n - 1 || strcmp(list[i].name, list[i + 1].name)) && match == 0)
				return 0;
		}
	}
	return tt > budget ? 0 : 1;
}

int solve() {
	int i, qmax = -1, qmin = 1000000005;
	char t2[25];
	scanf("%d%d", &n, &budget);
	for (i = 0; i < n; i++) {
		scanf("%s%s%d%d", list[i].name, t2, &list[i].p, &list[i].q);
		if (list[i].q > qmax)
			qmax = list[i].q;
		if (list[i].q < qmin)
			qmin = list[i].q;
	}
	sort(list, list + n, cmp);
	while (qmin <= qmax) {
		int mid = (qmin + qmax) / 2;
		if (check(mid))
			qmin = mid + 1;
		else
			qmax = mid - 1;
	}
	return qmax;
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}
