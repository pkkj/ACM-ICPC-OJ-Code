// 2008 Northwestern Europe: Equilibrium Mobile
// ACM-ICPC Live Archive 4286 
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
char s[400000];
map<long long, int> cnt;
int main() {
	int T;
	//freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		int len, i, dep, total = 0, best = 0;
		cnt.clear();
		scanf("%s", s);
		len = strlen(s);
		for (i = dep = 0; i < len;) {
			if (s[i] == '[') i++, dep++;
			else if (s[i] == ']') i++, dep--;
			else if (s[i] == ',') i++;
			else {
				int x = 0;
				while (i < len && s[i] >= '0' && s[i] <= '9')
					x = x * 10 + s[i++] - '0';
				total++;
				int v = ++cnt[(long long)x << dep];
				best = max(v, best);
			}
		}
		printf("%d\n", total - best);
	}
	return 0;
}