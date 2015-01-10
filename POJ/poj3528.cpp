// POJ 3528
// POJ Founder Monthly Contest – 2008.07.27: Ultimate Weapon
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
#define N 505
#define EPS 1e-8
 
int sgn(double x) {
	return x < -EPS ? -1 : x > EPS;
}
struct POINT {
	double x, y, z;
	POINT() {
	}
	POINT(double x, double y, double z) :
		x(x), y(y), z(z) {
	}
	void get() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	double len() {
		return sqrt(x * x + y * y + z * z);
	}
 
};
POINT operator+(const POINT a, const POINT b) {
	return POINT(a.x + b.x, a.y + b.y, a.z + b.z);
}
POINT operator-(const POINT &a, const POINT &b) {
	return POINT(a.x - b.x, a.y - b.y, a.z - b.z);
}
POINT operator*(const POINT &a, const POINT &b) {
	return POINT(a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - b.x * a.y);
}
POINT operator/(const POINT &a, const double &k) {
	return POINT(a.x / k, a.y / k, a.z / k);
}
POINT P[N];
double dot(const POINT &a, const POINT &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
double dot(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y) + (a.z - o.z) * (b.z - o.z);
}
POINT cross(POINT &o, POINT &a, POINT &b) {
	return (a - o) * (b - o);
}
struct FACE {
	int a, b, c;
	FACE() {
	}
	FACE(int a, int b, int c) :
		a(a), b(b), c(c) {
	}
	double area() {
		return cross(P[a], P[b], P[c]).len() / 2.0;
	}
	bool sameside(POINT &q, POINT & p) {
		double u = dot((P[a] - q), cross(q, P[b], P[c]));
		double v = dot((P[a] - p), cross(p, P[b], P[c]));
		return sgn(u * v) > 0;
	}
};
 
bool e[N][N];
vector<FACE> hull, tmp;
vector<pair<int, int> > line;
double convexhull3d(int n) {
	double ans = 0.0;
	int i, j;
	POINT center;
	if (n == 2) return 0.0;
	else if (n == 3) return cross(P[0], P[1], P[2]).len() / 2.0;
	memset(e, 0, sizeof(e));
	for (i = 0; i < 4; i++)
		hull.push_back(FACE(i, (i + 1) % 4, (i + 2) % 4));
	center = (P[0] + P[1] + P[2] + P[3]) / 4.0;
	for (i = 4; i < n; i++) {
		tmp.clear();
		line.clear();
		for (j = 0; j < (int) hull.size(); j++) {
			if (!hull[j].sameside(center, P[i])) {
				int a = hull[j].a, b = hull[j].b, c = hull[j].c;
				e[a][b] = e[b][a] = !e[a][b];
				line.push_back(make_pair(a, b));
				e[a][c] = e[c][a] = !e[a][c];
				line.push_back(make_pair(a, c));
				e[b][c] = e[c][b] = !e[b][c];
				line.push_back(make_pair(b, c));
			} else tmp.push_back(hull[j]);
		}
		hull = tmp;
		for (j = 0; j < (int) line.size(); j++) {
			int a = line[j].first, b = line[j].second;
			if (e[a][b]) {
				hull.push_back(FACE(a, b, i));
				e[a][b] = e[b][a] = 0;
			}
		}
	}
	for (i = 0; i < (int) hull.size(); i++)
		ans += hull[i].area();
	return ans;
}
int main() {
	int i, n;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		P[i].get();
	printf("%.3lf\n", convexhull3d(n));
	return 0;
}
