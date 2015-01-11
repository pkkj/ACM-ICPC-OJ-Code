// POJ 2932
// 2005 MIT Programming Contest: Coneology
#include <cmath>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;
#define EPS 1e-8
#define N 50005
struct POINT {
	double x, y, r;
	void get() {
		scanf("%lf%lf%lf", &r, &x, &y);
	}
};
POINT P[N];
int idx[N], yrank[N], n;
struct EVENT {
	double x;
	bool type;
	int idx;
	EVENT() {
	}
	EVENT(double x, bool type, int idx) :
		x(x), type(type), idx(idx) {
	}
	bool operator <(const EVENT& e) const {
		if (e.x != x) return x < e.x;
		return idx < e.idx;
	}
};
set<int> S;
EVENT e[N * 2];
bool cmpy(const int &a, const int &b) {
	if (P[a].y == P[b].y) return P[a].x < P[b].x;
	return P[a].y < P[b].y;
}
double sqr(double x) {
	return x * x;
}
double dis(const POINT &a, const POINT &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)) - fabs(a.r - b.r);
}
 
bool block(int a, int b) {
	a = idx[a], b = idx[b];
 
	if (dis(P[a], P[b]) < EPS) return 1;
	return 0;
}
bool insert(int id) {
	set<int>::iterator it = S.insert(id).first, it2;
	it2 = it;
	if (it != S.begin()) {
		it--;
		if (block(id, *it)) {
			S.erase(id);
			return 0;
		}
	}
	it2++;
	if (it2 != S.end()) {
		if (block(id, *it2)) {
			S.erase(id);
			return 0;
		}
	}
	return 1;
}
int ans[N];
void solve() {
	int i, an = 0, j;
	for (i = j = 0; i < n; i++) {
		P[i].get();
		e[j++] = EVENT(P[i].x - P[i].r, 1, i);
		e[j++] = EVENT(P[i].x + P[i].r, 0, i);
		idx[i] = i;
	}
	sort(idx, idx + n, cmpy);
	sort(e, e + 2 * n);
	for (i = 0; i < n; i++)
		yrank[idx[i]] = i;
	S.clear();
 
	for (i = 0; i < 2 * n; i++) {
		if (e[i].type == 1) {
			if (insert(yrank[e[i].idx])) ans[an++] = e[i].idx;
		} else {
			if (S.find(yrank[e[i].idx]) != S.end()) S.erase(yrank[e[i].idx]);
		}
	}
	sort(ans, ans + an);
	printf("%d\n", an);
	for (i = 0; i < an; i++)
		printf("%d ", ans[i] + 1);
	printf("\n");
}
int main() {
	while (scanf("%d", &n) != EOF)
		solve();
	return 0;
}
