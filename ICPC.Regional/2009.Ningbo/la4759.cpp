// 2009 Ningbo: Hamlet’s gambling
// ACM-ICPC Live Archive 4759
// HDU 3266
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 100005
#define M1 13447
#define M2 57371
int n, m;
char sa[N], sb[N];

void print(vector<short> b) {
    for (int i = 0; i < (int) b.size(); i++)
        printf("%d", b[i]);
    printf("\n");
}
void div(char *sa, int len1, char *sb, int len2, vector<short> &b) {
    b.clear();
    int i, j;
    int s1k1 = 0, s1k2 = 0, s2k1 = 0, s2k2 = 0, b1 = 1, b2 = 1;
    for (i = 0, j = len1 - 1; i < len1 && i < len2; i++, j--) {
        int v1 = sa[j] == 'H' ? 1 : 2, v2 = sb[i] == 'H' ? 1 : 2;
        s1k1 = (s1k1 + b1 * v1) % M1;
        s1k2 = (s1k2 + b2 * v1) % M2;
        s2k1 = ((s2k1 << 1) + v2) % M1;
        s2k2 = ((s2k2 << 1) + v2) % M2;
        if (s1k1 == s2k1 && s1k2 == s2k2) b.push_back(1);
        else b.push_back(0);
        b1 = (b1 << 1) % M1, b2 = (b2 << 1) % M2;
    }
}
vector<short> sbsb, sbsa, sasa, sasb;
void sub(vector<short> &a, vector<short> &b) {
    int i, len = min((int) a.size(), (int) b.size());
    for (i = 0; i < len; i++) {
        a[i] -= b[i];
        if (a[i] < 0) a[i] += 2, a[i + 1]--;
    }
    for (i = (int) a.size() - 1; i >= 0; i--) {
        if (a[i] == 0) a.pop_back();
        else break;
    }
}
 
int cmp(vector<short> &a, vector<short> &b) {
    if (a.size() != b.size()) return (int) a.size() - (int) b.size();
    for (int i = (int) a.size() - 1; i >= 0; i--)
        if (a[i] != b[i]) return a[i] - b[i];
    return 0;
}
 
void solve() {
    scanf("%s%s", sa, sb);
    div(sb, m, sb, m, sbsb);
    div(sb, m, sa, n, sbsa);
    div(sa, n, sa, n, sasa);
    div(sa, n, sb, m, sasb);
    sub(sbsb, sbsa);
    sub(sasa, sasb);
    int ans = cmp(sbsb, sasa);
    if (ans > 0) printf("Hamlet\n");
    else if (ans == 0) printf("Equal\n");
    else printf("Laertes\n");
}
int main() {
    while (scanf("%d%d", &n, &m) && n + m)
        solve();
    return 0;
}