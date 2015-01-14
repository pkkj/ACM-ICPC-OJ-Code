// 2005 Tokyo: Colored Cubes
// CII 3401
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
int ST[24][6] = { { 0, 1, 2, 3, 4, 5 }, { 0, 2, 4, 1, 3, 5 }, { 0, 4, 3, 2, 1, 5 }, { 0, 3, 1, 4, 2, 5 }, { 3, 1, 0, 5,
        4, 2 }, { 3, 0, 4, 1, 5, 2 }, { 3, 4, 5, 0, 1, 2 }, { 3, 5, 1, 4, 0, 2 }, { 5, 1, 3, 2, 4, 0 }, { 5, 3, 4, 1,
        2, 0 }, { 5, 4, 2, 3, 1, 0 }, { 5, 2, 1, 4, 3, 0 }, { 2, 1, 5, 0, 4, 3 }, { 2, 5, 4, 1, 0, 3 }, { 2, 4, 0, 5,
        1, 3 }, { 2, 0, 1, 4, 5, 3 }, { 4, 0, 2, 3, 5, 1 }, { 4, 2, 5, 0, 3, 1 }, { 4, 5, 3, 2, 0, 1 }, { 4, 3, 0, 5,
        2, 1 }, { 1, 0, 3, 2, 5, 4 }, { 1, 3, 5, 0, 2, 4 }, { 1, 5, 2, 3, 0, 4 }, { 1, 2, 0, 5, 3, 4 } };
int n;

int cube[4][6], buffer[4][6];
map<string, int> table;
int id, best;
int getcolor(char *cmd) {
    string str = cmd;
    if (table[str] == 0) table[str] = id++;
    return table[str];
}
char cmd[100];
void init() {
    id = 1;
    table.clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%s", cmd);
            cube[i][j] = getcolor(cmd);
        }
    }
    for (int i = 0; i < 6; i++) {
        buffer[0][i] = cube[0][i];
    }
}
int hash[6][30];
void dfs(int d) {
    int i, j, k, diff = 0, tmp = 0;
    if (d >= n) {
        memset(hash, 0, sizeof(hash));
        for (j = 0; j < 6; j++) {
            diff = 0;
            for (i = 0; i < n; i++) {
                if (hash[j][buffer[i][j]] == 0) diff++;
                hash[j][buffer[i][j]]++;
            }
            if (diff == 2) {
                for (i = 0; i < n; i++)
                    if (hash[j][buffer[i][j]] != 2) {
                        diff--;
                        break;
                    }
            } else diff--;
            tmp += diff;
        }

        if (tmp < best) best = tmp;
        return;
    }
    for (k = 0; k < 24; k++) {
        for (i = 0; i < 6; i++)
            buffer[d][i] = cube[d][ST[k][i]];
        dfs(d + 1);
    }

}
int solve() {
    init();
    if (n == 1) return 0;
    best = 24;
    dfs(1);
    return best;
}
int main() {
    while (scanf("%d", &n) && n)
        printf("%d\n", solve());
    return 0;
}

