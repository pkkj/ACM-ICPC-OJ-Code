// 2007 Nouthwestern Europe: Obfuscation
// ACM-ICPC Live Archive 3978
#include <cstdio>
#include <cstring>
#define N 1005
#define M 10005

struct WORD {
	char be, end;
	int len, st[26];
};

WORD wl[M];
bool begin;
int cnt[N][26], len, n;
char cmd[N], word[M][105], *s;
void init() {
	int i, j;
	gets(cmd + 1);
	memset(wl, 0, sizeof(wl));
	memset(cnt, 0, sizeof(cnt));
	scanf("%d\n", &n);
	for (i = 0; i < n; i++) {
		gets(word[i]);
		s = word[i];
		len = strlen(s);
		wl[i].be = s[0], wl[i].end = s[len - 1];
		wl[i].len = len;
		for (j = 0; j < len; j++)
			wl[i].st[s[j] - 'a']++;
	}
	cmd[0] = ' ';
	len = strlen(cmd);
	for (i = 1; i < len; i++) {
		for (j = 0; j < 26; j++)
			cnt[i][j] = cnt[i - 1][j];
		cnt[i][cmd[i] - 'a']++;
	}
}

int f[N], amg[N], pre[N];
int dp() {
	int i, j;
	memset(amg, 0, sizeof(amg));
	memset(f, 0, sizeof(f));
	f[0] = 1, pre[0] = -1;
	for (i = 0; i < len - 1; i++) {
		if (f[i] == 1) {
			for (j = 0; j < n; j++) {
				if (i + wl[j].len < len && cmd[i + 1] == wl[j].be && cmd[i + wl[j].len] == wl[j].end) {
					int ok = 1, k = 0, p1, p2;
					p1 = i, p2 = i + wl[j].len;
					while (k < 26) {
						if (cnt[p2][k] - cnt[p1][k] != wl[j].st[k]) {
							ok = 0;
							break;
						}
						k++;
					}
					if (ok == 1) {
						if (f[i + wl[j].len] || amg[i] == 1) amg[i + wl[j].len] = 1;
						f[i + wl[j].len] = 1;
						pre[i + wl[j].len] = j;
					}
				}
			}
		}
	}
	if (f[len - 1] && amg[len - 1] == 0) return 1;
	if (f[len - 1] && amg[len - 1]) return -1;
	return 0;
}

void output(int p) {
	if (pre[p] == -1)
		return;
	int np;
	np = p - strlen(word[pre[p]]);
	output(np);
	if (begin) begin = false;
	else printf(" ");
	printf("%s", word[pre[p]]);
}
void solve() {
	int ret;
	init();
	ret = dp();
	if (ret == 0) printf("impossible\n");
	else if (ret == -1) printf("ambiguous\n");
	else {
		begin = true;
		output(len - 1);
		printf("\n");
	}

}
int main() {
	int T;
	scanf("%d\n", &T);
	while (T--)
		solve();
	return 0;
}

