// 2000 Tehran: Dynamic Declaration Language (DDL)
// ACM-ICPC Live Archive 2054
// POJ 1684

#include <cstdio>
#include <map>
#include <cstring>
#include <cstdlib>
using namespace std;

#define N 500

struct VAR {
	int v, init;
};

int pvar;
char cmd[N][N];
VAR vlist[N];

int isdigit(char ch) {
	return ch >= '0' && ch <= '9';
}

int isletter(char ch) {
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

void throw_error(int line, int id) {
	printf("%d %d\n", line, id);
}

void solve() {
	int n, i, pcmd = 0, pt;
	map<char, int> varmap;

	scanf("%d\n", &n);
	for (i = 0; i < n; i++)
		gets(cmd[i]);
	pvar = 1;
	while (1) {
		if (strcmp(cmd[pcmd], "END") == 0)
			break;
		// 1.DCL
		if (strstr(cmd[pcmd], "DCL")) {
			pt = 0;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			while (isletter(cmd[pcmd][pt]))
				pt++;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			char nvar = cmd[pcmd][pt];
			if (varmap[nvar] == 0) {
				varmap[nvar] = pvar++;
				vlist[varmap[nvar]].init = 0;
				vlist[varmap[nvar]].v = 0;
			} else {
				if (vlist[varmap[nvar]].init == 0)
					throw_error(pcmd + 1, 1);
				else
					vlist[varmap[nvar]].init = 0, vlist[varmap[nvar]].v = 0;
			}
		}
		// 2.INC
		if (strstr(cmd[pcmd], "INC")) {
			pt = 0;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			while (isletter(cmd[pcmd][pt]))
				pt++;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			char nvar = cmd[pcmd][pt];
			if (varmap[nvar] == 0)
				throw_error(pcmd + 1, 2);
			else
				vlist[varmap[nvar]].init = 1, vlist[varmap[nvar]].v++;
		}
		// 3.DEC
		if (strstr(cmd[pcmd], "DEC")) {
			pt = 0;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			while (isletter(cmd[pcmd][pt]))
				pt++;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			char nvar = cmd[pcmd][pt];
			if (varmap[nvar] == 0)
				throw_error(pcmd + 1, 2);
			else
				vlist[varmap[nvar]].init = 1, vlist[varmap[nvar]].v--;
		}
		// 4. =
		if (strstr(cmd[pcmd], "=")) {
			pt = 0;
			char num[100];
			int j = 0;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			char nvar = cmd[pcmd][pt];
			if (varmap[nvar] == 0)
				throw_error(pcmd + 1, 2);
			else {
				while (!isdigit(cmd[pcmd][pt]))
					pt++;
				while (isdigit(cmd[pcmd][pt])) {
					num[j++] = cmd[pcmd][pt++];
				}
				num[j] = 0;
				int value = atoi(num);
				vlist[varmap[nvar]].init = 1, vlist[varmap[nvar]].v = value;

			}
		}

		// 4. GOTO
		if (strstr(cmd[pcmd], "GOTO")) {
			int type = 0;
			pt = 0;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			while (isletter(cmd[pcmd][pt]))
				pt++;
			while (cmd[pcmd][pt] == ' ')
				pt++;
			char nvar;
			if (isletter(cmd[pcmd][pt])) {
				nvar = cmd[pcmd][pt];
				if (varmap[nvar] == 0) {
					throw_error(pcmd + 1, 2);
					pcmd++;
					continue;
				}
				type = 1;
			}
			int j = 0;
			char num[100];
			while (!isdigit(cmd[pcmd][pt]))
				pt++;
			while (isdigit(cmd[pcmd][pt])) {
				num[j++] = cmd[pcmd][pt++];
			}
			num[j] = 0;
			int value = atoi(num);
			if (type == 0 || type == 1 && vlist[varmap[nvar]].v > 0) {
				pcmd = value - 1;
				continue;
			}

		}
		pcmd++;
	}
}

int main() {
	int T, t = 1;
	scanf("%d\n", &T);
	while (T--) {
		printf("%d\n", t++);
		solve();
	}
}
