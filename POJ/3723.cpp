// POJ 3723
// POJ Monthly Contest – 2009.04.05: Conscription
#include <algorithm>
#include <cstdio>
using namespace std;
#define N 100005
struct ITEM {
    int a, b, w;
    bool operator <(const ITEM x) const {
        return w > x.w;
    }
};
int fa[N];
void init_set(int n) {
    int i;
    for (i = 0; i <= n; i++)
        fa[i] = i;
}
int find_root(int p) {
    if (fa[p] != p) fa[p] = find_root(fa[p]);
    return fa[p];
}
void union_set(int p, int q) {
    int a = find_root(p), b = find_root(q);
    fa[b] = a;
}
ITEM el[N];
void solve() {
    int n, m, q, i;
    scanf("%d%d%d", &n, &m, &q);
    for (i = 0; i < q; i++)
        scanf("%d%d%d", &el[i].a, &el[i].b, &el[i].w);
    sort(el, el + q);
    long long ans = 0;
    init_set(n + m + 1);
    for (i = 0; i < q; i++)
        if (find_root(el[i].a) != find_root(el[i].b + n)) {
            union_set(el[i].a, el[i].b + n);
            ans -= el[i].w;
        }
    printf("%lld\n", ans + (n + m) * 10000);
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
