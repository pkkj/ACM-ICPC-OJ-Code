// 2007 World Finals: Consanguine Calculations
// ACM-ICPC Live Archive 3736

#include <cstdio>
#include <cstring>
#include <set>
#include <string>
#include <map>
#include <vector>
using namespace std;
char s1[100], s2[100], s3[100];
map<string, string> MA, MB, MC, MD;
void init() {
	MA["A"] = "AO";
	MA["AB"] = "AB";
	MA["B"] = "BO";
	MA["O"] = "O";

	MB["AA"] = "A";
	MB["AO"] = MB["OA"] = "A";
	MB["AB"] = MB["BA"] = "AB";
	MB["BB"] = "B";
	MB["BO"] = MB["OB"] = "B";
	MB["OO"] = "O";

	MC["+"] = "+-";
	MC["-"] = "-";

	MD["++"] = MD["-+"] = MD["+-"] = "+";
	MD["--"] = "-";
}

set<string> getans(string a, string b) {
	set<string> ans;
	int x, y, u, v;
	string aa = a.substr(0, a.size() - 1);
	string bb = b.substr(0, b.size() - 1);
	string z1 = a.substr(a.size() - 1);
	string z2 = b.substr(b.size() - 1);
	for (x = 0; x < (int)MA[aa].size(); x++)
		for (y = 0; y < (int)MA[bb].size(); y++) {
			for (u = 0; u < (int)MC[z1].size(); u++)
				for (v = 0; v < (int)MC[z2].size(); v++) {
					string ji = "";
					ji += MA[aa][x];
					ji += MA[bb][y];
					string key1 = MB[ji];
					ji = "";
					ji += MC[z1][u];
					ji += MC[z2][v];
					string key2 = MD[ji];
					ans.insert(key1 + key2);
				}
		}
	return ans;
}
void output(set<string> ans) {
	int st = 1;
	if (ans.size() == 0) {
		printf("IMPOSSIBLE");
		return;
	}
	if (ans.size() == 1) {
		printf("%s", ans.begin()->c_str());
		return;
	}
	printf("{");
	for (set<string>::iterator it = ans.begin(); it != ans.end(); it++) {
		if (st) st = 0;
		else printf(", ");
		printf("%s", it->c_str());
	}
	printf("}");
}
void solve() {
	string a = s1, b = s2, c = s3;
	if (s3[0] == '?') {
		set<string> ans = getans(a, b);
		printf("%s %s ", s1, s2);
		output(ans);
		printf("\n");
	}
	else {
		if (a == "?") swap(a, b);
		string sl[8] = { "A+", "B+", "AB+", "O+", "A-", "B-", "AB-", "O-" };
		set<string> ans, ta;
		for (int i = 0; i < 8; i++) {
			ta = getans(a, sl[i]);
			for (set<string>::iterator it = ta.begin(); it != ta.end(); it++) {
				if (*it == c) {
					ans.insert(sl[i]);
					break;
				}
			}
		}
		if (s1[0] == '?') {
			output(ans);
			printf(" %s %s\n", s2, s3);
		}
		else {
			printf("%s ", s1);
			output(ans);
			printf(" %s\n", s3);
		}
	}
}
int main() {
	int ca = 1;
	init();
	while (scanf("%s%s%s", s1, s2, s3) && s1[0] != 'E') {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}