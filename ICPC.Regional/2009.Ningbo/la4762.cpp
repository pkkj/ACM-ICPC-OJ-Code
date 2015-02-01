// 2009 Ningbo: P2P File Sharing System
// ACM-ICPC Live Archive 4762
// HDU 3269
#include <cstdio>
#include <cstring>
 
#define N 25
#define TIME 1005
int speed[N][N];
int fini[N], tmp[N];
int happen[TIME][N];
bool start[TIME], on[N][TIME];
void solve() {
    int n, m, time, ns, size, i, j, k, s, t;
    scanf("%d%d%d%d", &n, &time, &ns, &size);
    memset(fini, 0, sizeof(fini));
    memset(happen, -1, sizeof(happen));
    memset(start, 0, sizeof(start));
    memset(on, 0, sizeof(on));
    for (i = 0; i < ns; i++) {
        scanf("%d", &k);
        fini[k - 1] = size;
    }
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &speed[i][j]);
    for (i = 0; i < n; i++) {
        scanf("%d", &m);
        for (j = 0; j < m; j++) {
            scanf("%d%d", &s, &t);
            for (k = s; k < t; k++)
                on[i][k] = 1;
        }
    }
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
        scanf("%d%d", &s, &t);
        j = 0;
        while (happen[s][j] != -1)
            j++;
        happen[s][j] = t - 1;
    }
    for (i = 0; i <= time; i++) {
        j=0;
        while (happen[s][j] != -1) {
            start[happen[i][j]] = 1;
            j++;
        }
        for (j = 0; j < n; j++)
            tmp[j] = fini[j];
        for (j = 0; j < n; j++) {
            if (!start[j] || !on[j][i] || fini[j] >= size) continue;
            for (k = 0; k < n && tmp[j] < size; k++) {
                if (on[k][i] && fini[k] >= size) tmp[j] += speed[j][k];
            }
        }
        for (j = 0; j < n; j++)
            fini[j] = size < tmp[j] ? size : tmp[j];
    }
    for (i = 0; i < n; i++)
        printf("%d%%\n", int((double) fini[i] / size * 100.0));
}
int main() {
    int T;
 
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}