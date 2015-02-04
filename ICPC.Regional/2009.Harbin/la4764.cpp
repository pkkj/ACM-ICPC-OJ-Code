// 2009 Harbin: Bing it
// ACM-ICPC Live Archive 4764
#include <cstdio>
#include <cstring>
#define N 100005
int last[N], n;
int solve(){
	int best = 0, card;
	memset(last, -1, sizeof(last));
	for (int i = 0; i < n; i++){
		scanf("%d", &card);
		if (last[card] != -1){
			int score = last[card] + (card == 999 ? 3 : 1);
			if (score > best)
				best = score;
		}
		last[card] = best;
	}
	return best;
}

int main(){
	while (scanf("%d", &n) && n)
		printf("%d\n", solve());
}