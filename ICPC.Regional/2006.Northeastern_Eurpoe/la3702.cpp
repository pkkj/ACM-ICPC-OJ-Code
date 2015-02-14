// 2006 Northeastern Europe: ASCII Art
// ACM-ICPC Live Archive 3702

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define N 105

struct IPOINT {
	int x, y;
	void get() {
		scanf("%d%d", &x, &y);
	}
};
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
			x(x), y(y) {
	}
	POINT(IPOINT p) :
			x((double) p.x), y((double) p.y) {
	}
};
#define EPS 1e-8
struct LINE {
	POINT a, b;
	LINE() {
	}
	LINE(POINT a, POINT b) :
			a(a), b(b) {
	}
};
int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}
inline double cross(POINT &p, POINT &a, POINT &b) {
	return (a.x - p.x) * (b.y - p.y) - (b.x - p.x) * (a.y - p.y);
}
bool line_inter(POINT &a, POINT &b, POINT &c, POINT &d, POINT &p)
		{
	if (cross(c, a, d) * cross(c, b, d) >= 0)
		return false;
	double t1 = cross(b, a, d), t2 = cross(b, a, c);
	p.x = (t1 * c.x - t2 * d.x) / (t1 - t2);
	p.y = (t1 * c.y - t2 * d.y) / (t1 - t2);
	return true;
}

struct POLY {
	POINT pl[7];
	int n;
	POLY() {
		n = 0;
	}
};
double poly_area(POLY &p) {
	double s = 0;
	for (int i = 0; i < p.n; i++)
		s += p.pl[i].x * p.pl[(i + 1) % p.n].y - p.pl[i].y * p.pl[(i + 1) % p.n].x;
	return s / 2;
}
POLY cut(LINE l, POLY &ps)
		{
	POINT p;
	POLY temp;
	temp.n = 0;
	int i;
	for (i = 0; i < ps.n; ++i) {
		if (line_inter(ps.pl[i], ps.pl[i + 1], l.a, l.b, p))
			temp.pl[temp.n++] = p;
		if (sgn(cross(l.a, l.b, ps.pl[i + 1])) <= 0)
			temp.pl[temp.n++] = ps.pl[i + 1];
	}
	temp.pl[temp.n] = temp.pl[0];
	return temp;
}

int Q, n, m;
IPOINT pl[N];
double area[N][N];
void calc(IPOINT A, IPOINT B) {
	int sgn = 1, i, j, x1, x2, y1, y2;
	POINT a, b;
	double S;
	POINT pa, pb, pc, pd;
	if (A.x == B.x)
		return;
	if (A.x > B.x)
		sgn = -1, swap(A, B);
	a.x = A.x, a.y = A.y;
	b.x = B.x, b.y = B.y;
	y1 = min(A.y, B.y), y2 = max(A.y, B.y);
	x1 = min(A.x, B.x), x2 = max(A.x, B.x);
	for (i = x1; i < x2; i++) {
		for (j = 0;; j++) {
			if (j >= y2)
				break;
			if (j + 1 <= y1)
				area[i][j] += sgn;
			else {
				POLY ans;
				ans.n = 0;
				ans.pl[ans.n++] = POINT(i, j);
				ans.pl[ans.n++] = POINT(i + 1, j);
				ans.pl[ans.n++] = POINT(i + 1, j + 1);
				ans.pl[ans.n++] = POINT(i, j + 1);
				ans.pl[ans.n++] = POINT(i, j);
				ans.n = 4;
				ans = cut(LINE(a, b), ans);
				S = fabs(poly_area(ans));
				if (S == 0)
					break;
				area[i][j] += sgn * S;
			}
		}
	}

}

void print() {
	int i, j;
	for (i = m - 1; i >= 0; i--) {
		for (j = 0; j < n; j++) {
			if (area[j][i] + EPS < 0.25)
				printf(".");
			else if (area[j][i] + EPS < 0.5)
				printf("+");
			else if (area[j][i] + EPS < 0.75)
				printf("o");
			else if (area[j][i] < 1)
				printf("$");
			else
				printf("#");
		}
		printf("\n");
	}
}

int main() {
	int begin = 1;
	while (~scanf("%d%d%d", &Q, &n, &m)) {
		if (begin)
			begin = 0;
		else
			printf("\n");
		for (int i = 0; i < Q; i++)
			pl[i].get();
		memset(area, 0, sizeof(area));
		for (int i = 0; i < Q; i++)
			calc(pl[i], pl[(i + 1) % Q]);
		print();
	}
	return 0;
}
