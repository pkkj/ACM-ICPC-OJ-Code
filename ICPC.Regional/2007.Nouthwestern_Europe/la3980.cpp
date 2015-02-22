// 2007 Northwestern Europe: Walk
// ACM-ICPC Live Archive 3980
// POJ 3506

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;

const int N = 2505;
const double EPS = 1e-8;
const double INF = 1e30;
const double LEFT = 0.0;
const double RIGHT = 100000.0;
const double Y = 0.1;

struct POINT {
	double x, y;
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

// Find the intersection between segment (a, b) and line y = 0.1
bool line_intersect(POINT &a, POINT &b, double &x) {
	if (Y < min(a.y, b.y) || Y > max(a.y, b.y))
		return false;
	double dy = b.y - a.y, dx = b.x - a.x;
	double k = (Y - a.y) / dy;
	x = a.x + k * dx;
	return min(a.x, b.x) <= x && x <= max(a.x, b.x);
}

POINT poly[N];

int main(){
	int T, np, height, size;
	scanf("%d", &T);

	while (T--){
		set< pair<double, int> > out[2];
		scanf("%d", &np);

		for (int i = 0; i < np; i++){
			double rightMost = -INF, x;
			int cntIntersect = 0, itsA = 0, itsB = 0;

			scanf("%d%d", &height, &size);
			for (int j = 0; j < size; j++)
				poly[j].read();
			poly[size] = poly[0];

			for (int j = 0; j < size; j++){
				if (line_intersect(poly[j], poly[j + 1], x)){
					rightMost = max(rightMost, x);

					if (LEFT < x && x < RIGHT) cntIntersect++;
					if (x < LEFT) itsA++;
					if (x > RIGHT) itsB++;
				}
			}

			// Determine whether the current polygon is in the route from A to B.
			// If yes, then determine which point it wraps.
			if (cntIntersect % 2 == 1){
				if (itsA % 2 == 1)
					out[0].insert(make_pair(rightMost, height));
				else if (itsB % 2 == 1)
					out[1].insert(make_pair(-rightMost, height));
			}
		}

		// Simulate walking from A to B
		int up = 0, down = 0;
		int curHeight = out[0].size() ? out[0].begin()->second : (out[1].size() ? out[1].begin()->second : 0);
		for (int i = 0; i < 2; i++){
			for (set< pair<double, int> >::iterator it = out[i].begin(); it != out[i].end(); it++){
					if (curHeight > it->second)
						down += curHeight - it->second;
					else
						up += it->second - curHeight;
					curHeight = it->second;
			}
		}

		printf("%d %d\n", up, down);
	}
	return 0;
}