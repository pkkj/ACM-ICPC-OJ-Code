// CII 4125
// 2008 World Finals: Painter
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
#define N 100005
#define INF 1000000
struct POINT {
	int x, y;
	POINT() {
	}
	POINT(int x, int y) :
		x(x), y(y) {
	}
	void get() {
		scanf("%d%d", &x, &y);
	}
	bool operator<(const POINT &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};
int curx;
struct SEG {
	POINT p1, p2;
	int id;
	SEG() {
	}
	SEG(const POINT &p1, const POINT &p2, int id) :
		p1(p1), p2(p2), id(id) {
	}
	double y() const {
		if (p1.x == p2.x) {
			return (p1.y + p2.y) / 2.0;
		}
		return p1.y + (p2.y - p1.y) * (curx + 1e-6 - p1.x) / (p2.x + 1e-6 - p1.x);
	}
	bool operator <(const SEG &s) const {
		return y() < s.y();
	}
 
};
typedef multimap<SEG, int>::iterator IT;
int sgn(long long x) {
	return x < 0 ? -1 : x > 0;
}
inline long long cross(const POINT &o, const POINT &a, const POINT &b) {
	return (long long) (a.x - o.x) * (b.y - o.y) - (long long) (a.y - o.y) * (b.x - o.x);
}
 
inline long long dot(const POINT &o, const POINT &a, const POINT &b) {
	return (long long) (a.x - o.x) * (b.x - o.x) + (long long) (a.y - o.y) * (b.y - o.y);
}
 
int between(const POINT &o, const POINT &a, const POINT &b) {
	return sgn(dot(o, a, b)) != 1;
}
 
bool intersect(const SEG &A, const SEG &B) {
	if (A.id == B.id) return 0;
	POINT a = A.p1, b = A.p2, c = B.p1, d = B.p2;
	int a_cd = sgn(cross(c, a, d));
	if (a_cd == 0 && between(a, c, d)) return 1;
	int b_cd = sgn(cross(c, b, d));
	if (b_cd == 0 && between(b, c, d)) return 1;
	int c_ab = sgn(cross(a, c, b));
	if (c_ab == 0 && between(c, a, b)) return 1;
	int d_ab = sgn(cross(a, d, b));
	if (d_ab == 0 && between(d, a, b)) return 1;
	if ((a_cd ^ b_cd) == -2 && (c_ab ^ d_ab) == -2) return 1;
	return 0;
}
 
struct TRI {
	POINT p1, p2, p3;
	IT p12, p13, p23;
	void get() {
		p1.get();
		p2.get();
		p3.get();
		if (p2 < p1) swap(p1, p2);
		if (p3 < p2) swap(p2, p3);
		if (p2 < p1) swap(p1, p2);
	}
};
#define IN 0
#define CH 1
#define OUT 2
struct EVENT {
	int id, x, type;
	EVENT() {
	}
	EVENT(int id, int x, int type) :
		id(id), x(x), type(type) {
	}
	bool operator <(const EVENT &e) const {
		if (x != e.x) return x < e.x;
		return type < e.type;
	}
};
int n, ans = 1;
TRI tr[N];
EVENT ev[N * 3];
multimap<SEG, int> T;
void update(IT i1, IT i2) {
	IT t = i1;
	i1->second = (--t)->second + 1;
	ans = max(ans, i1->second);
	i2->second = t->second;
}
 
bool isok(multimap<SEG, int>::iterator it) {
	multimap<SEG, int>::iterator a = it, b = it;
	a--, b++;
	if (intersect(a->first, b->first)) return 0;
	if (intersect(a->first, it->first)) return 0;
	if (intersect(it->first, b->first)) return 0;
	return 1;
}
void solve() {
	int i, j, cnt = 0;
	for (i = 0; i < n; i++) {
		tr[i].get();
		ev[cnt++] = EVENT(i, tr[i].p1.x, IN);
		ev[cnt++] = EVENT(i, tr[i].p2.x, CH);
		ev[cnt++] = EVENT(i, tr[i].p3.x, OUT);
	}
	sort(ev, ev + cnt);
	T.clear();
	T.insert(make_pair(SEG(POINT(-INF, -INF), POINT(INF, -INF), -1), 1));
	T.insert(make_pair(SEG(POINT(-INF, INF), POINT(INF, INF), -1), 0));
	curx = 0, ans = 1;
	for (i = 0; i < cnt && ans != -1; i++) {
		j = ev[i].id, curx = ev[i].x;
		if (ev[i].type == IN) {
			tr[j].p12 = T.insert(make_pair(SEG(tr[j].p1, tr[j].p2, j), 0));
			tr[j].p13 = T.insert(make_pair(SEG(tr[j].p1, tr[j].p3, j), 0));
			if (!isok(tr[j].p12) || !isok(tr[j].p13)) ans = -1;
			else {
				IT t = tr[j].p12;
				if (++t == tr[j].p13) update(tr[j].p12, tr[j].p13);
				else update(tr[j].p13, tr[j].p12);
			}
		} else if (ev[i].type == CH) {
			if (!isok(tr[j].p12)) ans = -1;
			else {
				tr[j].p23 = T.insert(make_pair(SEG(tr[j].p2, tr[j].p3, j), tr[j].p12->second));
				T.erase(tr[j].p12);
				if (!isok(tr[j].p23)) ans = -1;
			}
		} else if (ev[i].type == OUT) {
			if (!isok(tr[j].p13) || !isok(tr[j].p23)) ans = -1;
			else T.erase(tr[j].p13), T.erase(tr[j].p23);
		}
	}
	if (ans == -1) printf("ERROR\n");
	else printf("%d shades\n", ans);
}
int main() {
	int ca = 1;
	while (scanf("%d", &n) && n != -1) {
		printf("Case %d: ", ca++);
		solve();
	}
	return 0;
}
