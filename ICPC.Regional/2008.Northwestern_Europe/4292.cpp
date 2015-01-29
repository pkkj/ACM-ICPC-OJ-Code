// 2008 Northwestern Europe: Matchsticks
// ACM-ICPC Live Archive 4292
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
#define N 105

string minAns[N] = { "", "", "1", "7", "4", "2", "6", "8", "10" };	// The best solution doesn't allow leading 0
string minAns0[N] = { "", "", "1", "7", "4", "2", "0", "8", "01" }; // The best (minimum length first, then minimum number) solution allows leading 0
void preProcess(){
	for (int num = 9; num <= 100; num++){
		long long best = 1LL << 50LL, best0 = 1LL << 50LL;
		for (int i = 2; i <= 7; i++){

			// Check the best previous answer allowing leading 0.
			string s = minAns[i] + minAns0[num - i];
			long long is = _atoi64(s.c_str());
			if (is < best){
				best = is;
				minAns[num] = s;
			}

			s = minAns0[i] + minAns0[num - i];
			is = _atoi64(s.c_str());
			if (minAns0[num].length() == 0 || minAns0[num].length() > s.length() || minAns0[num].length() == s.length() && is < best0){
				best0 = is;
				minAns0[num] = s;
			}
		}
	}
}
int main(){
	int T, n;
	preProcess();
	scanf("%d", &T);
	while (T--){
		scanf("%d", &n);
		// Smallest number
		printf("%s ", minAns[n].c_str());

		// Largest number
		printf(n % 2 ? "7" : "1");
		for (int i = 0; i < n / 2 - 1; i++)
			printf("1");
		printf("\n");
	}
	return 0;
}
