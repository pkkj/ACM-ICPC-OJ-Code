// 1999 Tehran: Counting Rectangles
// POJ 1693

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 100 + 5;

struct POINT{
	int x, y;
};
POINT points[N][2];

int solve(){
	int n, ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d%d%d%d", &points[i][0].x, &points[i][0].y, &points[i][1].x, &points[i][1].y);
		if (points[i][0].x > points[i][1].x) swap(points[i][0].x, points[i][1].x);
		if (points[i][0].y > points[i][1].y) swap(points[i][0].y, points[i][1].y);
	}

	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			if (points[i][0].x == points[i][1].x && points[j][0].x == points[j][1].x){
				int cnt = 0, minx = min(points[i][0].x, points[j][0].x), maxx = max(points[i][0].x, points[j][0].x);
				for (int k = 0; k < n; k++){
					if (points[k][0].y == points[k][1].y &&
						points[i][0].y <= points[k][0].y && points[k][0].y <= points[i][1].y &&
						points[j][0].y <= points[k][0].y && points[k][0].y <= points[j][1].y &&
						points[k][0].x <= minx && maxx <= points[k][1].x)
						cnt++;
				}
				ans += (cnt - 1) * cnt / 2;
			}
		}
	}
	return ans;
}
int main(){
	int T;
	scanf("%d", &T);
	while (T--)
		printf("%d\n", solve());	
	return 0;
}