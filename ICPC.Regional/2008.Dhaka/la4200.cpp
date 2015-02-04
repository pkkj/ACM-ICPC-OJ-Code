// 2008 Dhaka: Find the Format String
// ACM-ICPC Live Archive 4200
#include <cstdio>
#include <cstring>
#define N 150
char s1[N], s2[N];
int fb[N], n;
void solve() {
	int maxch = 0, count = 0, min = 255, i;
	memset(fb, 0, sizeof(fb));
	bool end = false;
	for (i = 0; i < n; i++) {
		scanf("%s%s", s1, s2);
		int l1 = strlen(s1), l2 = strlen(s2);
		if (l1 < l2) end = 1;
		if (end) continue;
		int i = 1;
		for (; s1[i] != '"' && s2[i] != '"' && !end; i++) {
			if (s1[i] == s2[i]) {
				if (fb[s1[i]] == -1) end = 1;
				else fb[s1[i]] = 1;
			} else end = true;
		}
		if (s1[i] != '"') {
			if (fb[s1[i]] == 1) end = 1;
			else fb[s1[i]] = -1;
		}
	}
	if (end) {
		printf("I_AM_UNDONE\n");
		return;
	}
	for (i = '0'; i <= 'z'; i++) {
		if (i >= '0' && i <= '9' || i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {
			if (fb[i] == 1) maxch = i;
			else if (fb[i] == -1) count++;
			else if (min > i) min = i;
		}
	}
 
	if (count == 62) {
		printf("I_AM_UNDONE\n");
	} else if (maxch == 0) {
		printf("[%c]\n", min);
	} else {
		printf("[");
		for (i = '0'; i <= maxch; i++)
			if (i >= '0' && i <= '9' || i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') if (fb[i] != -1) printf("%c", i);
		printf("]\n");
	}
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
