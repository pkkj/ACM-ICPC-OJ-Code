// 2009 Ningbo: Ancient vending machine
// ACM-ICPC Live Archive 4756
// HDU 3263
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define N 50
#define INF 1e100
#define EPS 1e-9
struct POINT {
	double x, y;
	void get() {
		scanf("%lf%lf", &x, &y);
	}
};
POINT hole[N], coin[N];
int n, m;
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
double dis(POINT &a, POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
double point_seg(POINT &p, POINT &a, POINT &b) {
	return fabs(cross(a, p, b) / dis(a, b));
}

bool cmp(const POINT &a, const POINT &b) {
	return cross(coin[0], a, b) > 0;
}

bool farer(POINT &a, POINT &b) {
	return dis(a, coin[0]) > dis(b, coin[0]);
}

double scoin() {
	int top, i, j;
	POINT ch[N];
	double ans = INF;
	for (i = 1; i < m; i++)
		if (coin[i].y < coin[0].y
				|| (coin[i].y == coin[0].y && coin[i].x < coin[0].x))
			swap(coin[i], coin[0]);
	sort(coin + 1, coin + m, cmp);
	j = 1;
	for (i = 2; i < m; i++) {
		if (sgn(cross(coin[0], coin[i], coin[j])))
			coin[++j] = coin[i];
		else if (farer(coin[i], coin[j]))
			coin[j] = coin[i];
	}
	ch[0] = coin[0], ch[1] = coin[1], ch[2] = coin[2];
	top = 2;
	for (int i = 3; i <= j; ++i) {
		while (!(cross(ch[top - 1], coin[i], ch[top]) < 0))
			--top;
		ch[++top] = coin[i];
	}
	top++;
	for (j = 0; j < top; j++) {
		double tmp = 0;
		for (i = 0; i < top; i++) {
			POINT a = ch[j], b = ch[(j + 1) % top];
			tmp = max(tmp, point_seg(ch[i], a, b));
		}
		ans = min(ans, tmp);
	}
	return ans;
}

double shole() {
	int i, j;
	double ans = 0;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			ans = max(ans, dis(hole[i], hole[j]));
	return ans;
}

int main() {
	int T, i;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			hole[i].get();
		scanf("%d", &m);
		for (i = 0; i < m; i++)
			coin[i].get();
		puts(shole() + EPS > scoin() ? "legal" : "illegal");
	}
	return 0;
}
