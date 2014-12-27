// CII 4838
// 2010 Hangzhou: Rotational Painting

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 50005
#define EPS 1e-8
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
struct POINT {
	double x, y;
	POINT() {
		x = y = 0;
	}
	POINT(double x, double y) :
		x(x), y(y) {
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	POINT operator+(const POINT &p) {
		return POINT(x + p.x, y + p.y);
	}
 
};
POINT pl[N], ch[N];
int n;
double sqr(double x) {
	return x * x;
}
inline double cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
inline double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
double dis(const POINT &p1, const POINT &p2) {
	return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}
bool cmp_angle(const POINT &p1, const POINT &p2) {
	return cross(pl[0], p1, p2) > 0;
}
inline bool farer(const POINT &p1, const POINT &p2) {
	return dis(p1, pl[0]) > dis(p2, pl[0]);
}
 
void remove_point() {
	int idx = 1;
	for (int i = 2; i < n; ++i) {
		if (sgn(cross(pl[0], pl[i], pl[idx]))) pl[++idx] = pl[i];
		else if (farer(pl[i], pl[idx])) pl[idx] = pl[i];
	}
	n = idx + 1;
}
int graham_scan() {
	int top;
	for (int i = 1; i < n; i++)
		if (pl[i].y < pl[0].y || (pl[i].y == pl[0].y && pl[i].x < pl[0].x)) swap(pl[i], pl[0]);
	sort(pl + 1, pl + n, cmp_angle);
	remove_point();
	ch[0] = pl[0], ch[1] = pl[1], ch[2] = pl[2];
	top = 2;
	for (int i = 3; i < n; ++i) {
		while (!(cross(ch[top - 1], pl[i], ch[top]) < 0))
			--top;
		ch[++top] = pl[i];
	}
	return top;
}
POINT getcenter(int n) {
	int i;
	double area = 0;
	POINT ct;
	pl[n] = pl[0];
	for (i = 0; i < n; i++) {
		double s = cross(POINT(), pl[i], pl[i + 1]);
		POINT t;
		area += s;
		t = pl[i] + pl[i + 1];
		ct.x += s * t.x, ct.y += s * t.y;
	}
	ct.x = ct.x / area / 3.0, ct.y = ct.y / area / 3.0;
	return ct;
}
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int i, ans = 0;
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			pl[i].get();
		POINT center = getcenter(n);
		n = graham_scan() + 1;
		ch[n] = ch[0];
		for (i = 0; i < n; i++)
			if (sgn(dot(ch[i], center, ch[i + 1])) > 0 && sgn(dot(ch[i + 1], center, ch[i])) > 0) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
