// 2004 Shanghai: Tian Ji -- The Horse Racing
// ACM-ICPC Live Archive 3266

#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1005;
int horse[2][N], n;

int main(){
	while (scanf("%d", &n) && n){
		for (int i = 0; i < 2; i++){
			for (int j = 0; j < n; j++)
				scanf("%d", &horse[i][j]);
			sort(horse[i], horse[i] + n);
		}

		int ans = 0, b0 = 0, b1 = 0, e0 = n - 1, e1 = n - 1;
		while (b0 <= e0){
			if (horse[0][e0] > horse[1][e1])
				e0--, e1--, ans++;
			else if (horse[0][e0] < horse[1][e1])
				b0++, e1--, ans--;
			else{
				if (horse[0][b0] > horse[1][b1])
					b0++, b1++, ans++;
				else{
					if (horse[0][b0] < horse[1][e1])
						ans--;
					b0++, e1--;
				}
			}
		}
		printf("%d\n", ans * 200);
	}
	return 0;
}