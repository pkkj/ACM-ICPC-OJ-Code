// 2009 Ningbo: Columbus's bargain
// ACM-ICPC Live Archive 4761
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 30
#define INF 1<<30
struct NODE {
    int dest, cost;
    NODE() {
    }
    NODE(int dest, int cost) :
        dest(dest), cost(cost) {
    }
    bool operator <(const NODE &p) const {
        return cost > p.cost;
    }
};
struct EDGE {
    int b, d, next;
};
int dist[N], G[N], tot;
bool v[N];
 
EDGE E[N * N * 5];
void addedge(int a, int b, int x) {
    EDGE e = { b, x , G[a]};
    E[tot] = e;
    G[a] = tot++;
}
void solve() {
    int i, j, k, n, m, q, a, b, x, cnt;
    bool count[N] = {0};
    priority_queue<NODE> Q;
    scanf("%d", &n);
    tot = 0;
    memset(G, -1, sizeof(G));
    for (i = 0; i < n; i++) {
        scanf("%d%d", &q, &x);
        addedge(0, q, x - 1);
        dist[q] = x;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) {
            if (i == j) continue;
            if (dist[i] == dist[j]) addedge(i, j, 0), addedge(j, i, 0);
        }
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d%d", &a, &b, &x);
        addedge(a, b, x);
    }
    for (i = 1; i <= n; i++)
        dist[i] = INF;
    dist[0] = 0;
    memset(v, 0, sizeof(v));
    Q.push(NODE(0, 0));
    while (!Q.empty()) {
        NODE top = Q.top();
        Q.pop();
        if (v[top.dest]) continue;
        v[top.dest] = 1;
        for (i = G[top.dest]; ~i; i = E[i].next) {
            j = E[i].b;
            if (top.cost + E[i].d < dist[j]) {
                dist[j] = top.cost + E[i].d;
                Q.push(NODE(j, top.cost + E[i].d));
            }
        }
    }
    for (i = 1; i <= n; i++)
        printf("%d %d\n", i, dist[i]);
    cnt = 0;
 
    for (i = 1; i <= n; i++)
        for (j = i + 1; j <= n; j++)
            for (k = 1; k <= n; k++)
                if (i != k && j != k) if (dist[i] + dist[j] == dist[k]) count[k]=1;
    for(i = 1;i <= n;i++)
        cnt += count[i];
    printf("%d\n", cnt);
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}