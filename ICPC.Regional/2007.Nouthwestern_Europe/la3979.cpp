// 2007 Nouthwestern Europe: Tower Parking
// ACM-ICPC Live Archive 3979
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

void solve(){
	int h, l, x, ans = 0;
	scanf("%d%d", &h, &l);
	for (int i = 0; i < h; i++){
		vector< pair<int, int> > park;
		for (int j = 0; j < l; j++){
			scanf("%d", &x);
			if (x != -1)
				park.push_back(make_pair(x, j));
		}
		sort(park.begin(), park.end());
		for (int j = 0, gate = 0; j < (int)park.size(); j++){
			int d = park[j].second - gate > 0 ? park[j].second - gate : gate - park[j].second;
			ans += min(d, l - d) * 5;
			gate = park[j].second;
		}
		ans += i * 20 * park.size();
	}
	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d\n", &T);
	while (T--)
		solve();
	return 0;
}
