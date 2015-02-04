// 2009 Harbin: YY and YY Again
// ACM-ICPC Live Archive 4773
#include <cstdio>
#include <cstring>
char s[1000];
int main() {
	while (gets(s)) {
		int len, i, ans = 0;
		len = strlen(s);
		for(i=0;i<len;i++)
			if(s[i] <= 'Z' && s[i] >= 'A') ans += s[i] - 'A' + 1;
		if(ans <= 100)printf("%d\n",ans);
		else printf("INVALID\n");
	}
	return 0;
}
