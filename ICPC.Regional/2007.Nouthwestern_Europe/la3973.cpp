// 2007 Nouthwestern Europe: Containers
// ACM-ICPC Live Archive 3973
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const long long INF = 1LL << 60LL;

long long area(long long  n, long long  m)
{
	long long nn, mm;
	nn = max(n, m);
	mm = min(n, m);
	return (10 * nn + 2) * (44 * mm + 4);
}

int main()
{
	int T;
	long long x, n, i, u1, u2;
	double dn;
	scanf("%d", &T);
	while (T--)
	{
		long long ans = INF, a, b, aa, bb;

		scanf("%lld", &x);
		n = (x + 4) / 5;
		dn = sqrt((double)n);
		for (i = 1; i <= (long long)dn + 1; i++)
		{
			u1 = n / i;
			u2 = n / i + 1;
			if (u1 * i < n)
				u1 = u2;

			if (area(i, u1) < ans)
				a = i, b = u1, ans = area(i, u1);
		}
		aa = 10 * max(a, b) + 2;
		bb = 44 * min(a, b) + 4;
		if (aa < bb)
			swap(aa, bb);
		printf("%lld X %lld = %lld\n", aa, bb, ans);
	}
	return 0;
}
