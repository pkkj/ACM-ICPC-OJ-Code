// HDU 2293
// The 4th Baidu Cup Final: Name PK 
#include <cstdio>
#include <cstring>
char n1[100], n2[100];
 
int calchp(char *s) {
	int len, i, ans = 0;
	len = strlen(s);
	for (i = 0; i < len; i++) {
		ans += (83 - (int) s[i])*(83 - (int) s[i]);
		ans %= 97;
	}
	ans = 300 - ans;
	return ans;
}
 
int calcstr(char *s) {
	int len, i, ans = 1;
	len = strlen(s);
	for (i = 0; i < len; i++) {
		ans *= ((int) s[i]);
		ans %= 79;
	}
	ans = 22 + ans % 79;
	return ans;
}
 
int calcspd(char *s) {
	int len, i, j, ans = 0;
	len = strlen(s);
	for (i = 0; i < len; i++) {
		for (j = i + 1; j < len; j++) {
			ans += ((int) s[i] * (int) s[j]);
			ans %= 11;
		}
	}
	return ans % 11;
}
void solve() {
 
	int hp1, hp2, str1, str2, spd1, spd2;
	scanf("%s %s", n1, n2);
	hp1 = calchp(n1), hp2 = calchp(n2);
	str1 = calcstr(n1), str2 = calcstr(n2);
	spd1 = calcspd(n1), spd2 = calcspd(n2);
	int t = 1;
	while (1) {
		t++;
		if (t % (20 - spd1) == 0) hp2 -= str1;
		if (t % (20 - spd2) == 0) hp1 -= str2;
		if(hp1 <= 0 || hp2 <= 0)
			break;
	}
	if(hp1 <= 0 && hp2 <= 0)
		puts("tie");
	else if(hp1 <= 0)
		puts("lose");
	else
		puts("win");
 
}
int main() {
	int T;
	scanf("%d\n", &T);
	while (T--)
		solve();
	return 0;
}
