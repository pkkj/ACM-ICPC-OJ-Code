// 2008 Northwestern Europe: Shuffle
// ACM-ICPC Live Archive 4294
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 200005;
int s, len;
bool validBackward[N], validForward[N];
int cnt[N], seq[N];

void solve() {
	memset(cnt, 0, sizeof(cnt));
	memset(validBackward, 0, sizeof(validBackward));
	memset(validForward, 0, sizeof(validForward));
	int diffNum = 0, ans = 0;
	for (int i = 0; i < len + s; i++) {

		if (i - s + 1 >= 0 && diffNum == s)
			validBackward[i - s] = true;

		// remove the old number at i-s
		if (i - s >= 0) {
			cnt[seq[i - s]]--;
			if (cnt[seq[i - s]] == 0)
				diffNum--;
		}

		// add the new number at i
		if (i >= len)
			diffNum++;
		else {
			if (cnt[seq[i]] == 0)
				diffNum++;
			cnt[seq[i]]++;
		}

		if (i < s && diffNum == i + 1)
			validForward[i] = true;

	}
	for (int i = 0; i < s; i++) {
		int ok = 1;

		// all previous numbers should be different
		if (i != 0 && !validForward[i - 1])
			continue;
		// all number from i should be divided into intervals with different numbers
		for (int j = i; j < len && ok; j += s)
			if (!validBackward[j])
				ok = 0;

		ans += ok;
	}

	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &s, &len);
		for (int i = 0; i < len; i++)
			scanf("%d", &seq[i]);
		solve();
	}
	return 0;
}
