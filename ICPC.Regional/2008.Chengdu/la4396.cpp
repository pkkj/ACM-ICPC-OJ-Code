// 2008 Chengdu: Slides
// ACM-ICPC Live Archive 4396
// HDU 2478
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100005

struct RECT{
	int x1, y1, x2, y2;
	RECT(){}
	RECT(int x1, int y1, int x2, int y2) :x1(x1), y1(y1), x2(x2), y2(y2){}
	void read(){
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
	}
	RECT intersect(RECT &other){
		RECT rect = RECT(max(x1, other.x1), max(y1, other.y1), min(x2, other.x2), min(y2, other.y2));
		if (rect.x1 > rect.x2 || rect.y1 > rect.y2)
			rect = RECT(0, 0, 0, 0);
		return rect;
	}
	int area(){
		return (x2 - x1) * (y2 - y1);
	}
};

RECT rect[N], forward[N], backward[N];
int solve(){
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		rect[i].read();
	if (n == 1) return 0;

	::forward[1] = rect[1];
	for (int i = 2; i <= n; i++)
		::forward[i] = rect[i].intersect(::forward[i - 1]);
	
	backward[n] = rect[n];
	for (int i = n - 1; i >= 1; i--)
		backward[i] = rect[i].intersect(backward[i + 1]);
	
	int ans = max(::forward[n-1].area(), backward[2].area());
	for (int i = 2; i + 1 <= n; i++)
		ans = max(ans, ::forward[i-1].intersect(backward[i+1]).area());
	return ans;
}

int main(){
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());
	return 0;
}