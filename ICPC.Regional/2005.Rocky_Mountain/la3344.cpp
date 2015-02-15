// Rocky Mountain 2005: Suit Distribution
// ACM-ICPC Live Archive 3344
// POJ 2721

#include <cstdio>
#include <cmath>
#include <cstring>
double solve(int a, int b)
{
	double ans = 1.0;
	int mo[28], i;
	memset(mo, 0, sizeof(mo));
	for(i = 2; i <= 13; i++)
		mo[i] = 1;
	for(i = 14; i<= 26; i++)
		mo[i] = -1;
	for(i = 2; i <= a+b; i++)
		mo[i]++;
	for(i = 2; i <= a; i++)
		mo[i]--;
	for(i = 2; i <= b; i++)
		mo[i]--;
	for(i = 2; i <= 26-a-b; i++)
		mo[i]++;
	for(i = 2; i <= 13-a; i++)
		mo[i]--;
	for(i = 2; i <= 26-a-b-(13-a); i++)
		mo[i]--;
 
	for(i = 2;i <= 26; i++)
	{
		while(mo[i] < 0)
		{
			ans /= (double)i;
			mo[i]++;
		}
		while(mo[i] > 0)
		{
			ans *= (double)i;
			mo[i]--;
		}
	}
	if(a != b)
		ans *= 2;
	return ans;
}
 
int main()
{
	int a, b;
	while(scanf("%d%d", &a, &b) && a != -1)
	{
		printf("%d-%d split: %.8lf\n",a,b, solve(a, b));
	}
	return 0;
}