// 2002 Kaohsiung: Poker Card Game
// POJ 1339

#include <cstdio>
#include <queue>
using namespace std;

int main(){
	int T, n, x, ans;
	scanf("%d", &T);
	while (T--){
		priority_queue<int> q;
		ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			scanf("%d", &x);
			q.push(-x);
		}

		while (q.size() > 1){
			int a = q.top();
			q.pop();
			int b = q.top();
			q.pop();

			q.push(a + b);
			ans += a + b;
		}

		printf("%d\n", -ans);
	}
	return 0;
}