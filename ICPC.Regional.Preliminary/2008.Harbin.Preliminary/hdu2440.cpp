// 2008 Harbin Preliminary: Watch out the Animal
// HDU 2440

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define PRECISION  1e-8
#define N 101
int n;

struct POINT {
	double x, y;

	POINT(double x, double y) :
			x(x), y(y) {
	}

	POINT() :
			x(0), y(0) {
	}
};
POINT plist[N];
POINT ch[N];

double cross_det(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

int cmpzero(double d) {
	return (fabs(d) < PRECISION) ? 0 : (d > 0 ? 1 : -1);
}

inline double sqr(double x) {
	return x * x;
}

bool cmp_angle(const POINT &p1, const POINT &p2) {
	return cross_det(plist[0], p1, p2) > 0;
}

double pt_distance(const POINT &p1, const POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}

inline bool farer(const POINT &p1, const POINT &p2) {
	return pt_distance(p1, plist[0]) > pt_distance(p2, plist[0]);
}

int graham_scan() {
	int top;
	for (int i = 1; i < n; i++)
		if (plist[i].y < plist[0].y
				|| (plist[i].y == plist[0].y && plist[i].x < plist[0].x))
			swap(plist[i], plist[0]);
	sort(plist + 1, plist + n, cmp_angle);
	ch[0] = plist[0];
	ch[1] = plist[1];
	ch[2] = plist[2];
	top = 2;
	for (int i = 3; i < n; ++i) {
		while (!(cross_det(ch[top - 1], plist[i], ch[top]) < 0))
			--top;
		ch[++top] = plist[i];
	}
	return top;
}

double get_all_dis(const POINT &p, int newn) {
	double ans = 0.0;
	for (int i = 0; i <= newn; i++)
		ans += pt_distance(ch[i], p);
	return ans;
}

int main() {
	int i, newn, T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%lf%lf", &plist[i].x, &plist[i].y);
		newn = graham_scan();

		POINT st = ch[0];
		double step = 100, mind = get_all_dis(st, newn);
		while (step > 0.2) {
			int ok = 1;
			while (ok) {
				POINT tmp, nt;
				double t;
				ok = 0;
				tmp = POINT(st.x, st.y + step);
				t = get_all_dis(tmp, newn);
				nt = st;
				if (t < mind) {
					mind = t;
					ok = 1;
					nt = tmp;
				}

				tmp = POINT(st.x, st.y - step);
				t = get_all_dis(tmp, newn);
				if (t < mind) {
					mind = t;
					ok = 1;
					nt = tmp;
				}

				tmp = POINT(st.x + step, st.y);
				t = get_all_dis(tmp, newn);
				if (t < mind) {
					mind = t;
					ok = 1;
					nt = tmp;
				}

				tmp = POINT(st.x - step, st.y);
				t = get_all_dis(tmp, newn);
				if (t < mind) {
					mind = t;
					ok = 1;
					nt = tmp;
				}
				st = nt;
			}
			step = step / 2.0;
		}
		int ans = (int) (mind + 0.5) * 100 / 100;
		printf("%d\n", ans);
		if (T != 0)
			printf("\n");
	}
	return 0;
}
