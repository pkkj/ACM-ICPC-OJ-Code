// CII 4683
// 2009 Amritapuri: Find The Number
#include <cstdio>
#include <cstring>
#define N 12
typedef long long LL;
#define BIG (1LL<<51L)
#define MAX 1000000000000000LL
LL num[1 << N];
int cnt[1 << N], dep[N];
int n, m, k;
LL gcd(LL a, LL b) {
       return b ? gcd(b, a % b) : a;
}
void dfs(LL x, int cur, int bit) {
       if (cur > BIG) return;
       if (cur == k) {
               if (bit) {
                       num[m] = x, cnt[m] = bit;
                       m++;
               }
               return;
       }
       dfs(x / gcd(x, dep[cur])* dep[cur], cur + 1, bit + 1);
       dfs(x, cur + 1, bit);
}
LL check(LL x, int &mod) {
       LL ans = 0, t;
       int i;
       mod = 0;
       for (i = 0; i < k; i++) {
               if (x % dep[i] == 0) mod++;
       }
       for (i = 0; i < m; i++) {
               t = x / num[i];
               if (cnt[i] % 2 == 1) ans += cnt[i] * t;
               else ans -= cnt[i] * t;
       }
       return ans;
}
void solve() {
       int i, mod;
       LL l = BIG, r, mid, tmp;
       scanf("%d%d", &k, &n);
       for (i = 0; i < k; i++) {
               scanf("%d", &dep[i]);
               if (dep[i] < l) l = dep[i];
       }
       m = 0;
       dfs(1, 0, 0);
       /*      for(i =0; i <m;i++)
        printf("%lld %d\n",num[i], cnt[i]);*/
       r = MAX;
       while (l <= r) {
               mid = (l + r) >> 1;
               tmp = check(mid, mod);
               //printf("check mid %lld tmp %lld mod %d\n", mid, tmp, mod);
               if (tmp == n && mod == 1) break;
               if (tmp >= n) r = mid - 1;
               else l = mid + 1;
       }
       printf("%lld\n", mid);
}
int main() {
       int T;
       scanf("%d", &T);
       while (T--)
               solve();
       return 0;
}
