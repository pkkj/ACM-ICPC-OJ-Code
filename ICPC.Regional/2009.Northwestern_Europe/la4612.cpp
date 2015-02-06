// CII 4612
// 2009 Northwestern Europe: Fractal
#include <cstdio>
#include <cstring>
#include <cmath>
#define N 105
struct POINT {
	double x, y;
	POINT() {
	}
	POINT(double x, double y) :
			x(x), y(y) {
	}
	void get() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("(%.10lf,%.10lf)\n", x, y);
	}
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	POINT operator *(const double & v) {
		return POINT(x * v, y * v);
	}
};
inline double dot(POINT &a, POINT &b) {
	return a.x * b.x + a.y * b.y;
}
inline double sqr(double x) {
	return x * x;
}
double dis(const POINT &p1, const POINT &p2) {
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
POINT rotate(const POINT &p, double a) {
	POINT ret;
	ret.x = p.x * cos(a) - p.y * sin(a);
	ret.y = p.x * sin(a) + p.y * cos(a);
	return ret;
}
inline double cross(POINT &a, POINT &b) {
	return a.x * b.y - a.y * b.x;
}

POINT points[N], newPoints[N];
double len[N], ratio[N];
int nextSeg[N];

void solve() {
	int depth, n;
	double frac, totalLength = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		points[i].get();
		if (i > 0) {
			len[i - 1] = dis(points[i], points[i - 1]);
			totalLength += len[i - 1];
		}
	}
	double shapeLength = dis(points[0], points[n - 1]);
	for (int i = 0; i < n - 1; i++) {
		ratio[i] = len[i] / totalLength;
	}

	scanf("%d%lf", &depth, &frac);
	// Find the last position in the fractal
	for (int dep = 0; dep < depth; dep++) {
		for (int i = 0; i < n - 1; i++) {
			if (ratio[i] >= frac) {
				nextSeg[dep] = i;
				frac = frac / ratio[i];
				break;
			}
			frac -= ratio[i];
		}
	}

	for (int dep = 0; dep < depth - 1; dep++) {
		int copyToSegIdx = nextSeg[dep];
		double scale = len[copyToSegIdx] / shapeLength;
		POINT a1 = points[0], a2 = points[n - 1];
		POINT b1 = points[copyToSegIdx], b2 = points[copyToSegIdx + 1];
		POINT v1 = a2 - a1, v2 = b2 - b1;
		double angle = acos(dot(v1, v2) / dis(a1, a2) / dis(b1, b2));
		if (cross(v1, v2) < 0)
			angle = -angle; // Be aware that the new shape appears in the counter-clockwise side of the original segment
		// Scale and rotate the polyline.
		for (int i = 0; i < n; i++) {
			newPoints[i] = points[i] * scale;
			newPoints[i] = rotate(newPoints[i], angle);
		}
		// Move the distorted new polyline to correct location.
		POINT move = b1 - newPoints[0];
		for (int i = 0; i < n; i++) {
			points[i] = newPoints[i] + move;
		}
	}
	// Pinpoint where we end in the final polyline.
	POINT a = points[nextSeg[depth - 1]], b = points[nextSeg[depth - 1] + 1];
	((b - a) * frac + a).print();
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		solve();
	return 0;
}

