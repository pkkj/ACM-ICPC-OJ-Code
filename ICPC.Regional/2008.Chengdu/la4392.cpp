// 2008 Chengdu: Process scheduling
// ACM-ICPC Live Archive 4392
// HDU 2474
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
#define N 50005
#define M 3

struct PROCESS{
    PROCESS(){}
    int allocated[M], request[M], stage;
    bool operator<(const PROCESS &process){
        return request[stage] > process.request[process.stage];
    }
};
bool operator <(const PROCESS &a, const PROCESS &b) {
    return a.request[a.stage] > b.request[b.stage];
}

PROCESS process[N];
int available[M], n, m, processed;
priority_queue<PROCESS> q[M];

bool clearQueue(int dep){
    bool ok = false;
    if (dep + 1 == m){
        // Find all the executable processes, and release their resources
        while (!q[dep].empty() && q[dep].top().request[dep] <= available[dep]){
            PROCESS top = q[dep].top();
            for (int i = 0; i < m; i++)
                available[i] += top.allocated[i];
            q[dep].pop();
            ok = true;
            processed++;
        }
        return ok;
    }
    if (!q[dep].empty()){
        while (!q[dep].empty() && q[dep].top().request[dep] <= available[dep]){
            PROCESS top = q[dep].top();
            q[dep].pop();
            top.stage++;
            q[dep + 1].push(top);
            ok = true;
        }
        if (!ok) return false;
    }
    return clearQueue(dep + 1);
}

bool solve(){
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &process[j].allocated[i]);
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n;j++)
            scanf("%d", &process[j].request[i]);
    
    for (int i = 0; i < m; i++){
        scanf("%d", &available[i]);
        while (!q[i].empty())
            q[i].pop();
    }

    for (int i = 0; i < n; i++){
        process[i].stage = 0;
        q[0].push(process[i]);
    }
    
    processed = 0;
    while (processed < n){
        if (!clearQueue(0)) return false;
    }
    return true;
}

int main(){
    while (scanf("%d%d", &n, &m)  != EOF)
        printf(solve() ? "Yes\n" : "No\n");
    return 0;
}
