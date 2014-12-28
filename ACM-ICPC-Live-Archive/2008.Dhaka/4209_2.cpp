// CII 4209 - Solution 2
// 2008 Dhaka: Stopping Doom's Day
// 计算系数时用的拉格朗日插值法，附带多项式计算类和分数计算类。 

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20
typedef long long ll;
ll gcd(ll m, ll n) {
	ll r;
	if (m < 0) m = -m;
	if (n < 0) n = -n;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
struct FRAC {
	ll z, m;
	FRAC() {
		z = 0, m = 1;
	}
	FRAC(ll x) {
		z = x, m = 1;
	}
	void print() {
		if (z < 0 && m < 0) z = -z, m = -m;
		printf("(%I64d/%I64d)", z, m);
	}
};
FRAC operator +(const FRAC &a, const FRAC &b) {
	FRAC ans;
	ll g;
	ans.m = a.m * b.m;
	ans.z = a.z * b.m + b.z * a.m;
	g = gcd(ans.m, ans.z);
	ans.m /= g, ans.z /= g;
	return ans;
}
 
FRAC operator *(const FRAC &a, const FRAC &b) {
	FRAC ans;
	ll g;
	ans.m = a.m * b.m, ans.z = a.z * b.z;
	g = gcd(ans.m, ans.z);
	ans.m /= g, ans.z /= g;
	return ans;
}
FRAC operator /(const FRAC &a, ll k) {
	FRAC ans = a;
	ans.m *= k;
	ll g = gcd(ans.m, ans.z);
	ans.m /= g, ans.z /= g;
	return ans;
}
struct POLY {
	FRAC k[20];
	int h;
	void print() {
		int i;
		for (i = h; i >= 0; i--) {
			k[i].print();
			printf("x^%d ", i);
		}
	}
};
POLY operator *(const POLY &a, const POLY &b) {
	POLY ans;
	int i, j;
	ans.h = a.h + b.h;
	for (i = 0; i <= a.h; i++) {
		for (j = 0; j <= b.h; j++)
			ans.k[i + j] = ans.k[i + j] + a.k[i] * b.k[j];
	}
	return ans;
}
POLY operator +(const POLY &a, const POLY &b) {
	POLY ans;
	int i;
	ans.h = max(a.h, b.h);
	for (i = 0; i <= ans.h; i++) {
		ans.k[i] = a.k[i] + b.k[i];
	}
	return ans;
}
ll x[N], y[N];
FRAC f[N];
POLY p[N];
int main() {
	freopen("in.txt", "r", stdin);
	int i, j, n;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%I64d %I64d", x + i, y + i);
	}
	for (i = 0; i < n; i++) {
		f[i] = FRAC(y[i]);
		p[i].h = 0, p[i].k[0] = FRAC(1);
		for (j = 0; j < n; j++) {
			if (i == j) continue;
			f[i] = f[i] / (x[i] - x[j]);
			POLY pt;
			pt.h = 1;
			pt.k[0] = FRAC(-x[j]), pt.k[1] = FRAC(1);
			p[i] = p[i] * pt;
		}
		POLY pt;
		pt.h = 0;
		pt.k[0] = f[i];
		p[i] = p[i] * pt;
	}
	/*	for (i = 0; i < n; i++) {
	 f[i].print();
	 printf("   ");
	 p[i].print();
	 printf("\n");
	 }*/
	POLY final;
	for (i = 0; i < n; i++) {
		final = final + p[i];
	}
	printf("===================\n");
	final.print();
	printf("\n");
	for (i = n - 1; i >= 0; i--) {
		printf("%.6lf x ^ %d  \n", (double) final.k[i].z / final.k[i].m, i);
	}
	return 0;
}
