// 2007 Beijing: Color Squares
// ACM-ICPC Live Archive 4025
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100000
struct NODE {
    int v, next;
};
NODE E[N];
int G[N], tot;
int find(int x) {
    int p = x % N, i;
    for (i = G[p]; ~i; i = E[i].next)
        if (E[i].v == x) return i;
    return -1;
}
void add(int x) {
    int p = x % N;
    NODE e = { x, G[p] };
    G[p] = tot;
    E[tot++] = e;
}
int hash(short a[3][3]) {
    int ret = 0, i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            ret = ret * 5 + a[i][j];
    return ret;
}
 
void fhash(int x, short a[3][3]) {
    int i, j;
    for (i = 2; i >= 0; i--)
        for (j = 2; j >= 0; j--)
            a[i][j] = x % 5, x /= 5;
}
int Q[N * 2];
short final[10][10][10][10];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
void bfs() {
    int qh, qe, inq = 1, step = 0;
    short st[3][3], st2[3][3];
    memset(G, -1, sizeof(G));
    memset(final, -1, sizeof(final));
    tot = 0;
    qh = qe = 0;
    Q[qe++] = 0;
    while (qh < qe) {
        int nextr = 0;
        while (inq--) {
            int top = Q[qh++], cnt[4] = { 0 }, i, j, k;
            fhash(top, st);
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    if (st[i][j]) cnt[st[i][j] - 1]++;
            if (final[cnt[0]][cnt[1]][cnt[2]][cnt[3]] == -1 || final[cnt[0]][cnt[1]][cnt[2]][cnt[3]] > step) final[cnt[0]][cnt[1]][cnt[2]][cnt[3]]
                    = step;
            for (k = 0; k < 3; k++)
                st2[1][k] = st[1][k], st2[0][k] = st[2][k], st2[2][k] = st[0][k];
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    int cb = 0, cg = 0, cr = 0;
                    for (k = 0; k < 4; k++) {
                        int nx = i + dx[k], ny = j + dy[k];
                        if (nx < 0 || nx == 3 || ny < 0 || ny == 3) continue;
                        if (st[nx][ny] == 1) cb++;
                        else if (st[nx][ny] == 2) cr++;
                        else if (st[nx][ny] == 3) cg++;
                    }
                    int pre = st[i][j], r1, r2;
                    if (st[i][j] < 1) {
                        st[i][j] = st2[2 - i][j] = 1;
                        r1 = hash(st);
                        r2 = hash(st2);
                        if (find(r1) == -1 && find(r2) == -1) {
                            add(r1);
                            Q[qe++] = r1;
                            nextr++;
                        }
                        st[i][j] = st2[2 - i][j] = pre;
                    }
                    if (st[i][j] < 2 && cb) {
                        st[i][j] = st2[2 - i][j] = 2;
                        r1 = hash(st);
                        r2 = hash(st2);
                        if (find(r1) == -1 && find(r2) == -1) {
                            add(r1);
                            Q[qe++] = r1;
                            nextr++;
                        }
                        st[i][j] = st2[2 - i][j] = pre;
                    }
                    if (st[i][j] < 3 && cb && cr) {
                        st[i][j] = st2[2 - i][j] = 3;
                        r1 = hash(st);
                        r2 = hash(st2);
                        if (find(r1) == -1 && find(r2) == -1) {
                            add(r1);
                            Q[qe++] = r1;
                            nextr++;
                        }
                        st[i][j] = st2[2 - i][j] = pre;
                    }
                    if (st[i][j] < 4 && cb && cr && cg) {
                        st[i][j] = st2[2 - i][j] = 4;
                        r1 = hash(st);
                        r2 = hash(st2);
                        if (find(r1) == -1 && find(r2) == -1) {
                            add(r1);
                            Q[qe++] = r1;
                            nextr++;
                        }
                        st[i][j] = st2[2 - i][j] = pre;
                    }
                }
            }
        }
        inq = nextr;
        step++;
    }
}
int main() {
    int wb, wr, wg, wy, w, T = 1, a, b, c, d, best;
    bfs();
    while (scanf("%d", &wb) && wb) {
        scanf("%d%d%d%d", &wr, &wg, &wy, &w);
        printf("Case %d: ", T++);
        best = 1000000;
        for (a = 0; a < 10; a++)
            for (b = 0; b < 10; b++)
                for (c = 0; c < 10; c++)
                    for (d = 0; d < 10; d++)
                        if (final[a][b][c][d] != -1 && final[a][b][c][d] < best) {
                            if (a * wb + b * wr + c * wg + d * wy >= w) best = final[a][b][c][d];
                        }
        if (best == 1000000) printf("Impossible\n");
        else printf("%d\n", best);
    }
    return 0;
}