// 2007 Tokyo: Lowest Pyramid
// ACM-ICPC Live Archive 3885
// POJ 3520
// Note: in POJ, G++ will get wrong answer.
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <vector>
using namespace std;

#define EPS 1e-7
const double INF = 1e20;
const int LIMIT = 100;
const int RANGE = 200;
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

struct POINT {
	double x, y;
	POINT() {}
	POINT(double x, double y) : x(x), y(y) {}
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
	void unit() {
		double k = sqrt(x * x + y * y);
		x /= k, y /= k;
	}
};

POINT p0, p1, p2;
vector<POINT> fast[RANGE * RANGE * 2 + 5];
double mySqrt[RANGE * RANGE * 2 + 5];
double dis(POINT &p1, POINT &p2){
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
double dis2(POINT &p1, POINT &p2){
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
double cross(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
int crossi(int ox, int oy, int ax, int ay, int bx, int by){
	return (ax - ox) * (by - oy) - (ay - oy) * (bx - ox);
}

bool intersect(POINT &a, double ra, POINT &b, double rb, POINT &p1, POINT &p2) {
	double d = dis2(a, b);
	if (d > (ra + rb) * (ra + rb)) return false;
	if (d < (ra - rb) * (ra - rb)) return false;
	double cosa = (ra * ra + d - rb * rb) / 2 / sqrt(d) / ra;
	double sina = sqrt(1 - cosa * cosa);
	POINT v = POINT(b.x - a.x, b.y - a.y);
	v.unit();
	v = v * ra;
	p1 = POINT(v.x * cosa - v.y * sina, v.x * sina + v.y * cosa) + a;
	p2 = POINT(v.x * cosa + v.y * sina, -v.x * sina + v.y * cosa) + a;
	return true;
}

bool isInteger(double x){
	return sgn(floor(x) - x) == 0 || sgn(ceil(x) - x) == 0;
}

bool isPcOk(POINT &pc){
	return pc.x >= -LIMIT && pc.x <= LIMIT && pc.y >= -LIMIT && pc.y <= LIMIT && isInteger(pc.x) && isInteger(pc.y) && sgn(cross(p2, pc, p0)) > 0;
}

#define N 3
double a[N][N];
double xdet(double a1, double a2, double b1, double b2) {
	return a1 * b2 - a2 * b1;
}
double volume(double p, double q, double r, double n, double m, double l) {
	a[0][0] = p * p;
	a[1][1] = q * q;
	a[2][2] = r * r;
	a[0][1] = a[1][0] = (p * p + q * q - n * n) / 2.0;
	a[0][2] = a[2][0] = (p * p + r * r - m * m) / 2.0;
	a[1][2] = a[2][1] = (q * q + r * r - l * l) / 2.0;
	double ans = a[0][0] * xdet(a[1][1], a[1][2], a[2][1], a[2][2]) + 
		a[0][2] * xdet(a[1][0], a[1][1], a[2][0], a[2][1]) - 
		a[0][1] * xdet(a[1][0], a[1][2], a[2][0], a[2][2]);
	if (ans < 0)
		return -INF;
	ans = sqrt(ans) / 6.0;
	return ans;
}

void solve(int x0, int y0, int x1, int y1, int x2, int y2){
	double minH = INF;
	double area = cross(p0, p1, p2) / 2.0;
	// Enumerate the location of the first point
	for (int i = -LIMIT; i <= LIMIT; i++){
		for (int j = -LIMIT; j <= LIMIT; j++){
			if (crossi(x0, y0, x1, y1, i, j) >= 0)
				continue;
			// Enumerate the second point
			int d_2 = (i - x1) * (i - x1) + (j - y1) * (j - y1);
			for (int k = 0; k < fast[d_2].size(); k++){
				int xb = x1 + fast[d_2][k].x;
				int yb = y1 + fast[d_2][k].y;
				if (xb > LIMIT || xb < -LIMIT || yb > LIMIT || yb < -LIMIT || crossi(x1, y1, xb, yb, x2, y2) <= 0)
					continue;

				// Calculate the third point
				POINT pa = POINT(i, j), pb = POINT(xb, yb);
				double d1 = dis(pa, p0), d2 = dis(pb, p2);
				POINT pc1, pc2;
				if (!intersect(p0, d1, p2, d2, pc1, pc2))
					continue;

				if (isPcOk(pc1) || isPcOk(pc2)){
					// Use pc1 is good enough because the volume is only determined by dis(pc, p2)
					double p = dis(p0, p1), q = dis(p0, p2), r = dis(p2, p1), n = dis(p0, pa), m = dis(p1, pa), l = dis(p2, pc1);
					double v = volume(p, q, n, r, m, l);
					if (v > EPS){
						double h = v * 3 / area; 
						if (h < minH && h > 1e-4)
							minH = h;
					}
				}
			}
		}
	}
	if (minH >= INF)
		printf("-1\n");
	else
		printf("%.7lf\n", minH);
}

int main() {
	// Do the preprocessing. Solve this problem first: given the distance, answer the possible points with in the grid
	for (int x = -RANGE; x <= RANGE; x++)
		for (int y = -RANGE; y <= RANGE; y++)
			fast[x * x + y * y].push_back(POINT(x, y));

	int x0, y0, x1, y1, x2, y2;
	while (scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x0, &y0)
		&& !(x0 == 0 && y0 == 0 && x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0)) {
		p0 = POINT(x0, y0), p1 = POINT(x1, y1), p2 = POINT(x2, y2);
		solve(x0, y0, x1, y1, x2, y2);
	}
}