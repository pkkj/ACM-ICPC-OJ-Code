// 2000 Tehran: Dolphin Pool
// ACM-ICPC Live Archive 2059
// POJ 1688

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 20 + 5;
const double PI = 3.14159265358979323846;
const double EPS = 1e-8;

inline int sgn(double x) {
	return (x < -EPS) ? -1 : x > EPS;
}

struct POINT {
	double x, y, r, ang;
	int with;
	bool vis;
	void read(){
		scanf("%lf%lf%lf", &x, &y, &r);
	}
	POINT() { }
	POINT(double x, double y) : x(x), y(y) { }
	POINT(double x, double y, double ang, int with) : x(x), y(y), ang(ang), with(with), vis(false) { }
	POINT operator +(const POINT & b) {
		return POINT(x + b.x, y + b.y);
	}
	POINT operator -(const POINT & b) {
		return POINT(x - b.x, y - b.y);
	}
	bool operator ==(const POINT &p) {
		return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
	}
	bool operator<(const POINT &p) {
		return ang < p.ang;
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
	POINT to_length(double k) {
		double v = k / abs();
		return POINT(x * v, y * v);
	}
};

double sqr(double x) {
	return x * x;
}

POINT rotate(const POINT &p, double sina, double cosa) {
	POINT ret;
	ret.x = p.x * cosa - p.y * sina;
	ret.y = p.x * sina + p.y * cosa;
	return ret;
}

double calcang(POINT &o, POINT &p) {
	double ans = atan2(p.y - o.y, p.x - o.x);
	if (ans < 0) ans = 2 * PI + ans;
	return ans;
}

bool circle_intersect(POINT &a, POINT &b, POINT &p1, POINT &p2) {
	double d = sqr(a.x - b.x) + sqr(a.y - b.y), sina, cosa;
	if (d >= sqr(a.r + b.r)) return false;
	if (d <= sqr(a.r - b.r)) return false;
	d = sqrt(d);
	cosa = (sqr(a.r) + sqr(d) - sqr(b.r)) / 2 / d / a.r;
	sina = sqrt(1 - cosa * cosa);
	POINT v = b - a;
	v = v.to_length(a.r);
	p1 = rotate(v, sina, cosa), p2 = rotate(v, -sina, cosa);
	p1 = a + p1, p2 = a + p2;
	return true;
}

int n;
POINT circle[N];
bool in_circle(POINT &p){
	for (int i = 0; i < n; i++){
		double d = sqr(p.x - circle[i].x) + sqr(p.y - circle[i].y);
		if (sgn(d - circle[i].r * circle[i].r) == -1)
			return true;
	}
	return false;
}

void solve(){
	vector<POINT> intersects[N];
	int ans = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		circle[i].read();

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++){
			POINT p1, p2;

			// Only keep the intersecting points that not inside any circle
			if (circle_intersect(circle[i], circle[j], p1, p2)){
				if (!in_circle(p1)){
					intersects[i].push_back(POINT(p1.x, p1.y, calcang(circle[i], p1), j));
					intersects[j].push_back(POINT(p1.x, p1.y, calcang(circle[j], p1), i));
				}
				if (!in_circle(p2)){
					intersects[i].push_back(POINT(p2.x, p2.y, calcang(circle[i], p2), j));
					intersects[j].push_back(POINT(p2.x, p2.y, calcang(circle[j], p2), i));
				}
			}
		}	

	for (int i = 0; i < n; i++)
		sort(intersects[i].begin(), intersects[i].end());

	while (1){
		int cid = -1, iid = -1;
		for (int i = 0; i < n && cid == -1; i++)
			for (size_t j = 0; j < intersects[i].size() && cid == -1; j++)
				if (!intersects[i][j].vis)
					cid = i, iid = j;	

		if (cid == -1)break;
		double area = 0;
		int curc = cid, curi = iid, nextc, nexti;
		do{
			intersects[curc][curi].vis = true;
			
			// Try to move a small angle in counter-clockwise direction. Chech whether we will go into any circle
			double midang = intersects[curc][curi].ang  - 0.01;
			POINT midPoint = circle[curc] + POINT(cos(midang) * circle[curc].r, sin(midang) * circle[curc].r);

			if (in_circle(midPoint)){
				// Jump to the intersecting circle
				nextc = intersects[curc][curi].with;
				for (nexti = 0; nexti < intersects[nextc].size(); nexti++)
					if (intersects[nextc][nexti] == intersects[curc][curi]) break;
			}
			else{
				// Move to the next intersect point in counter-clockwise order.
				nexti = (curi - 1 + intersects[curc].size()) % intersects[curc].size();
				nextc = curc;
				area += intersects[nextc][curi].x * intersects[nextc][nexti].y - intersects[nextc][curi].y * intersects[nextc][nexti].x;
			}
			curc = nextc, curi = nexti;
		} while (!(curc == cid && curi == iid));
		if (sgn(area) > 0) ans++;
	}
	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) 
		solve();
	return 0;
}
