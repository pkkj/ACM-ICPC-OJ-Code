// 2006 Northeastern Europe: Kickdown
// ACM-ICPC Live Archive 3712

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 105;
char s1[N], s2[N];

int check(char *s1, char *s2){
	int l1 = strlen(s1), l2 = strlen(s2);
	int ans = l1 + l2;
	for (int i = 0; i < l1; i++){
		bool ok = true;
		for (int j = 0; j < l2 && i + j < l1 && ok; j++){
			if (s1[i + j] == '2' && s2[j] == '2')
				ok = false;
		}
		if (ok){
			int len = max(l1, i + l2);
			ans = min(len, ans);
		}
	}
	return ans;
}
int main(){
	while (~scanf("%s%s", s1, s2))
		printf("%d\n", min(check(s1, s2), check(s2, s1)));
	return 0;
}