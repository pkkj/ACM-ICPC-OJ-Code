// 2009 Ningbo: Seat taking up is tough
// ACM-ICPC Live Archive 4755
// HDU 3262
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 55
struct NODE {
    int t, q, id, x, y;
    void get(int i) {
        int h, m;
        scanf("%d:%d %d", &h, &m, &q);
        t = h * 60 + m;
        id = i;
    }
 
};
bool cmp1(const NODE &n1, const NODE &n2) {
    return n1.t < n2.t;
}
bool cmp2(const NODE &n1, const NODE &n2) {
    return n1.id < n2.id;
}
int feel[N][N];
NODE Q[N];
int main() {
    int n, m, q, i, j, k, t;
    while (scanf("%d%d%d", &n, &m, &q) && n) {
        for (i = 1; i <= n; i++)
            for (j = 1; j <= n; j++)
                scanf("%d", &feel[i][j]);
        for (i = 0; i < q; i++)
            Q[i].get(i);
        sort(Q, Q + q, cmp1);
        for (t = 0; t < q; t++) {
            int best = -1, bx, by, num;
            num = Q[t].q;
            for (i = 1; i <= n; i++) {
                for (j = 1; j <= m - num + 1; j++) {
                    int ok = 1;
                    for (k = 0; k < num; k++) {
                        if (feel[i][j + k] == -1) ok = 0;
                    }
                    if (ok) if (feel[i][j] > best) best = feel[i][j], bx = i, by = j;
                }
            }
            if (best != -1) {
                Q[t].x = bx, Q[t].y = by;
                for (k = 0; k < num; k++)
                    feel[bx][by + k] = -1;
            } else {
                for (i = 1; i <= n; i++) {
                    for (j = 1; j <= m; j++) {
                        if (feel[i][j] > best) best = feel[i][j], bx = i, by = j;
                    }
                }
                if (best != -1) Q[t].x = bx, Q[t].y = by, feel[bx][by] = -1;
                else Q[t].x = -1;
            }
        }
        sort(Q, Q + q, cmp2);
        for (i = 0; i < q; i++) {
            if (Q[i].x == -1) printf("-1\n");
            else printf("%d %d\n", Q[i].x, Q[i].y);
        }
    }
 
    return 0;
}