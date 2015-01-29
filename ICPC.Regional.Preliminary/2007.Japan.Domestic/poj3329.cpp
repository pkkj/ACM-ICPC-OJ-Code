// 2007 Japan Domestic: Twirl Around
// POJ 3229
// Aizu OJ 1151
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define EPS 1e-5
#define INF 1e30
#define PI 3.14159265358979323846
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

#define N 105

struct POINT {
	double x, y;
	POINT() :
			x(0), y(0) {
	}
	POINT(double x, double y) :
			x(x), y(y) {
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
	double operator *(POINT &p) {
		return x * p.x + y * p.y;
	}
	bool operator==(POINT &other) {
		return sgn(x - other.x) == 0 && sgn(y - other.y) == 0;
	}
	bool operator<(const POINT &p) const {
		if (sgn(p.x - x))
			return x < p.x;
		return y < p.y;
	}
	bool operator !=(const POINT &p) {
		return sgn(x - p.x) != 0 || sgn(y - p.y) != 0;
	}
	double abs2() {
		return x * x + y * y;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	void print() {
		printf("%.8lf  %.8lf\n", x, y);
	}
};
double dist(const POINT &a, const POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double cross(const POINT &o, const POINT &a, const POINT &b) {
	return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}
double dot(POINT &o, POINT &a, POINT &b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}
int inSegment(POINT &o, POINT &p1, POINT &p2) {
	return sgn(cross(p1, o, p2)) == 0 && sgn(dot(p1, p2, o)) >= 0;
}
int inbound(POINT &a, POINT &b, POINT &c) {
	return a.x <= max(b.x, c.x) && a.x >= min(b.x, c.x) && a.y <= max(b.y, c.y) && a.y >= min(b.y, c.y);
}
int between(POINT &o, POINT &a, POINT &b) {
	return sgn(dot(o, a, b)) != 1;
}
int solveQuadraticFormula(double a, double b, double c, double &x1, double &x2) {
	double d = b * b - 4 * a * c;
	if (sgn(d) < 0)
		return -1;
	d = sqrt(d);
	x1 = (-b + d) / 2.0 / a;
	x2 = (-b - d) / 2.0 / a;
	return 1;
}

vector<POINT> lineCircleIntersect(POINT A, POINT B, POINT O, double R) {
	vector<POINT> ans;
	POINT toO = O - POINT(0, 0), C, D;
	A = A - toO, B = B - toO, O = O - toO;
	double a, b, c, x1, x2;
	POINT v = A - B;
	a = v.abs2();
	b = 2.0 * (B * v);
	c = B.abs2() - R * R;
	if (solveQuadraticFormula(a, b, c, x1, x2) >= 0) {
		C = B + v * x1, D = B + v * x2;
		if (inbound(C, B, A))
			ans.push_back(C + toO);
		if (inbound(D, B, A))
			ans.push_back(D + toO);
	}
	return ans;
}

POINT rotateVector(POINT &p1, POINT &p2, double a) {
	POINT p = p2 - p1, res;
	res.x = p.x * cos(a) - p.y * sin(a);
	res.y = p.x * sin(a) + p.y * cos(a);
	return res + p1;
}

POINT poly[N];
int n;
double l, r;

// Determine whether the end is blocked by an edge
int turnable(POINT &p1, POINT &p2, POINT &pivot, POINT &end) {
	// I. Edge and pivot are in the same line.
	if (sgn(cross(p1, p2, pivot)) == 0)
		return !(p1 < p2 && pivot < end);

	// II. p1 intersects the stick, may block its movement
	if (inSegment(p1, pivot, end))
		return sgn(cross(pivot, p2, p1)) <= 0;

	// III. End of the stick touches the end of edge.
	if (end == p1 || end == p2) {
		if (!between(pivot, p1, p2))
			return true;
	}

	// IV. End of the stick locates inside an edge. Need to calculate their degree to determine
	if (sgn(cross(p1, p2, pivot)) > 0)
		return sgn(dot(end, p1, pivot)) <= 0;
	else
		return sgn(dot(end, p1, pivot)) >= 0;
}

double getAngle(POINT &o, POINT &p1, POINT &p2) {
	// Be careful! We need to verify this. Otherwise acos() will cause exception.
	if (sgn(cross(o, p1, p2)) == 0)
		return sgn(dot(o, p1, p2)) == 1 ? 0 : PI;

	double cosa = dot(o, p1, p2) / (p1 - o).abs() / (p2 - o).abs();
	return acos(cosa);
}

double getRotateAngle(POINT &pivot, POINT &end, POINT &newPivot) {
	double disPivotToEnd = dist(end, pivot);
	double farestStop = 0, minAngle = PI;
	newPivot = pivot;
	for (int i = 0; i < n; i++) {
		// I. The end of the stick touch an edge: segment-circle intersection
		vector<POINT> newPivots = lineCircleIntersect(poly[i], poly[i + 1], pivot, dist(pivot, end));

		// II. An end of edge block the movement of the stick
		if (pivot != poly[i] && dist(poly[i], pivot) <= disPivotToEnd) {
			newPivots.push_back(poly[i]);
		}

		for (size_t j = 0; j < newPivots.size(); j++) {
			// We only handle the rotation < 180 degrees
			if (sgn(cross(pivot, newPivots[j], end)) < 0)
				continue;
			double angle = getAngle(pivot, end, newPivots[j]);
			// Be careful when the turning angle is 0. Turnable means the point could rotate.
			if (sgn(angle) == 0 && turnable(poly[i], poly[i + 1], pivot, newPivots[j]))
				continue;
			// Take the destination with minimum angle. If tied, the farthest pivot should be used.
			if (minAngle > angle) {
				minAngle = angle;
				newPivot = newPivots[j];
				farestStop = dist(pivot, newPivot);
			} else if (sgn(angle - minAngle) == 0 && dist(pivot, newPivots[j]) > farestStop) {
				newPivot = newPivots[j];
				farestStop = dist(pivot, newPivot);
			}
		}
	}
	return minAngle;
}

void solve() {
	POINT ends[2] = { POINT(0, 0), POINT(0, l) }, pivot;
	pivot = ends[0];
	r = r * 2 * PI;
	while (1) {
		if (pivot == ends[0] || pivot == ends[1]) {
			// The pivot is one of the ends of the stick. Only the flexible end should be rotated.
			int pivotId = pivot == ends[0] ? 0 : 1;
			POINT newPivot;
			double angle = getRotateAngle(pivot, ends[!pivotId], newPivot);
			if (sgn(angle) == 0)
				break;
			if (angle > r) {
				ends[!pivotId] = rotateVector(pivot, ends[!pivotId], -r);
				break;
			}
			ends[!pivotId] = rotateVector(pivot, ends[!pivotId], -angle);
			pivot = newPivot;
			r -= angle;
		} else {
			// The pivot is somewhere inside the stick. Both ends should be rotated. But only turn the minimum angle afterwards.
			POINT newPivots[2];
			double newAngles[2];
			newAngles[0] = getRotateAngle(pivot, ends[0], newPivots[0]);
			newAngles[1] = getRotateAngle(pivot, ends[1], newPivots[1]);

			if (sgn(newAngles[0]) == 0 || sgn(newAngles[1]) == 0)
				break;
			int newPivotId = sgn(newAngles[0] - newAngles[1]) == -1 ? 0 : 1;
			if (newAngles[newPivotId] > r) {
				ends[0] = rotateVector(pivot, ends[0], -r);
				ends[1] = rotateVector(pivot, ends[1], -r);
				break;
			}
			ends[0] = rotateVector(pivot, ends[0], -newAngles[newPivotId]);
			ends[1] = rotateVector(pivot, ends[1], -newAngles[newPivotId]);
			pivot = newPivots[newPivotId];
			r -= newAngles[newPivotId];
		}
	}
	ends[0].print();
}

int main() {
	while (scanf("%lf%lf%d", &l, &r, &n) && n) {
		for (int i = 0; i < n; i++)
			poly[i].read();
		poly[n] = poly[0];
		solve();
	}
}
