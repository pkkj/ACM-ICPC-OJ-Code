// 2000 Tehran: Puzzlestan
// ACM-ICPC Live Archive 2053
// POJ 1683

#include <cstdio>
#include <cstring>
using namespace std;

const int N = 8;
const int SIZE = 200;

char input[N][N], ans[N][N];
int assign[SIZE];
bool used[N][N];
int nr, n, m;

struct RULE {
	char i1, i2, r;	
	bool read() {
		int x1, x2, y1, y2;
		scanf("%d%d %c %d%d", &x1, &y1, &r, &x2, &y2);
		if (x1 == 0)
			return false;
		i1 = input[x1 - 1][y1 - 1], i2 = input[x2 - 1][y2 - 1];
		return true;
	}
};

RULE rules[1000];

bool dfs(int item, int person) {
	if (person == m) 
		person = 0, item++;
	
	if (item == n) 
		return true;
	
	for (int i = 0; i < m; i++) {
		// Find an available item
		if (used[item][i])
			continue;
		assign[input[item][i]] = person;

		// Loop and verify all the rules.
		bool ok = true;
		for (int j = 0; j < nr && ok; j++) {
			char i1 = rules[j].i1, i2 = rules[j].i2;
			if (assign[i1] == -1 || assign[i2] == -1)
				continue;
			if (rules[j].r == 'R' && assign[i1] != assign[i2] || 
				rules[j].r == 'N' && assign[i1] == assign[i2])
				ok = false;
		}

		// If the solution is consistent with the rules, go ahead and try next person/item
		if (ok) {
			ans[person][item] = input[item][i];
			used[item][i] = true;
			if (dfs(item, person + 1))
				return true;
			used[item][i] = false;
		}		
		assign[input[item][i]] = -1;
	}
	return false;
}

int main() {
	int T;
	scanf("%d\n", &T);
	while (T--) {
		nr = 0;
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", input[i]);

		while (rules[nr].read())
			nr++;

		memset(assign, -1, sizeof(assign));
		memset(used, 0, sizeof(used));
		memset(ans, 0, sizeof(ans));

		for (int i = 0; i < m; i++) {
			ans[i][0] = input[0][i];
			assign[input[0][i]] = i;
		}

		dfs(1, 0);

		for (int i = 0; i < m; i++) 
			printf("%s\n", ans[i]);		
		printf("\n");
	}
	return 0;
}
