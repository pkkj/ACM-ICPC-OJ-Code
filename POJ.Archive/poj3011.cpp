// 2006 Japan Domestic: Secrets in Shadows
// POJ 3011
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define N 105
#define EPS 1e-8
#define INF 1e30
#define PI 3.14159265358979323846
inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

struct POINT {
	double x, y;
	int idx;
	POINT() :
			x(0), y(0) {
	}
	POINT(double x, double y) :
			x(x), y(y) {
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	bool operator==(POINT &other) {
		return sgn(x - other.x) == 0 && sgn(y - other.y) == 0;
	}
	bool operator<(const POINT &p) const {
		return y < p.y;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	double angle() {
		return acos(x / abs());
	}
};

bool cmpDouble(double a, double b) {
	return sgn(a - b) == 0;
}
double dist(const POINT &a, const POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

POINT rotate(const POINT &p, double sina, double cosa) {
	return POINT(p.x * cosa - p.y * sina, p.x * sina + p.y * cosa);
}

POINT circles[N], rc[N];
int n;
double minAngle, maxAngle, minWidth, maxWidth;

double fixAngle(double angle) {
	while (angle < 0)
		angle += PI;
	while (angle > PI)
		angle -= PI;
	return angle;
}

void calcTangentAngle(int i, int j, vector<double> &angles) {
	// Angle of external tangent
	if (circles[i].y < circles[j].y)
		swap(i, j);
	double externalAngle = (circles[i] - circles[j]).angle();
	angles.push_back(PI - externalAngle);	// Apply (PI - angle) because the rotate() function rotate in counterclockwise way

	// Angle of internal tangent
	double disHalf = dist(circles[i], circles[j]) / 2.0;
	double tangentLen = sqrt(disHalf * disHalf - 1);
	double internalAngle = acos(tangentLen / disHalf);
	angles.push_back(PI - fixAngle(externalAngle - internalAngle));
	angles.push_back(PI - fixAngle(externalAngle + internalAngle));
}

void update(double angle, double width) {
	if (width > maxWidth)
		maxAngle = angle, maxWidth = width;
	if (width < minWidth)
		minAngle = angle, minWidth = width;
}

void solve() {
	// Generate all the tangent angles
	vector<double> angles;
	angles.push_back(0);
	angles.push_back(PI);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			calcTangentAngle(i, j, angles);

	sort(angles.begin(), angles.end());
	angles.erase(unique(angles.begin(), angles.end(), cmpDouble), angles.end());

	minWidth = INF, maxWidth = -INF;

	// Let f(θ) represents the width of shadow. Obviously f(θ) is a step function. Each interval of θ is determined by the angle between two tangent angles
	// The overlapping relation of shadow changed when the rotation passes a tangent angle.
	// So we need to solve these angle intervals one by one.
	for (size_t i = 0; i < angles.size() - 1; i++) {
		double centerAngle = 0.5 * (angles[i] + angles[i + 1]);
		double a = 0, b = 0, c = 0, sina = sin(centerAngle), cosa = cos(centerAngle);

		// Rotate everything in the plane
		for (int j = 0; j < n; j++) {
			rc[j] = rotate(circles[j], sina, cosa);
			rc[j].idx = j;
		}
		sort(rc, rc + n);

		// After rotation, the width of shadow is projected to y-axis. We need to find all the overlapping circles.
		// The width of shadow from some overlapping circles is determined by the north-most circle and south-most circle among them.
		// In this centerAngle rotation, the width is: sum (ymax_i - ymin_i + 2.0), we need to iterate all the overlapping circle set
		// Of course, centerAngle is not the optimal rotation angle. The optimal angle needs to be calculated.
		int left = 0;
		for (int j = 0; j <= n; j++) {
			if (j == 0 || j != n && rc[j].y - rc[j - 1].y <= 2)
				continue;

			// Find the vectors connecting the north-most circle center and south-most circle center in each overlapping circle set. Then move them to (0, 0).
			a += circles[rc[j - 1].idx].x - circles[rc[left].idx].x;
			b += circles[rc[j - 1].idx].y - circles[rc[left].idx].y;
			c += 2.0;
			left = j;
		}
		// Assume that θ (angles[i] < θ < angles[i+1]) is the optimal angle, which maximize or minimize the width of shadow.
		// The width of shadow W = sum (ymax_i - ymin_i + 2.0)
		// W = sum [(dx_i * sin θ) + (dy_i * cos θ) + 2].
		// W = a sin θ + b cos θ + 2.
		// W' = a cos θ - b sin θ = 0
		// a / b = tan θ
		double t = fixAngle(atan(a / b));

		update(angles[i], a * sin(angles[i]) + b * cos(angles[i]) + c);
		if (angles[i] < t && t < angles[i + 1])
			update(t, a * sin(t) + b * cos(t) + c);

	}
	printf("%.10lf\n%.10lf\n",  minAngle,  maxAngle);
}

int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			circles[i].read();
		solve();
	}
	return 0;
}
