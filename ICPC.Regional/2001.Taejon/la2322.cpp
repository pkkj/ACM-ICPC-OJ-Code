// 2001 Taejon: Wooden Sticks
// ACM-ICPC Live Archive 2322
// POJ 1065

#include <cstdio>
#include <algorithm>
#include <utility>
#include <cstring>
using namespace std;

const int N = 5005;
pair<int, int> stick[N];
bool used[N];

int main(){
	int T, n;
	scanf("%d", &T);
	while (T--){
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d%d", &stick[i].first, &stick[i].second);
		sort(stick, stick + n);

		int ans = 0, left = n;
		memset(used, 0, sizeof(used));
		while (left > 0){
			int i = 0;
			for (i = 0; used[i]; i++);
			ans++;
			pair<int, int> last = stick[i];
			for (int j = i; j < n; j++){
				if (!used[j] && last.second <= stick[j].second){
					last = stick[j];
					used[j] = true;
					left--;
				}
			}
		}
		printf("%d\n", ans);
	}
}