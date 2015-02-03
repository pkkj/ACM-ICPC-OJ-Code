// 2009 Phuket: Elias Omega Coding
// ACM-ICPC Live Archive 4713
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<string>
#include<map>
#include<iostream>
typedef long long ll;
 
int getbit(ll x)
{
   int ans = 0;
   while(x)
       ans++, x >>= 1;
   return ans;
}
void f(ll x)
{
   if(x == 1)
   {
       printf("0");
       return;
   }
   ll bit = getbit(x);
   f(bit - 1);
   for(ll i = bit-1;i>=0;i--)
   {
      if(x & (1LL<<i))printf("1");
      else printf("0");
   }
}
 
int main()
{
   ll x;
   while(scanf("%lld", &x) && x)
   {
       f(x);
       printf("\n");
   }
   return 0;
}