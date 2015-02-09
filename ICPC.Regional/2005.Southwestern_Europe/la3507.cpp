// 2005 Southwestern Europe: Keep the Customer Satisfied
// ACM-ICPC Live Archive 3507
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
#define N 800005

int n, l;
struct NODE {
	int q, d;
	bool operator <(const NODE &x) const {
		return d < x.d;
	}
};
NODE nl[N];

int main() {
	int T;
	scanf("%d", &T);
	for (int ca = 0; ca < T; ca++){
		if (ca)
			printf("\n");
		priority_queue<int, vector<int>, less<vector<int>::value_type> > Q;
		scanf("%d", &n);
		int i, c = 0;
		for (i = 0; i < n; i++)
			scanf("%d%d", &nl[i].q, &nl[i].d);
		sort(nl, nl + n);
		for (i = 0; i < n; i++) {
			Q.push(nl[i].q);
			c += nl[i].q;
			if (c > nl[i].d) {
				c -= Q.top();
				Q.pop();
			}
		}
		printf("%d\n", Q.size());
	}
	return 0;
}