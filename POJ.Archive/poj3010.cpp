// 2006 Japan Domestic: The Genome Database of All Space Life
// POJ 3010
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define N 130
#define INF 1LL<<29LL
char s[N], subs[N];
int idx, pos;
char ans;
bool isletter(char c) {
	return 'A' <= c && c <= 'Z';
}
bool isdigit(char c) {
	return '0' <= c && c <= '9';
}
struct INFO {
	long long len, time, pos;
	INFO() {
	}
	INFO(long long len, long long time, long long pos) :
		len(len), time(time), pos(pos) {
	}
};
vector<INFO> info[N];
int dfs(int fa) {
	long long sublen = 0, num = 0, thislen = 0;
	while (1) {
		if (s[pos] == ')' || s[pos] == 0) {
			pos++;
			return thislen;
		} else if (isdigit(s[pos])) {
			int here = pos;
			num = 0;
			while (isdigit(s[pos]))
				num = num * 10 + (s[pos++] - '0');

			if (isletter(s[pos])) {
				pos++;
				info[fa].push_back(INFO(1, num, here));
				info[here].push_back(INFO(1, 1, pos - 1));
				thislen += num;
				if (thislen > INF) thislen = INF;
			} else {
				pos++;
				int len = dfs(here);
				long long slen = num * len;
				info[fa].push_back(INFO(len, num, here));
				thislen += slen;
				if (thislen > INF) thislen = INF;
			}

		} else {
			int here = pos;
			sublen = 0;
			while (isletter(s[pos]))
				sublen++, pos++;
			info[fa].push_back(INFO(sublen, 1, here));
			thislen += sublen;
			if (thislen > INF) thislen = INF;
		}
	}
	return -1;
}
char find(int r) {
	if (info[r].size() == 0) return s[r + idx];
	for (int i = 0; i < (int) info[r].size(); i++) {
		long long len = info[r][i].len * info[r][i].time;
		if (idx < len) {
			idx %= info[r][i].len;
			return find(info[r][i].pos);
		}
		idx -= len;
	}
	return 0;
}

int main() {
	while (scanf("%s%d", s, &idx) && s[0] != '0') {
		int root = strlen(s), i;
		pos = 0;
		for (i = 0; i <= root; i++)
			info[i].clear();
		long long len = dfs(root);
		if (idx >= len) printf("0\n");
		else printf("%c\n", find(root));

	}
	return 0;
}
