// 2007 World Finals: Jacquard Circuits
// ACM-ICPC Live Archive 2395

#include <cstdio>
#include <cstring>
#define N 1005
typedef long long ll;
typedef unsigned long long ull;
ll llabs(ll x) {
	return x < 0 ? -x : x;
}
ll gcd(ll m, ll n) {
	ll r;
	while (n > 0) {
		r = m % n;
		m = n;
		n = r;
	}
	return m;
}
struct POINT {
	ll x, y;
	bool ok;
	void get() {
		scanf("%lld%lld", &x, &y);
		ok = 1;
	}
};
inline ll cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

ull n, m;
POINT pl[N];
ll polyarea() {
	ll ans = 0;
	pl[n] = pl[0];
	for (int i = 0; i < n; i++)
		ans += pl[i].x * pl[i + 1].y - pl[i].y * pl[i + 1].x;
	return llabs(ans);
}
int next(int i) {
	i = (i + 1) % n;
	while (!pl[i].ok)
		i = (i + 1) % n;
	return i;
}
ll solve() {
	int i, j, begin, st;
	ll com, bg = 0, ba;
	for (i = 0; i < n; i++)
		pl[i].get();
	for (i = 0; i < n; i++)
		if (cross(pl[i], pl[(i - 1 + n) % n], pl[(i + 1) % n]) == 0) pl[i].ok = 0;
	for (i = 0; i < n; i++)
		if (pl[i].ok) {
			begin = i;
			break;
		}
	com = -1;
	for (i = begin, st = 1; i != begin || st == 1; i = next(i)) {
		st = 0;
		j = next(i);
		ll dx = llabs(pl[j].x - pl[i].x);
		ll dy = llabs(pl[j].y - pl[i].y);
		if (com == -1) {
			if (dx == 0) com = dy;
			if (dy == 0) com = dx;
			if (dx && dy) com = gcd(dx, dy);
		}
		else {
			if (dx) com = gcd(com, dx);
			if (dy) com = gcd(com, dy);
		}
	}
	ba = polyarea() / com / com;
	for (i = begin, st = 1; i != begin || st == 1; i = next(i)) {
		st = 0;
		j = next(i);
		ll dx = llabs(pl[j].x - pl[i].x);
		ll dy = llabs(pl[j].y - pl[i].y);
		if (dx == 0) bg += dy / com;
		if (dy == 0) bg += dx / com;
		if (dx && dy) bg += gcd(dx, dy) / com;
	}
	ull a = m * (m + 1) * (2 * m + 1) / 6;
	ull b = (m + 1) * m / 2;
	ull ans = (a * ba - b * bg + 2 * m) / 2;
	return ans;
}

int main() {
	int ca = 1;
	while (scanf("%llu%llu", &n, &m) && n + m)
		printf("Case %d: %llu\n", ca++, solve());
	return 0;
}