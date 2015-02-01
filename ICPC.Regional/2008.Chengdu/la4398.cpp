// 2008 Chengdu: Steal the Treasure
// ACM-ICPC Live Archive 4398
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 1005
struct EDGE {
    int a, b, w;
    bool t;
    bool operator<(const EDGE &e) const {
        return w > e.w;
    }
};
EDGE el[N*N / 2];
int fa[N];
bool v[N];
int find(int x) {
    if (fa[x] == x) return x;
    fa[x] = find(fa[x]);
    return fa[x];
}
void uniset(int x, int y) {
    fa[x] = y;
}
void init(int n) {
    for (int i = 0; i <= n; i++)
        fa[i] = i;
}
int solve(int n, int m) {
    int ans, i, cnt, ok, t;
    init(n);
    memset(v, 0, sizeof(v));
    for (i = 0; i < m; i++) {
        scanf("%d%d%d%d", &el[i].a, &el[i].b, &t, &el[i].w);
        el[i].t = (t == 1);
    }
    sort(el, el + m);
    ans = cnt = 0;
    for (i = 0; i < m && cnt < n; i++) {
        int x = find(el[i].a);
        int y = find(el[i].b);
        ok = 0;
        if (el[i].t) {
            if (!v[x]) v[x] = 1, ok = 1;
        } else {
            if (!v[x] && v[y]) v[x] = 1, ok = 1;
            else if (!v[y] && v[x]) v[y] = 1, ok = 1;
            else if (!v[x] && !v[y]) {
                ok = 1;
                uniset(x, y);
                if (x == y) v[x] = 1;
            }
        }
        if (ok) cnt++, ans += el[i].w;
    }
    return ans;
}
int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF)
        printf("%d\n", solve(n, m));
    return 0;
}