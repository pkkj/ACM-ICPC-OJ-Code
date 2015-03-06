// 1999 Tehran: (Your)((Term)((Project)))
// POJ 1690

#include <cstdio>
#include <string>
using namespace std;

char s[300];

string solve(int &pos){
	string ans = "";
	char before = 0;
	while (!(s[pos] == ')' || s[pos] == 0)){
		if (s[pos] == '('){
			pos++;
			string tmp = solve(pos);
			if (before == '+' || before == 0 || tmp.length() == 1)
				ans += tmp;
			else
				ans += "(" + tmp + ")";
		}
		else if (s[pos] != ' '){
			ans += s[pos];
			before = s[pos];
		}
		pos++;
	}
	return ans;
}

int main(){
	int T;
	scanf("%d\n", &T);
	while (T--){
		int pos = 0;
		gets(s);
		printf("%s\n", solve(pos).c_str());
	}
	return 0;
}
